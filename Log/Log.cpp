#include "Log.h"
#include <stdio.h>
#include <assert.h>
#include <windows.h>

FILE* g_LogFile = 0;

namespace LFC
{

namespace LOG
{
	LogLevel Log::m_eGobalLevel = LOG_VERBOSE;
	LogLevel Log::m_eCurrLevel = LOG_VERBOSE;
	LogTarget Log::m_eLogTarget = LOG_CONSOLE;

	void Log::setGobalLevel(LogLevel ll)
	{
		m_eGobalLevel = ll;
	}

	void Log::setLogTarget(LogTarget lt)
	{
		m_eLogTarget = lt;
	}

	void Log::e(const char* format, ...)
	{
		if (m_eGobalLevel < LOG_RELEASE)
		{
			va_list arg_ptr;
			va_start(arg_ptr, format);
			setCurrLogLevel(LOG_ERROR);
			log(format, arg_ptr);
			va_end(arg_ptr);
		}
	}

	void Log::w(const char* format, ...)
	{
		if (m_eGobalLevel < LOG_ERROR)
		{
			va_list arg_ptr;
			va_start(arg_ptr, format);
			setCurrLogLevel(LOG_WARNING);
			log(format, arg_ptr);
			va_end(arg_ptr);
		}
	}

	void Log::d(const char* format, ...)
	{
		if (m_eGobalLevel < LOG_WARNING)
		{
			va_list arg_ptr;
			va_start(arg_ptr, format);
			setCurrLogLevel(LOG_DEBUG);
			log(format, arg_ptr);
			va_end(arg_ptr);
		}
	}

	void Log::i(const char* format, ...)
	{
		if (m_eGobalLevel < LOG_DEBUG)
		{
			va_list arg_ptr;
			va_start(arg_ptr, format);
			setCurrLogLevel(LOG_INFO);
			log(format, arg_ptr);
			va_end(arg_ptr);
		}
	}

	void Log::v(const char* format, ...)
	{
		if (m_eGobalLevel < LOG_INFO)
		{
			va_list arg_ptr;
			va_start(arg_ptr, format);
			setCurrLogLevel(LOG_VERBOSE);
			log(format, arg_ptr);
			va_end(arg_ptr);
		}
	}

	void Log::log(const char* format, va_list arg_list)
	{
		switch (m_eLogTarget)
		{
		case LOG_CONSOLE:
			{
				setConsoleColor();
				vprintf_s(format, arg_list);
				resumeConsoleColor();
			}
			break;
		case LOG_DEBUG_OUTPUT:
			{
				char szBufPrefix[16] = {0};
				setOutputPrefix(szBufPrefix);

				char szBufLog[256] = {0};
				vsprintf_s(szBufLog, sizeof(szBufLog), format, arg_list);
				OutputDebugStringA(szBufPrefix);
				OutputDebugStringA(szBufLog);
			}
			break;
		case LOG_FILE:
			{
				char szBufPrefix[16] = {0};
				setOutputPrefix(szBufPrefix);

				errno_t err = fopen_s(&g_LogFile, "Log.txt", "a");
				assert(err == 0);
				fprintf_s(g_LogFile, szBufPrefix);
				vfprintf_s(g_LogFile, format, arg_list);
				fclose(g_LogFile);
			}
			break;

		default:
			break;
		}
	}

	void Log::setCurrLogLevel(LogLevel ll)
	{
		m_eCurrLevel = ll;
	}

	void Log::setConsoleColor()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole)
		{
			switch (m_eCurrLevel)
			{
			case LOG_VERBOSE:	// White
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
			case LOG_INFO:		// Blue
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY |
					FOREGROUND_BLUE);
				break;
			case LOG_DEBUG:		// Green
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY |
					FOREGROUND_GREEN);
				break;
			case LOG_WARNING:	// Yellow
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN);
				break;
			case LOG_ERROR:		// Red
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY |
					FOREGROUND_RED);
				break;

			default:
				break;
			}
		}	
	}
	
	void Log::resumeConsoleColor()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hConsole)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | 
				FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}

	void Log::setOutputPrefix(char* szBuf)
	{
		switch (m_eCurrLevel)
		{
		case LOG_VERBOSE:
			strcpy_s(szBuf, 16, "[VERBOSE] : ");
			break;
		case LOG_INFO:
			strcpy_s(szBuf, 16, "[INFO] : ");
			break;
		case LOG_DEBUG:
			strcpy_s(szBuf, 16, "[DEBUG] : ");
			break;
		case LOG_WARNING:
			strcpy_s(szBuf, 16, "[WARNING] : ");
			break;
		case LOG_ERROR:
			strcpy_s(szBuf, 16, "[ERROR] : ");
			break;

		default:
			break;
		}
	}
}

}

