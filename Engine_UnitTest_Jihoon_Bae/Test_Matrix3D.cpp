/*-------------------------------------------------------
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: <Test_Vector3D.cpp>
Purpose: <Test cases for 3D Vector class>
Language: <c++,visual studio2022>
Platform: <visual studio2022, win11>
Project: <jihoon.bae_CS529_2>
Author: <jihoon.bae>
Creation date: <09/11/2023>
--------------------------------------------------------*/
#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMatrix3D
{
	TEST_CLASS(TestMatrix3D)
	{
	public:

		TEST_METHOD(Identity_Matrix_Validation)
		{
			Matrix3D matrix;

			//Case where matrix is not identity matrix
			matrix.data[0][0] = 1.0f;
			matrix.data[1][2] = 5.0f;
			
			Matrix3D identity_matrix = matrix.IdentityMatrix();

			float expected = 1.0f;
			for (auto i = 0; i < 3; i++)
			{
				for (auto j = 0; j < 3; j++)
				{
					expected = i == j ? 1.0f : 0.0f;
					Assert::AreEqual(expected, identity_matrix.data[i][j]);
				}
			}
		}

		TEST_METHOD(Transpose_FilledMatrix)
		{
			Matrix3D matrix(
				{
				{1.0f, 2.0f, 3.0f},
				{4.0f, 5.0f, 6.0f},
				{7.0f, 8.0f, 9.0f}
				});

			Matrix3D result = matrix.Transpose();

			Matrix3D expected(
				{
				{1.0f, 4.0f, 7.0f},
				{2.0f, 5.0f, 8.0f},
				{3.0f, 6.0f, 9.0f}
				});

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					Assert::AreEqual(expected.data[i][j], result.data[i][j]);
				}
			}
		}

		TEST_METHOD(Transpose_IdentityMatrix_ExpectedIdentity)
		{
			Matrix3D matrix;

			Matrix3D result = matrix.Transpose();

			float expected = 1.0f;
			for (auto i = 0; i < 3; i++)
			{
				for (auto j = 0; j < 3; j++)
				{
					expected = i == j ? 1.0f : 0.0f;
					Assert::AreEqual(expected, matrix.data[i][j]);
				}
			}
		}

		TEST_METHOD(Inverse_IdentityMatrix_ExpectedResultIdentityMatrix)
		{
			Matrix3D identityMatrix(
				{
				{1.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f},
				{0.0f, 0.0f, 1.0f}
				});

			Matrix3D result = identityMatrix.Inverse();

			float expected = 1.0f;
			for (auto i = 0; i < 3; i++)
			{
				for (auto j = 0; j < 3; j++)
				{
					expected = i == j ? 1.0f : 0.0f;
					Assert::AreEqual(expected, identityMatrix.data[i][j]);
				}
			}
		}

		TEST_METHOD(Inverse_SingularMatrix_ExpectedResultException)
		{
			Matrix3D singularMatrix(
				{
				{1.0f, 2.0f, 3.0f},
				{4.0f, 5.0f, 6.0f},
				{7.0f, 8.0f, 9.0f}
				});

			Assert::ExpectException<std::invalid_argument>([&singularMatrix](){
					Matrix3D result = singularMatrix.Inverse();
				});
		}

		TEST_METHOD(Inverse_RegularMatrix)
		{
			Matrix3D matrix(
				{
				{1.0f, 2.0f, 3.0f},
				{0.0f, 1.0f, 4.0f},
				{5.0f, 6.0f, 0.0f}
				});

			Matrix3D result = matrix.Inverse();

			Matrix3D expected({
				{-24.0f, 18.0, 5.0f},
				{20.0f, -15.0f, -4.0f},
				{-5.0f, 4.0f, 1.0f}
				});

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					Assert::AreEqual(expected.data[i][j], result.data[i][j]);
				}
			}
		}

		TEST_METHOD(Addition_Between_IdentityMatrix)
		{
			Matrix3D identity_matrix1;
			Matrix3D identity_matrix2;

			Matrix3D result = identity_matrix1 + identity_matrix2;

			result += identity_matrix1;

			Matrix3D expected({
				{3.0f, 0.0f, 0.0f},
				{0.0f, 3.0f, 0.0f},
				{0.0f, 0.0f, 3.0f}
				});

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					Assert::AreEqual(expected.data[i][j], result.data[i][j]);
				}
			}
		}

		TEST_METHOD(Subtraction_RegularMatrix)
		{
			Matrix3D matrix(
				{
				{2.0f, 0.0f, 0.0f},
				{0.0f, 2.0f, 0.0f},
				{2.0f, 0.0f, 2.0f}
				});
			Matrix3D identity_matrix;

			Matrix3D result = matrix - identity_matrix;

			result -= identity_matrix;

			Matrix3D expected({
				{0.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f},
				{2.0f, 0.0f, 0.0f}
				});

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					Assert::AreEqual(expected.data[i][j], result.data[i][j]);
				}
			}
		}

		TEST_METHOD(Multiplication_MatrixScalar_ExpectedResult)
		{
			Matrix3D matrix({
				{1.0f, 2.0f, 3.0f},
				{4.0f, 5.0f, 6.0f},
				{7.0f, 8.0f, 9.0f}
				});
			float scalar = 2.0f;

			Matrix3D result = matrix * scalar;
			matrix *= scalar;

			Matrix3D expected({
				{2.0f, 4.0f, 6.0f},
				{8.0f, 10.0f, 12.0f},
				{14.0f, 16.0f, 18.0f}
				});

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					Assert::AreEqual(expected.data[i][j], matrix.data[i][j]);
					Assert::AreEqual(expected.data[i][j], result.data[i][j]);
				}
			}
		}

		TEST_METHOD(Multiplication_MatrixMatrix_ExpectedResult)
		{
			Matrix3D matrix1({
				{1.0f, 2.0f, 3.0f},
				{4.0f, 5.0f, 6.0f},
				{7.0f, 8.0f, 9.0f}
				});
			Matrix3D matrix2({
				{9.0f, 8.0f, 7.0f},
				{6.0f, 5.0f, 4.0f},
				{3.0f, 2.0f, 1.0f}
				});

			Matrix3D result = matrix1 * matrix2;

			Matrix3D expected({
				{30.0f, 24.0f, 18.0f},
				{84.0f, 69.0f, 54.0f},
				{138.0f, 114.0f, 90.0f}
				});

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					Assert::AreEqual(expected.data[i][j], result.data[i][j]);
				}
			}
		}

		TEST_METHOD(Multiplication_MatrixVector_ExpectedResult)
		{
			Matrix3D matrix({
				{1.0f, 2.0f, 3.0f},
				{4.0f, 5.0f, 6.0f},
				{7.0f, 8.0f, 9.0f}
				});
			Vector3D vector(2.0f, 3.0f, 4.0f);

			Vector3D result = matrix * vector;

			Vector3D expected(20.0f, 47.0f, 74.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}
	};
}
