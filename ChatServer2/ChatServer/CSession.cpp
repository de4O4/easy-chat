#include "CSession.h"
#include "CServer.h"
#include "LogicSystem.h"
#include <iostream>
#include <sstream>
CSession::CSession(boost::asio::io_context& ioc, CServer* server):_socket(ioc) , _server(server),_user_uid(0),
_b_close(false),_b_head_parse(false)
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	_session_id = boost::uuids::to_string(a_uuid);
	_recv_head_node = std::make_shared<MsgNode>(HEAD_TOTAL_LEN);

}

void CSession::Close() {
	std::lock_guard<std::mutex> lock(_session_mtx);
	_socket.close();
	_b_close = true;
}

CSession::~CSession()
{
	std::cout << "CSession Destruct!" << std::endl;
}

tcp::socket& CSession::GetSocket()
{
	return _socket;
}

std::string& CSession::GetSessionid()
{
	return _session_id;
}

void CSession::SetUserid(int uid)
{
	_user_uid = uid;
}

int CSession::GetUserid()
{
	return _user_uid;
}

void CSession::Start()
{
	AsyncReadHead(HEAD_TOTAL_LEN); //开始异步读取消息头
}

void CSession::Send(char* msg, short max_length, short msgid)
{
	std::lock_guard<std::mutex> lock(_send_lock);
	int send_len = _send_que.size();
	if (send_len > MAX_SENDQUE) {
		std::cout << "session :" << _session_id << " send queue is full!" << std::endl;
		return;
	}
	_send_que.push(std::make_shared<SendNode>(msg, max_length, msgid));
	if (send_len > 0) {
		return; // already in sending process	
	}
	auto& msgnode = _send_que.front();			//从发送队列取出头部消息进行发送
	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data , msgnode->_total_len) , 
		std::bind(&CSession::HandlerWrite , this , std::placeholders::_1 , SharedSelf()));
}

void CSession::Send(std::string msg, short msgid)
{
	std::lock_guard<std::mutex> lock(_send_lock);
	int send_len = _send_que.size();
	if (send_len > MAX_SENDQUE) {
		std::cout << "session :" << _session_id << " send queue is full!" << std::endl;
		return;
	}
	_send_que.push(std::make_shared<SendNode>(msg.c_str(), msg.length(), msgid));
	if (send_len > 0) {
		return; // already in sending process	
	}
	auto& msgnode = _send_que.front();			//从发送队列取出头部消息进行发送
	std::cout << "开始发送数据！" << std::endl;
	boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
		std::bind(&CSession::HandlerWrite, this, std::placeholders::_1, SharedSelf()));
}

std::shared_ptr<CSession> CSession::SharedSelf()
{
	return shared_from_this();
}

void CSession::AsyncReadBody(int length)
{
	auto self = SharedSelf();
	asyncReadFull(length, [self , length](const boost::system::error_code& ec, std::size_t bytes_to_transfered) {
		try
		{
			if (ec) {
				std::cout << " read body failed code is :" << ec.what() << std::endl;
				self->Close();
				self->_server->ClearSession(self->_session_id);
				return;
			}
			if (bytes_to_transfered < length) {
				std::cout << "read body length is less than total length!" << std::endl;
				self->Close();
				self->_server->ClearSession(self->_session_id);
				return;
			}
			memcpy(self->_recv_msg_node->_data, self->_data, bytes_to_transfered);
			self->_recv_msg_node->_cur_len += bytes_to_transfered; //更新当前接收消息长度
			self->_recv_msg_node->_data[self->_recv_msg_node->_total_len] = '\0'; //确保字符串结尾
			std::cout << "read data is " << self->_recv_msg_node->_data << std::endl;
			LogicSystem::GetInstance()->PostMsgToQue(std::make_shared<LogicNode>(self , self->_recv_msg_node));
			self->AsyncReadHead(HEAD_TOTAL_LEN);	//继续监听读取头部消息
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception code is " << e.what() << std::endl;
		}
		});
}

