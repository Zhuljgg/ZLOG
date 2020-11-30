#pragma once
/*这个类用来保存日志到文件中，自己用*/
#include<iostream>
#include<fstream>
#include<ctime>


class Zlog
{
public:
	enum class LOG_LEVEL
	{
		DEBUG = 0,
		FILE,
		PRINT,
		NOLOG
	};
	enum class OPEN_TYPE
	{
		ADD = 0,
		OVER
	};

	Zlog(LOG_LEVEL level = LOG_LEVEL::DEBUG) :_level(level) {};

	//print in screen
	template<typename T,typename M>
	void p(T tag, M msg, unsigned int codeline = 0);

	//write in file
	//tag,msg,time
	template<typename T, typename M>
	void w(T tag, M msg, unsigned int codeline = 0,
		OPEN_TYPE type = OPEN_TYPE::ADD, const char* filename = "loglog.txt");

private:
	/*默认log level，调试时最低*/
	LOG_LEVEL _level;
};



template<typename T, typename M>
void Zlog::p(T tag, M msg, unsigned int codeline)
{
	if (_level <= LOG_LEVEL::PRINT)
	{
		std::cout << "[" << codeline << "]" << " " << "[" << tag << "]" ":" << msg << std::endl;
	}
}

template<typename T, typename M>
void Zlog::w(T tag, M msg, unsigned int codeline,
	OPEN_TYPE type, const char* filename)
{
	if (_level <= LOG_LEVEL::FILE)
	{
		std::fstream file;
		if (type == OPEN_TYPE::ADD)
		{
			file.open(filename, std::ios::out | std::ios::app);
		}
		else
		{
			file.open(filename, std::ios::out | std::ios::trunc);
		}

		//time
		tm t;
		time_t tm = time(NULL);
		localtime_s(&t, &tm);
		//strftime
		file << t.tm_year + 1900 << '/' << t.tm_mon << '/' << t.tm_mday << '_'
			<< t.tm_hour << ':' << t.tm_min << ':' << t.tm_sec << ','
			<< "[" << codeline << "]" << " " << "[" << tag << "]" << ":" << msg << std::endl;
		file.close();
	}
	p(tag, msg, codeline);
}