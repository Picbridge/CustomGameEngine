/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Matrix3D.cpp>
Purpose: <Matrix3D class function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_2>
Author: <jihoon.bae>
Creation date: <09/11/2023>
--------------------------------------------------------*/
#include "pch.h"

Matrix3D::Matrix3D(const std::vector<std::vector<float>>& matrix)
{
	data = matrix;
}

Matrix3D::Matrix3D() {
	data.push_back({ 1.0f, 0.0f, 0.0f });
	data.push_back({ 0.0f, 1.0f, 0.0f });
	data.push_back({ 0.0f, 0.0f, 1.0f });
}

Matrix3D Matrix3D::IdentityMatrix()
{
	return Matrix3D();
}

Matrix3D Matrix3D::Transpose()
{
	Matrix3D res;
	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j <= i; j++)
		{
			res.data[i][j] = this->data[j][i];
			res.data[j][i] = this->data[i][j];
		}
	}
	return res;
}

Matrix3D Matrix3D::Inverse()
{
	Matrix3D res;
	auto det_inv = Determinant();

	det_inv == 0 ? (throw std::invalid_argument("Matrix is not invertible")) : (det_inv = 1 / det_inv);
		
	res.data[0][0] = (this->data[1][1] * this->data[2][2] - this->data[1][2] * this->data[2][1]) * det_inv;
	res.data[0][1] = (this->data[0][2] * this->data[2][1] - this->data[0][1] * this->data[2][2]) * det_inv;
	res.data[0][2] = (this->data[0][1] * this->data[1][2] - this->data[0][2] * this->data[1][1]) * det_inv;
	res.data[1][0] = (this->data[1][2] * this->data[2][0] - this->data[1][0] * this->data[2][2]) * det_inv;
	res.data[1][1] = (this->data[0][0] * this->data[2][2] - this->data[0][2] * this->data[2][0]) * det_inv;
	res.data[1][2] = (this->data[0][2] * this->data[1][0] - this->data[0][0] * this->data[1][2]) * det_inv;
	res.data[2][0] = (this->data[1][0] * this->data[2][1] - this->data[1][1] * this->data[2][0]) * det_inv;
	res.data[2][1] = (this->data[0][1] * this->data[2][0] - this->data[0][0] * this->data[2][1]) * det_inv;
	res.data[2][2] = (this->data[0][0] * this->data[1][1] - this->data[0][1] * this->data[1][0]) * det_inv;

	return res;

	return Matrix3D();
}

Matrix3D Matrix3D::operator+(const Matrix3D& rhs)
{
	Matrix3D res;

	res.data[0][0] = this->data[0][0] + rhs.data[0][0];
	res.data[0][1] = this->data[0][1] + rhs.data[0][1];
	res.data[0][2] = this->data[0][2] + rhs.data[0][2];
	res.data[1][0] = this->data[1][0] + rhs.data[1][0];
	res.data[1][1] = this->data[1][1] + rhs.data[1][1];
	res.data[1][2] = this->data[1][2] + rhs.data[1][2];
	res.data[2][0] = this->data[2][0] + rhs.data[2][0];
	res.data[2][1] = this->data[2][1] + rhs.data[2][1];
	res.data[2][2] = this->data[2][2] + rhs.data[2][2];

	return res;
}

void Matrix3D::operator+=(const Matrix3D& rhs)
{
	this->data[0][0] += rhs.data[0][0];
	this->data[0][1] += rhs.data[0][1];
	this->data[0][2] += rhs.data[0][2];
	this->data[1][0] += rhs.data[1][0];
	this->data[1][1] += rhs.data[1][1];
	this->data[1][2] += rhs.data[1][2];
	this->data[2][0] += rhs.data[2][0];
	this->data[2][1] += rhs.data[2][1];
	this->data[2][2] += rhs.data[2][2];

	return;
}

Matrix3D Matrix3D::operator-(const Matrix3D& rhs)
{
	Matrix3D res;

	res.data[0][0] = this->data[0][0] - rhs.data[0][0];
	res.data[0][1] = this->data[0][1] - rhs.data[0][1];
	res.data[0][2] = this->data[0][2] - rhs.data[0][2];
	res.data[1][0] = this->data[1][0] - rhs.data[1][0];
	res.data[1][1] = this->data[1][1] - rhs.data[1][1];
	res.data[1][2] = this->data[1][2] - rhs.data[1][2];
	res.data[2][0] = this->data[2][0] - rhs.data[2][0];
	res.data[2][1] = this->data[2][1] - rhs.data[2][1];
	res.data[2][2] = this->data[2][2] - rhs.data[2][2];

	return res;
}

