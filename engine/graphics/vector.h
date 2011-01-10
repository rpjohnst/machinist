#ifndef GRAPHICS_VECTOR_H
#define GRAPHICS_VECTOR_H

template <class Type>
struct Vector {
	Vector(Type x = 0, Type y = 0) : x(x), y(y) {}
	Type x, y;
};

#endif
