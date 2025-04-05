#pragma once
#include "Matrix.hpp"

#define PI(x) x *= 0.0174533

class Transform
{
public:
	Transform();
	~Transform();
public:
	void Update(); //�� �����Ӹ��� ������Ʈ �Ǵ� �Լ�. �� �Լ� ���ο��� TRS������ ����ȴ�.
	void SetParent(Transform* parentTransform); // �ش� Ʈ�������� �θ� ����.
	void SetPosition(float posx, float posy, float posz);	// position���� ����. ���� ��ȯ����� ����ϴ°��� �ƴԿ� ����
	void SetRotation(float rotx, float roty, float rotz);	// rotation���� ����. ������ �ƴ� ������ ���. ���� ��ȯ����� ����ϴ°��� �ƴԿ� ����
	void SetScale(float scalx, float scaly, float scalz);	// scale���� ����. ���� ��ȯ����� ����ϴ°��� �ƴԿ� ����
	Matrix GetTransformMatrix();

public:
	Point PointmultiplyMatrix(const struct Point& m);
	Point PointPlusMatrix(const struct Point& m);
	Point PointMinusMatrix(const struct Point& m);
private:
	Matrix TransformHierarchy(); // ���� ������ �θ� �ִٸ� �θ��� matrix�� �����ͼ� �����ϵ��� �ϴ� �Լ�. ��ͷ� ����
	Matrix Translate();
	Matrix Rotation();
	Matrix Scale();
	Matrix RotationQ(double angle, double ax, double ay, double az);
private:
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	float scalX, scalY, scalZ;

	Matrix transformMatrix;
	Transform* parent;
};
