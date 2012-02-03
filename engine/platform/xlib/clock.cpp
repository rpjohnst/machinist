#include "clock.h"
#include <sys/time.h>
#include <unistd.h>

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
	timeval time = { 0, 0 };
	gettimeofday(&time, NULL);
	
	return time.tv_sec + time.tv_usec / 1000000.0;
}

void Clock::sleep(double time) {
	usleep(static_cast<unsigned long>(time * 1000000));
}

}
