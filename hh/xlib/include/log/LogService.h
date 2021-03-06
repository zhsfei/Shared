#pragma once

#include "../include/define/define.h"
#include "../include/CircularQueue.h"
#include <thread>
#include <boost/thread.hpp>

#define LOG_BUF_LEN 1024*100		// 每条日志的大小
//#define FOLDERNAME "log"			// 存放日志文件夹名

#pragma warning (push)

#pragma warning (disable: 4251)

namespace xlib
{
	class XDLL LogService2
	{
	public:
		LogService2(const std::string& logname);
		~LogService2(void);

	public:
		/**
		* @brief		记录一条日志
		*/
		void LogMessage(const char* format, ...);


		/**
		* @brief		设置文件大小限制
		* @param[in]	maxsize[int32] : 最大文件限制
		* @return		void
		* @remarks
		*/
		inline void SetMaxSize(int32 maxsize);

	protected:

		/**
		* @brief		初始化log目录
		*/
		void init();

		/**
		* @brief		产生一个日志文件
		*/
		bool createLogFile();

		void ThreadProc(void);

	private:
		std::string m_LogName;				// 日志文件名
		FILE* m_hFile;					// 当前要写入的文件指针
		int64 m_MaxFileSize;			// 日志文件当前的容量
		int64 m_CurFileSize;			// 当前文件大小

		boost::mutex m_Mutex;

		char* _pszLog;

		bool m_bActive;
		CCircularQueue<std::string> m_CQueue;	//循环队列
		std::thread m_thread;
	};


}

#pragma warning (pop)