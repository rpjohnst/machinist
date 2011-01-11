#ifndef PLATFORM_CLOCK_H
#define PLATFORM_CLOCK_H

#if PLATFORM_WIN32
#	include <platform/win32/clock.h>
#elif PLATFORM_XLIB
#	include <platform/xlib/clock.h>
#endif

#endif
