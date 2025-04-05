#pragma once
#include "Transform.h"

struct Vertex
{
public:
	Vertex()
		:vPoint(0,0,0),vNormal(0,0,0) {}
	Vertex(Point point, Point normal)
		:vPoint(point),vNormal(normal) {}
	~Vertex() {}
public:
	Point vPoint;
	Point vNormal;
};