void Matrix3D::operator-=(const Matrix3D& rhs)
{
	this->data[0][0] -= rhs.data[0][0];
	this->data[0][1] -= rhs.data[0][1];
	this->data[0][2] -= rhs.data[0][2];
	this->data[1][0] -= rhs.data[1][0];
	this->data[1][1] -= rhs.data[1][1];
	this->data[1][2] -= rhs.data[1][2];
	this->data[2][0] -= rhs.data[2][0];
	this->data[2][1] -= rhs.data[2][1];
	this->data[2][2] -= rhs.data[2][2];

	return;
}

Matrix3D Matrix3D::operator*(const float scalar)
{
	Matrix3D res;

	res.data[0][0] = this->data[0][0] * scalar;
	res.data[0][1] = this->data[0][1] * scalar;
	res.data[0][2] = this->data[0][2] * scalar;
	res.data[1][0] = this->data[1][0] * scalar;
	res.data[1][1] = this->data[1][1] * scalar;
	res.data[1][2] = this->data[1][2] * scalar;
	res.data[2][0] = this->data[2][0] * scalar;
	res.data[2][1] = this->data[2][1] * scalar;
	res.data[2][2] = this->data[2][2] * scalar;

	return res;
}

void Matrix3D::operator*=(const float scalar)
{
	this->data[0][0] *= scalar;
	this->data[0][1] *= scalar;
	this->data[0][2] *= scalar;
	this->data[1][0] *= scalar;
	this->data[1][1] *= scalar;
	this->data[1][2] *= scalar;
	this->data[2][0] *= scalar;
	this->data[2][1] *= scalar;
	this->data[2][2] *= scalar;

	return;
}

Matrix3D Matrix3D::operator*(const Matrix3D& rhs)
{
	Matrix3D res;

	res.data[0][0] = 
		this->data[0][0] * rhs.data[0][0] +
		this->data[0][1] * rhs.data[1][0] + 
		this->data[0][2] * rhs.data[2][0];
	res.data[0][1] =
		this->data[0][0] * rhs.data[0][1] +
		this->data[0][1] * rhs.data[1][1] +
		this->data[0][2] * rhs.data[2][1];
	res.data[0][2] =
		this->data[0][0] * rhs.data[0][2] +
		this->data[0][1] * rhs.data[1][2] +
		this->data[0][2] * rhs.data[2][2];
	res.data[1][0] = 
		this->data[1][0] * rhs.data[0][0] +
		this->data[1][1] * rhs.data[1][0] +
		this->data[1][2] * rhs.data[2][0];
	res.data[1][1] =
		this->data[1][0] * rhs.data[0][1] +
		this->data[1][1] * rhs.data[1][1] +
		this->data[1][2] * rhs.data[2][1];
	res.data[1][2] = 
		this->data[1][0] * rhs.data[0][2] +
		this->data[1][1] * rhs.data[1][2] +
		this->data[1][2] * rhs.data[2][2];
	res.data[2][0] =
		this->data[2][0] * rhs.data[0][0] +
		this->data[2][1] * rhs.data[1][0] +
		this->data[2][2] * rhs.data[2][0];
	res.data[2][1] =
		this->data[2][0] * rhs.data[0][1] +
		this->data[2][1] * rhs.data[1][1] +
		this->data[2][2] * rhs.data[2][1];
	res.data[2][2] =
		this->data[2][0] * rhs.data[0][2] +
		this->data[2][1] * rhs.data[1][2] +
		this->data[2][2] * rhs.data[2][2];

	return res;
}

//Vector3D is assumed as transposed vector
Vector3D Matrix3D::operator*(const Vector3D& rhs)
{
	Vector3D res;

	res.x =
		this->data[0][0] * rhs.x +
		this->data[0][1] * rhs.y +
		this->data[0][2] * rhs.z;
	res.y =				   
		this->data[1][0] * rhs.x +
		this->data[1][1] * rhs.y +
		this->data[1][2] * rhs.z;
	res.z =				   
		this->data[2][0] * rhs.x +
		this->data[2][1] * rhs.y +
		this->data[2][2] * rhs.z;

	return res;
}

float Matrix3D::Determinant()
{
	return this->data[0][0] * (this->data[1][1] * this->data[2][2] - this->data[1][2] * this->data[2][1])
		 - this->data[0][1] * (this->data[1][0] * this->data[2][2] - this->data[1][2] * this->data[2][0])
		 + this->data[0][2] * (this->data[1][0] * this->data[2][1] - this->data[1][1] * this->data[2][0]);
}
