#include "Transform.h"

Transform::Transform()
	:posX(0),posY(0),posZ(0)
	,rotX(0),rotY(0),rotZ(0)
	,scalX(1),scalY(1),scalZ(1)
	,parent(nullptr)
{
	transformMatrix.ResetMartix();
}

Transform::~Transform()
{
}

///////////////////////////////////////////////////////////////////////////////////////////
void Transform::Update()
{
	Matrix result;
	result.ResetMartix();
	result = Translate() * result;
	result = Rotation() * result;
	result = Scale() * result;
	transformMatrix = result;

	transformMatrix = TransformHierarchy();

}

Matrix Transform::TransformHierarchy()
{
	if (parent == nullptr)
	{
		return this->transformMatrix;
	}
	
	else
	{
		return this->transformMatrix * TransformHierarchy();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
void Transform::SetParent(Transform* parentTransform)
{
	parent = parentTransform;
}

void Transform::SetPosition(float posx, float posy, float posz)
{
	posX = posx;
	posY = posy;
	posZ = posz;
}

void Transform::SetRotation(float rotx, float roty, float rotz)
{
	rotX = PI(rotx);
	rotY = PI(roty);
	rotZ = PI(rotz);
}

void Transform::SetScale(float scalx, float scaly, float scalz)
{
	scalX = scalx;
	scalY = scaly;
	scalZ = scalz;
}

Matrix Transform::GetTransformMatrix()
{
	return transformMatrix;
}

Point Transform::PointmultiplyMatrix(const Point& m)
{
	return transformMatrix.PointmultiplyMatrix(m);
}

Point Transform::PointPlusMatrix(const Point& m)
{
	return transformMatrix.PointPlusMatrix(m);
}

Point Transform::PointMinusMatrix(const Point& m)
{
	return transformMatrix.PointMinusMatrix(m);
}

///////////////////////////////////////////////////////////////////////////////////////////
Matrix Transform::Translate()
{
	Matrix result;
	result = {
		   1,		0,		0,		0,
		   0,		1,		0,		0,
		   0,		0,		1,		0,
		posX,	 posY,	 posZ,		1
	};

	return result;
}

Matrix Transform::Rotation()
{
	Matrix rotx;
	rotx = {
		   1,			0,			0,			0,
		   0,	cos(rotX),	sin(rotX),			0,
		   0,  -sin(rotX),	cos(rotX),			0,
		   0,			0,			0,			1
	};

	Matrix roty;
	roty = {
   cos(rotY),			0, -sin(rotY),			0,
		   0,			1,			0,			0,
   sin(rotY),			0,	cos(rotY),			0,
		   0,			0,			0,			1
	};

	Matrix rotz;
	rotz = {
   cos(rotZ),	sin(rotZ),			0,			0,
  -sin(rotZ),   cos(rotZ),			0,			0,
		   0,			0,			1,			0,
		   0,			0,			0,			1
	};

	Matrix result = rotx * roty * rotz;

	return result;
}

Matrix Transform::RotationQ(double angle, double ax, double ay, double az)
{
	Matrix result;

	return result;
}

Matrix Transform::Scale()
{
	Matrix result;
	result = {
   scalX,		0,		0,		0,
	   0,	scalY,		0,		0,
	   0,		0,	scalZ,		0,
	   0,		0,		0,		1
	};

	return result;
}