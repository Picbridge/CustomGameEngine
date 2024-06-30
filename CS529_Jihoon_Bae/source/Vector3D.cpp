/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Vector3D.cpp>
Purpose: <Vector3D class function definition>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_2>
Author: <jihoon.bae>
Creation date: <09/07/2023>
--------------------------------------------------------*/
#include "pch.h"

float Vector3D::Length()
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector3D::Dot(const Vector3D& rhs)
{
	return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
}

Vector3D Vector3D::Cross(const Vector3D& rhs)
{
	return Vector3D((this->y * rhs.z) - (this->z * rhs.y),
					(this->z * rhs.x) - (this->x * rhs.z),
					(this->x * rhs.y) - (this->y * rhs.x));
}

Vector3D Vector3D::Normalize()
{
	float length = Length();
	
	if (length == 0)
		return Vector3D(0, 0, 0);

	return Vector3D(this->x / length, this->y / length, this->z / length);
}

Vector3D Vector3D::Lerp(const Vector3D& rhs, float factor)
{
	return Vector3D(this->x + (factor * (rhs.x - this->x)),
					this->y + (factor * (rhs.y - this->y)),
					this->z + (factor * (rhs.z - this->z)));
}

Vector3D Vector3D::Translate(const Vector3D& translate)
{
	std::vector<std::vector<float>> translation_matrix = {
		{ 1.0f, 0.0f, 0.0f, translate.x },
		{ 0.0f, 1.0f, 0.0f, translate.y },
		{ 0.0f, 0.0f, 1.0f, translate.z },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	std::vector<float> current_vec = { this->x, this->y, this->z, 1.0f };

	return this->TransformMultiplication(translation_matrix, current_vec);
}

Vector3D Vector3D::Rotate(const Vector3D& axisAngle)
{
	float x_in_rad = axisAngle.x * (PI / 180.0f);
	float y_in_rad = axisAngle.y * (PI / 180.0f);
	float z_in_rad = axisAngle.z * (PI / 180.0f);

	std::vector<std::vector<float>> rotation_matrix = {
		{std::cos(z_in_rad) * std::cos(y_in_rad), 
		 std::cos(z_in_rad) * std::sin(y_in_rad) * std::sin(x_in_rad) - (std::sin(z_in_rad) * std::cos(x_in_rad)),
		 std::cos(z_in_rad) * std::sin(y_in_rad) * std::cos(x_in_rad) + std::sin(z_in_rad) * std::sin(x_in_rad)},
		{std::sin(z_in_rad) * std::cos(y_in_rad),
		 std::sin(z_in_rad) * std::sin(y_in_rad) * std::sin(x_in_rad) + std::cos(z_in_rad) * std::cos(x_in_rad),
		 std::sin(z_in_rad) * std::sin(y_in_rad) * std::cos(x_in_rad) - std::cos(z_in_rad) * std::sin(x_in_rad)},
		{-std::sin(y_in_rad), std::cos(y_in_rad) * std::sin(x_in_rad),  std::cos(y_in_rad) * std::cos(x_in_rad)}
	};

	std::vector<float> current_vec = { this->x, this->y, this->z };

	return this->TransformMultiplication(rotation_matrix, current_vec);
}

Vector3D Vector3D::Scale(const Vector3D& scale)
{
	return Vector3D(this->x * scale.x, this->y * scale.y, this->z * scale.z);
}

Vector3D Vector3D::Scale(const float percentage)
{
	float scale = 1.0f + (percentage / 100.0f);

	return Vector3D(this->x * scale, this->y * scale, this->z * scale);
}

Vector3D Vector3D::operator+(const Vector3D& rhs)
{
	return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

void Vector3D::operator+=(const Vector3D& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;	
	this->z += rhs.z;
}

Vector3D Vector3D::operator-(const Vector3D& rhs)
{
	return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

void Vector3D::operator-=(const Vector3D& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
}

Vector3D Vector3D::operator*(const float scalar)
{
	return Vector3D(this->x  * scalar, this->y * scalar, this->z * scalar);
}

void Vector3D::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
}

Vector3D Vector3D::TransformMultiplication(const std::vector<std::vector<float>>& mat, std::vector<float>& current_vec)
{
	std::vector<float> output(4, 0.0f);

	for (auto i = 0; i < mat.size(); i++)
	{
		for (auto j = 0; j < mat[0].size(); j++)
		{
			output[i] +=
				mat[i][j] * current_vec[j];
		}
	}

	return Vector3D(output[0], output[1], output[2]);
}