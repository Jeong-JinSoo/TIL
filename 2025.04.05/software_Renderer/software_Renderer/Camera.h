#pragma once
#include "Transform.h"

class Camera
{
public:
	Camera();
	~Camera();
public:
	void Update();

	void LookAt(Point camPos, Point target, Point worldUp);	// ī�޶� �⺻ ����

	void CreatePerspectiveFrustum(float fov, float aspect, float near, float far_);	//����ü ����
	void SetViewPort(float hight, float length);

	void ClacViewMatrix();
	void ClacProjectionMatrix();

	Matrix GetView();
	Matrix GetProj();
	Matrix GetViewPort();
private:
	Point eye;
	Point at;
	Point up;

	float _fovy;		//�þ߰�
	float _aspect;		//��Ⱦ��
	float _near;		//������������ �Ÿ�
	float _far;			//�Ĺ��������ǰŸ�

	float windowHight;
	float windowLength;
	
	Matrix view;
	Matrix proj;
	Matrix viewPort;
};