void CSession::AsyncReadHead(int total_len)
{
	auto self = SharedSelf();
	asyncReadFull(total_len, [self](const boost::system::error_code& ec, const std::size_t bytes_to_transfered) {
		try
		{
			if (ec) {
				std::cout << "read failed code is :" << ec.what() << std::endl;
				self->Close();
				self->_server->ClearSession(self->_session_id);
				return;
			}
			if (bytes_to_transfered < HEAD_TOTAL_LEN) {
				std::cout<< "read head length is less than total length!" << std::endl;
				self->Close();
				self->_server->ClearSession(self->_session_id);
				return;
			}
			self->_recv_head_node->clear();
			memcpy(self->_recv_head_node->_data, self->_data, bytes_to_transfered);
			short msg_id = 0;
			memcpy(&msg_id, self->_recv_head_node->_data, HEAD_ID_LEN);
			msg_id = boost::asio::detail::socket_ops::network_to_host_short(msg_id);	//获得主机字节序的消息ID
			std::cout << "read head msg_id is " << msg_id << std::endl;
			if (msg_id > MAX_LENGTH) {
				std::cout << "非法消息ID! " << std::endl;
				self->_server->ClearSession(self->_session_id);
				return;
			}

			short msg_len = 0;
			memcpy(&msg_len, self->_recv_head_node->_data + HEAD_ID_LEN, HEAD_DATA_LEN);
			msg_len = boost::asio::detail::socket_ops::network_to_host_short(msg_len);	//获得主机字节序的消息长度
			std::cout << "read head msg_len is " << msg_len << std::endl;
			if (msg_len > MAX_LENGTH) {
				std::cout << "非法消息长度! " << std::endl;
				self->_server->ClearSession(self->_session_id);
				return;
			}
			self->_recv_msg_node = std::make_shared<RecvNode>(msg_len , msg_id); //创建接收消息节点
			self->AsyncReadBody(msg_len);
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception code is " << e.what() << std::endl;
		}
		});
}

void CSession::asyncReadFull(std::size_t maxlen, std::function<void(const boost::system::error_code& ec, const std::size_t bytes_to_transfered)> hander)
{
	::memset(_data, 0, MAX_LENGTH);
	asyncReadLen(0, maxlen, hander);
}

void CSession::asyncReadLen(std::size_t read_len, std::size_t total_len, std::function<void(const boost::system::error_code& ec, const std::size_t bytes_to_transfered)> hander)
{
	auto self = SharedSelf();
	_socket.async_read_some(boost::asio::buffer(_data + read_len, total_len - read_len), [hander, self, total_len, read_len]
	(const boost::system::error_code& ec , const std::size_t bytes_to_transfered) {
			if (ec) {
				hander(ec, bytes_to_transfered);		//出现错误调用回调函数
				return;
			}
			if (read_len + bytes_to_transfered >= total_len) {
				hander(ec, read_len + bytes_to_transfered);		//读取长度超过总长度，调用回调函数
				return;
			}
			self->asyncReadLen(read_len + bytes_to_transfered, total_len, hander);  //未出现错误，读取长度不足，继续读取
		});
}

void CSession::HandlerWrite(const boost::system::error_code& error, std::shared_ptr<CSession> shared_self)
{
	try {
		auto self = shared_from_this();
		if (!error) {
			std::lock_guard<std::mutex> lock(_send_lock);
			std::cout << "send data " << _send_que.front()->_data+ HEAD_TOTAL_LEN<< std::endl;
			_send_que.pop();
			if (!_send_que.empty()) {
				auto& msgnode = _send_que.front();
				boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_total_len),
					std::bind(&CSession::HandlerWrite, this, std::placeholders::_1, shared_self));
			}
		}
		else {
			std::cout << "handle write failed, error is " << error.what() << std::endl;
			Close();
			//DealExceptionSession();
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception code : " << e.what() << std::endl;
	}
}

LogicNode::LogicNode(std::shared_ptr<CSession> session, std::shared_ptr<RecvNode> recvnode):_session(session) , _recvnode(recvnode)
{
}
