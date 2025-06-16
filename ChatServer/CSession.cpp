#include "CSession.h"

CSession::CSession(boost::asio::io_context& ioc, CServer* server):_socket(ioc) , _server(server),_user_uid(0),
_b_close(false),_b_head_parse(false)
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
	_session_id = boost::uuids::to_string(a_uuid);
	_recv_head_node = std::make_shared<RecvNode>(HEAD_TOTAL_LEN);

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

std::shared_ptr<CSession> CSession::SharedSelf()
{
	return shared_from_this();
}
