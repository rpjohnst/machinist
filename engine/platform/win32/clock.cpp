#include "clock.h"
#include <windows.h>

namespace machinist {

Clock::Clock() {
	reset();
}

void Clock::reset() {
	start = get_time();
}

double Clock::get_elapsed() {
	return get_time() - start;
}

double Clock::get_time() {
	DWORD ticks = GetTickCount();
	return (double)ticks / 1000;
}

void Clock::sleep(double time) {
	Sleep(time * 1000);
}

}
