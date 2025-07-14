#include "MsgNode.h"

MsgNode::MsgNode(short maxlen):_cur_len(0),_total_len(maxlen)
{
	_data = new char[maxlen + 1];
	_data[_total_len] = '\0'; // Null-terminate the string
}

MsgNode::~MsgNode()
{
	if(_data) {
		delete[] _data;
		_data = nullptr;
	}
	std::cout << " msgnode destruct!" << std::endl;
}

void MsgNode::clear() {
	memset(_data, 0, _total_len);
	_cur_len = 0;
}

RecvNode::RecvNode(short maxlen, short msg_id):_msg_id(msg_id),MsgNode(maxlen)
{

}

SendNode::SendNode(const char* msg, short maxlen, short msg_id):_msg_id(msg_id), MsgNode(maxlen + HEAD_TOTAL_LEN)
{
	short msg_id_net = boost::asio::detail::socket_ops::host_to_network_short(msg_id);
	memcpy(_data, &msg_id_net, HEAD_ID_LEN);
	short msg_len_net = boost::asio::detail::socket_ops::host_to_network_short(maxlen);
	memcpy(_data + HEAD_ID_LEN, &msg_len_net, HEAD_DATA_LEN);
	memcpy(_data + HEAD_TOTAL_LEN, msg, maxlen);
}
