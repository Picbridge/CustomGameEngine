/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Vector3D.h>
Purpose: <Define custom Vector3D class>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_2>
Author: <jihoon.bae>
Creation date: <09/07/2023>
--------------------------------------------------------*/
#pragma once
class Vector3D
{
public:

	float x, y, z;

	Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
	float Length();
	float Dot(const Vector3D& rhs);
	Vector3D Cross(const Vector3D& rhs);
	Vector3D Normalize();
	Vector3D Lerp(const Vector3D& rhs, float factor);

	Vector3D Translate(const Vector3D& translate);
	Vector3D Rotate(const Vector3D& axisAngle);
	Vector3D Scale(const Vector3D& scale);
	Vector3D Scale(const float percentage);

	Vector3D operator+(const Vector3D& rhs);
	void operator+=(const Vector3D& rhs);
	Vector3D operator-(const Vector3D& rhs);
	void operator-=(const Vector3D& rhs);
	Vector3D operator*(const float scalar);
	void operator*=(const float scalar);

private:
	Vector3D TransformMultiplication(const std::vector<std::vector<float>>& mat, std::vector<float>& current_vec);
};

