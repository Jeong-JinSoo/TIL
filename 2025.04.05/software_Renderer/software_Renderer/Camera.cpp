#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	ClacProjectionMatrix();
	ClacViewMatrix();
}

void Camera::LookAt(Point camPos, Point target, Point worldUp)
{
	eye = camPos;
	at = target;
	up = worldUp;
}

void Camera::CreatePerspectiveFrustum(float fov, float aspect, float near, float far_)
{
	this->_fovy = fov;
	this->_aspect = aspect;
	this->_near = near;
	this->_far = far_;
}

void Camera::SetViewPort(float hight, float length)
{
	windowHight = hight;
	windowLength = length;
	float min = 0.0;	//depthÀÇ ÃÖ¼Ú°ª
	float max = 1.0;	//depthÀÇ ÃÖ´ñ°ª
	float x = 100;		//left
	float y = 100;		//top

	Matrix result;

	result = {
		  length/2,			  0,		  0,			0
	,			 0,	 -(hight/2),	 	  0,			0
	, 			 0,			  0,	max-min,			0
	, x+(length/2),	y+(hight/2),		min,			1
	};

	viewPort = result;
}

void Camera::ClacProjectionMatrix()
{
	Matrix result;
	float k = 1.0f / tan(_fovy / 2.0f);
	float fmn = _far - _near;
	    

	result = {
		k/_aspect,			0,								0,			0
	,			0,			k,								0,			0
	,			0,			0,					-( _far/ fmn),			-1
	,			0,			0,				-(_far*_near/fmn),			0
	};

	proj = result;
}
                   

void Camera::ClacViewMatrix()
{
	Matrix result;

   	Point n = Point::Normalize(eye-at); // Z
   	Point u = Point::Normalize(Point::CrossR(n,up)); // Y
   	Point v = Point::CrossR(u, n); // X

	//result = {
	//v.x,		u.x,		n.x,		0,
	//v.y,		u.y,		n.y,		0,
	//v.z,		u.z,		n.z,		0,
	//-(Point::Dot(eye, v)),	-(Point::Dot(eye, u)),	-(Point::Dot(eye, n)),	1
	//};

	//Point n(0.0f, 0.0f, 1.0f);
	//Point u(1.0f, 0.0f, 0.0f);
	//Point v(0.0f, 1.0f, 0.0f);

	result = {
						 u.x,					   v.x,						   n.x,		0
	,					 u.y,					   v.y,						   n.y,		0
	,					 u.z,					   v.z,						   n.z,		0
	, -(Point::Dot(u , eye)),	-(Point::Dot(v , eye)),		-(Point::Dot(n , eye)),		1
	};


// 	result = {
// 						 v.x,					   v.y,						   v.z,		-(Point::Dot(eye , v))
// 	,					 u.x,					   u.y,						   u.z,		-(Point::Dot(eye , u))
// 	,					 n.x,					   n.y,						   n.z,		-(Point::Dot(eye , n))
// 	,					   0,						 0,					 		 0,							1
// 	};


	view = result;

//  	view =
//  	{
//  		1.0f, 0.0f, 0.0f, -eye.x,
//  		0.0f, 1.0f, 0.0f, -eye.y,
//  		0.0f, 0.0f, 1.0f, -eye.z,
//  		0.0f, 0.0f, 0.0f, 1.0f
//  	};
	return;
}

Matrix Camera::GetView()
{
	return view;
}

Matrix Camera::GetProj()
{
	return proj;
}

Matrix Camera::GetViewPort()
{
	return viewPort;
}