#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

namespace machinist {

class EventHandler {
protected:
	virtual void key_press(int) = 0;
	virtual void key_release(int) = 0;
	virtual void quit() = 0;
};

}

#endif
