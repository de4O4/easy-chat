#pragma once
#include <string>
#include "const.h"
#include <boost/asio.hpp>
#include <iostream>

class LogicSystem;
class MsgNode
{
public:
	MsgNode(short maxlen);
	~MsgNode();
	void clear();

	short _cur_len; // 当前消息长度
	short _total_len; // 总消息长度
	char* _data;
};

class RecvNode :public MsgNode
{
	friend class LogicSystem;
public:
	RecvNode(short maxlen, short msg_id);
private:
	short _msg_id;
};

class SendNode :public MsgNode
{
	friend class LogicSystem;
public:
	SendNode(const char* msg, short maxlen, short msg_id);
private:
	short _msg_id;
};

