/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Matrix3D.h>
Purpose: <Matrix3D class function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_2>
Author: <jihoon.bae>
Creation date: <09/11/2023>
--------------------------------------------------------*/
#pragma once
class Matrix3D
{
public:
	std::vector<std::vector<float>> data;
	
	Matrix3D(const std::vector<std::vector<float>>& matrix);
	Matrix3D();

	Matrix3D IdentityMatrix();
	Matrix3D Transpose();
	Matrix3D Inverse();

	Matrix3D operator+(const Matrix3D& rhs);
	void operator+=(const Matrix3D& rhs);
	Matrix3D operator-(const Matrix3D& rhs);
	void operator-=(const Matrix3D& rhs);
	Matrix3D operator*(const float scalar);
	void operator*=(const float scalar);
	Matrix3D operator*(const Matrix3D& rhs);
	Vector3D operator*(const Vector3D& rhs);
private:
	float Determinant();
};

