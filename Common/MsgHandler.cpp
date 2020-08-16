// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#include <string>

#include "ppsspp_config.h"

#include "Common.h"
#include "Common/Log.h"
#include "StringUtils.h"
#include "util/text/utf8.h"

#ifdef PPSSPP_PLATFORM(WINDOWS)
#include "CommonWindows.h"
#endif

bool ShowAssertDialog(const char *file, int line, const char* format, ...) {
	// Read message and write it to the log
	char text[2048];
	const char *caption = "Critical";
	va_list args;
	va_start(args, format);
	CharArrayFromFormatV(text, sizeof(text)-1, format, args);
	va_end(args);
	// Normal logging (will also log to Android log)
	ERROR_LOG(SYSTEM, "(%s:%d) %s: %s", file, line, caption, text);

#if defined(USING_WIN_UI)
	int msgBoxStyle = MB_ICONINFORMATION | MB_YESNO;
	std::wstring wtext = ConvertUTF8ToWString(text) + L"\n\nTry to continue?";
	std::wstring wcaption = ConvertUTF8ToWString(caption);
	OutputDebugString(wtext.c_str());
	return IDYES == MessageBox(0, wtext.c_str(), wcaption.c_str(), msgBoxStyle);
#else
	OutputDebugStringUTF8(text);
	return false;
#endif
}
