#pragma once
#include "const.h"

struct SectionInfo {
	SectionInfo() {

	}
	std::map<std::string, std::string> _section_datas;
	~SectionInfo() {
		_section_datas.clear();
	}
	SectionInfo(const SectionInfo& src) {			//重写拷贝构造函数
		_section_datas = src._section_datas;
	}
	SectionInfo& operator =(const SectionInfo& src) {			//拷贝赋值运算符：防止自赋值，复制源对象的_section_datas
		if (&src == this) {
			return *this;
		}
		this->_section_datas = src._section_datas;
	}
	std::string  operator[](const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}
		// 这里可以添加一些边界检查  
		return _section_datas[key];
	}
};


class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_map.clear();
	}
	SectionInfo operator[](const std::string& section) {
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();
		}
		return _config_map[section];
	}


	ConfigMgr& operator=(const ConfigMgr& src) {
		if (&src == this) {
			return *this;
		}

		this->_config_map = src._config_map;
	};

	ConfigMgr(const ConfigMgr& src) {
		this->_config_map = src._config_map;
	}

	static ConfigMgr& Instance();
private:
	ConfigMgr();
	// 存储section和key-value对的map  
	std::map<std::string, SectionInfo> _config_map;
};

