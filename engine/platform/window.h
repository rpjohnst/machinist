#ifndef PLATFORM_WINDOW_H
#define PLATFORM_WINDOW_H

#if PLATFORM_WIN32
#	include <platform/win32/window.h>
#elif PLATFORM_XLIB
#	include <platform/xlib/window.h>
#endif



#endif
