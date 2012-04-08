/*	
	Copyright (C) 2012-2012 Leo Peng
	This is a part of LFC (Leo's Fantasy Codes)
	see more : http://www.leosfantasyworld.net

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/ 

#ifndef __LFC_LOG_H__
#define __LFC_LOG_H__

#include <stdarg.h>

namespace LFC
{

namespace LOG
{
	typedef enum {LOG_VERBOSE=0, LOG_INFO, LOG_DEBUG, LOG_WARNING, LOG_ERROR, LOG_RELEASE} LogLevel;
	typedef enum {LOG_CONSOLE, LOG_DEBUG_OUTPUT, LOG_FILE} LogTarget;	

	class Log
	{
	public:
		static void e(const char* format, ...);
		static void w(const char* format, ...);
		static void d(const char* format, ...);
		static void i(const char* format, ...);
		static void v(const char* format, ...);
		
	public:
		static void setGobalLevel(LogLevel ll);
		static void setLogTarget(LogTarget lt);
		
	private:
		static void log(const char* format, va_list arg_list);

		static void setConsoleColor();
		static void resumeConsoleColor();
		static void setOutputPrefix(char* szBuf);
		static void setCurrLogLevel(LogLevel ll);

		static LogLevel m_eGobalLevel;
		static LogLevel m_eCurrLevel;
		static LogTarget m_eLogTarget;
	};
}

}

#endif