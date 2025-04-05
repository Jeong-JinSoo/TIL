#include "GraphicsClass.h"

Coner::Coner()
{
		//vertex[0] = Vertex(Point( 1, -1,  1),	Point());
		//vertex[1] = Vertex(Point(-1, -1,  1),	Point());
		//vertex[2] = Vertex(Point( 1, -1, -1),	Point());
		//vertex[3] = Vertex(Point(-1, -1, -1),	Point());
		//vertex[4] = Vertex(Point( 1, 1,  1),	Point());
		//vertex[5] = Vertex(Point(-1, 1,  1),	Point());
		//vertex[6] = Vertex(Point( 1, 1, -1),	Point());
		//vertex[7] = Vertex(Point(-1, 1, -1),	Point());

		vertex[0] = Vertex(Point( 1,  1, -1),	Point());
		vertex[1] = Vertex(Point(-1,  1, -1),	Point());
		vertex[2] = Vertex(Point( 1, -1, -1),	Point());
		vertex[3] = Vertex(Point(-1, -1, -1),	Point());
		vertex[4] = Vertex(Point( 1,  1,  1),	Point());
		vertex[5] = Vertex(Point(-1,  1,  1),	Point());
		vertex[6] = Vertex(Point( 1, -1,  1),	Point());
		vertex[7] = Vertex(Point(-1, -1,  1),	Point());

		index[0] = 4, index[1] = 0,  index[2] = 2;
		index[3] = 4, index[4] = 2,  index[5] = 6;
		index[6] = 5, index[7] = 1,  index[8] = 0;
		index[9] = 5, index[10] = 0, index[11] = 4;
		index[12] = 7, index[13] = 3, index[14] = 1;
		index[15] = 7, index[16] = 1, index[17] = 5;
		index[18] = 6, index[19] = 2, index[20] = 3;
		index[21] = 6, index[22] = 3, index[23] = 7;
		index[24] = 5, index[25] = 4, index[26] = 6;
		index[27] = 5, index[28] = 6, index[29] = 7;
		index[30] = 0, index[31] = 1, index[32] = 3;
		index[33] = 0, index[34] = 3, index[35] = 2;

		transform.SetPosition(0, 0, 0);
		transform.SetRotation(0, 0, 0);
		transform.SetScale(1, 1, 1 );
}

void Coner::Update(Matrix camView, Matrix camproj, Matrix viewport)
{
	Matrix result =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	transform.Update();
	view = camView;
	proj = camproj;
	this->viewport = viewport;
	finalTransform = transform.GetTransformMatrix() * view * proj * viewport;
}

Point Coner::UpdateVertex(int index)
{
	Point result;

	if (index == -1)
	{
		result = finalTransform.PointmultiplyMatrix(result);
		return result;
	}

	//result = transform.GetTransformMatrix().PointmultiplyMatrix(vertex[index].vPoint);
	result = finalTransform.PointmultiplyMatrix(vertex[index].vPoint);



	return result;
}

int Coner::ReturnIndex(int i)
{
	return index[i];
}
