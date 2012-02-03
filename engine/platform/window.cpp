#include <platform/window.h>
#include <sstream>

namespace machinist {

void WindowBase::display() {
	if (framerate > 0) {
		double time = 1.0 / framerate - clock.get_elapsed();
		if (time > 0)
			Clock::sleep(time);
	}
	
	frame = clock.get_elapsed();
	clock.reset();
	
	input().swap_buffers();
	swap_buffers();
	
	std::ostringstream ss;
	ss << "fps: " << 1.0 / get_frame_time();
	set_caption(ss.str());
}

}
