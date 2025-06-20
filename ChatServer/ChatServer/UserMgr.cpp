#include "UserMgr.h"
#include "CSession.h"

UserMgr::~UserMgr()
{
	_uid_to_session.clear();
}

std::shared_ptr<CSession> UserMgr::GetSession(int uid)
{
	std::lock_guard<std::mutex> lock(_session_mtx);
	auto it = _uid_to_session.find(uid);
	if (it != _uid_to_session.end()) {
		return it->second;
	}
	return nullptr;
}

void UserMgr::SetUserSession(int uid, std::shared_ptr<CSession> session)
{
	std::lock_guard<std::mutex> lock(_session_mtx);
	_uid_to_session[uid] = session;
}

void UserMgr::RmvUserSession(int uid, std::string session_id)
{
	{
		std::lock_guard<std::mutex> lock(_session_mtx);
		auto it = _uid_to_session.find(uid);
		if (it == _uid_to_session.end()) {
			return;
		}
		auto sess_id = it->second->GetSessionid();
		if (session_id != sess_id) {
			return;
		}
		_uid_to_session.erase(uid);
	}
}

UserMgr::UserMgr() {

}