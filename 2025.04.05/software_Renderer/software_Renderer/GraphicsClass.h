#pragma once
#include "RenderStruct.hpp"

//사면체 구조체
class Coner
{
public:
	Coner();
	~Coner() {}

	void Update(Matrix camView, Matrix camproj, Matrix viewport);
	Point UpdateVertex(int index);
	int ReturnIndex(int i);

	Transform transform;
	Vertex vertex[8];
	unsigned int index[36];

	Matrix view;
	Matrix proj;
	Matrix viewport;

	Matrix finalTransform;
};

