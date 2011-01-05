#ifndef GRAPHICS_RECT_H
#define GRAPHICS_RECT_H

template <class Type>
struct Rect {
	Rect(Type l, Type t, Type w, Type h) : left(l), top(t), width(w), height(h) {}
	Type left, top, width, height;
};

#endif
