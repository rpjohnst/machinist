#ifndef PLATFORM_WIN32_CLOCK_H
#define PLATFORM_WIN32_CLOCK_H

namespace machinist {

class Clock {
public:
	Clock();
	void reset();
	double get_elapsed();
	
	static double get_time();
	static void sleep(double time);
	
private:
	double start;
};

}

#endif
