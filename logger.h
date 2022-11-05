#pragma once
#include "LockQueue.h"
#include <iostream>
// ����� LOG_INFO("xxx %d %s", 20, "xxxx")
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \

#define LOG_ERR(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \

// ������־����
enum LogLevel
{
	INFO,  // ��ͨ��Ϣ
	ERROR, // ������Ϣ
};

// Mprpc����ṩ����־ϵͳ
class Logger
{
public:
	// ��ȡ��־�ĵ���
	static Logger& GetInstance();
	// ������־���� 
	void SetLogLevel(LogLevel level);
	// д��־
	void Log(std::string msg);
private:
	int m_loglevel; // ��¼��־����
	LockQueue<std::string>  m_lckQue; // ��־�������

	Logger();
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
};
