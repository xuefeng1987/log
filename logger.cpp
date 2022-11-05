#include "logger.h"
#include <thread>
// ��ȡ��־�ĵ���
Logger& Logger::GetInstance()
{
	static Logger logger;
	return logger;
}

Logger::Logger()
{
	// ����ר�ŵ�д��־�߳�
	std::thread writeLogTask([&]() {
		for (;;)
		{
			// ��ȡ��ǰ�����ڣ�Ȼ��ȡ��־��Ϣ��д����Ӧ����־�ļ����� a+
			time_t now = time(nullptr);
			tm nowtm;
		    localtime_s(&nowtm,&now);

			char file_name[128];
			sprintf_s(file_name, "%d-%d-%d-log.txt", nowtm.tm_year + 1900, nowtm.tm_mon + 1, nowtm.tm_mday);

			FILE* pf;
			errno_t  ret= fopen_s(&pf,file_name, "a+");
			if (pf == nullptr)
			{
				std::cout << "logger file : " << file_name << " open error!" << std::endl;
				exit(EXIT_FAILURE);
			}

			std::string msg = m_lckQue.Pop();

			char time_buf[128] = { 0 };
			sprintf_s(time_buf, "%d:%d:%d =>[%s] ",
				nowtm.tm_hour,
				nowtm.tm_min,
				nowtm.tm_sec,
				(m_loglevel == INFO ? "info" : "error"));
			msg.insert(0, time_buf);
			msg.append("\n");
			fputs(msg.c_str(), pf);
			fclose(pf);
		}
		});
	// ���÷����̣߳��ػ��߳�
	writeLogTask.detach();
}

// ������־���� 
void Logger::SetLogLevel(LogLevel level)
{
	m_loglevel = level;
}

// д��־�� ����־��Ϣд��lockqueue����������
void Logger::Log(std::string msg)
{
	m_lckQue.Push(msg);
}
