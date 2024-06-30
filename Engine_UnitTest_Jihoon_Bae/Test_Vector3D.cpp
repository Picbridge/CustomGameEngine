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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestVector3D
{
	TEST_CLASS(TestVector3D)
	{
	public:

		TEST_METHOD(Length_Validation_ZeroVector_ExpectedLength0)
		{
			Vector3D vector;
			float calculatedLength = vector.Length();

			Assert::AreEqual(0.0f, calculatedLength);
		}

		TEST_METHOD(Length_Validation_DesignatedVector_ExpectedToMatchTheCalculatedValue)
		{
			Vector3D vector(1.0f, 2.0f, 3.0f);
			float expectedLength = std::sqrt(1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f);
			float calculatedLength = vector.Length();

			Assert::AreEqual(expectedLength, calculatedLength);
		}

		TEST_METHOD(DotProduct_Validation_ZeroVectors_ExpectedResultZero)
		{
			Vector3D v1(0.0f, 0.0f, 0.0f);
			Vector3D v2(0.0f, 0.0f, 0.0f);

			float calculatedDotProduct = v1.Dot(v2);

			Assert::AreEqual(0.0f, calculatedDotProduct);
		}

		TEST_METHOD(DotProduct_OrthogonalVectors_ExpectedResultZero)
		{
			Vector3D v1(1.0f, 0.0f, 0.0f);
			Vector3D v2(0.0f, 1.0f, 0.0f);

			float calculatedDotProduct = v1.Dot(v2);

			Assert::AreEqual(0.0f, calculatedDotProduct);
		}

		TEST_METHOD(DotProduct_ParallelVectors_ExpectedResultLengthProduct)
		{
			Vector3D v1(2.0f, 0.0f, 0.0f);
			Vector3D v2(3.0f, 0.0f, 0.0f);

			float calculatedDotProduct = v1.Dot(v2);

			float expectedDotProduct = v1.Length() * v2.Length();

			Assert::AreEqual(expectedDotProduct, calculatedDotProduct);
		}

		TEST_METHOD(CrossProduct_OrthogonalVectors_Z_ValueExpected1)
		{
			Vector3D v1(1.0f, 0.0f, 0.0f);
			Vector3D v2(0.0f, 1.0f, 0.0f);

			Vector3D result = v1.Cross(v2);

			Vector3D expected(0.0f, 0.0f, 1.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}

		TEST_METHOD(CrossProduct_ParallelVectors_Z_ValueExpected0)
		{
			Vector3D v1(2.0f, 0.0f, 0.0f);
			Vector3D v2(4.0f, 0.0f, 0.0f);

			Vector3D result = v1.Cross(v2);

			Vector3D expected(0.0f, 0.0f, 0.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}

		TEST_METHOD(Normalize_NonZeroVector_ExpectedLength0)
		{
			Vector3D vector(0.0f, 0.0f, 0.0f);

			Vector3D result = vector.Normalize();

			float expectedLength = 0.0f;
			Assert::AreEqual(expectedLength, result.Length());
		}

		TEST_METHOD(Normalize_NonZeroVector_ExpectedLength1)
		{
			Vector3D vector(3.0f, 4.0f, 5.0f);

			Vector3D result = vector.Normalize();

			float expectedLength = 1.0f;
			Assert::AreEqual(expectedLength, result.Length());
		}

		TEST_METHOD(Lerp_BasicInterpolation)
		{
			Vector3D start(1.0f, 2.0f, 3.0f);
			Vector3D end(4.0f, 5.0f, 6.0f);
			float t = 0.5f; // Blending factor

			Vector3D result = start.Lerp(end, t);

			// The result should be the vector (2.5, 3.5, 4.5) based on linear interpolation.
			Vector3D expected(2.5f, 3.5f, 4.5f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}

		TEST_METHOD(Lerp_AtTZero_ReturnsStartVector)
		{
			Vector3D start(1.0f, 2.0f, 3.0f);
			Vector3D end(4.0f, 5.0f, 6.0f);
			float t = 0.0f; // Blending factor at t = 0

			Vector3D result = start.Lerp(end, t);

			// When t = 0, the result should be the same as the start vector.
			Vector3D expected(1.0f, 2.0f, 3.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}

		TEST_METHOD(Lerp_AtTOne_ReturnsEndVector)
		{
			Vector3D start(1.0f, 2.0f, 3.0f);
			Vector3D end(4.0f, 5.0f, 6.0f);
			float t = 1.0f; // Blending factor at t = 1

			Vector3D result = start.Lerp(end, t);

			// When t = 1, the result should be the same as the end vector.
			Vector3D expected(4.0f, 5.0f, 6.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}

		TEST_METHOD(Vector_Addition)
		{
			Vector3D up_vector(0.0f, 1.0f, 0.0f);
			Vector3D forward_vector(0.0f, 0.0f, 1.0f);

			Vector3D result = up_vector + forward_vector;
			up_vector += forward_vector;
			Vector3D expected(0.0f, 1.0f, 1.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);

			Assert::AreEqual(expected.x, up_vector.x);
			Assert::AreEqual(expected.y, up_vector.y);
			Assert::AreEqual(expected.z, up_vector.z);
		}

		TEST_METHOD(Vector_Subtraction)
		{
			Vector3D up_vector(0.0f, 1.0f, 0.0f);
			Vector3D forward_vector(0.0f, 0.0f, 1.0f);

			up_vector -= forward_vector;
			Vector3D result = up_vector - forward_vector;

			Vector3D expected_up(0.0f, 1.0f, -1.0f);
			Vector3D expected(0.0f, 1.0f, -2.0f);

			//Result for up_vector modification
			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);

			//Result for calculation on modified up_vector
			Assert::AreEqual(expected_up.x, up_vector.x);
			Assert::AreEqual(expected_up.y, up_vector.y);
			Assert::AreEqual(expected_up.z, up_vector.z);
		}

		TEST_METHOD(Vector_Scale)
		{
			Vector3D v1(1.0f, 2.0f, 3.0f);

			v1 *= 2;
			Vector3D result = v1 * 2;

			//times 2
			Vector3D expected1(2.0f, 4.0f, 6.0f);
			// times 2^2
			Vector3D expected2(4.0f, 8.0f, 12.0f);

			//Result for v1 modification
			Assert::AreEqual(expected1.x, v1.x);
			Assert::AreEqual(expected1.y, v1.y);
			Assert::AreEqual(expected1.z, v1.z);

			//Result for calculation on modified v1
			Assert::AreEqual(expected2.x, result.x);
			Assert::AreEqual(expected2.y, result.y);
			Assert::AreEqual(expected2.z, result.z);
		}

		TEST_METHOD(Transform_Translate10InX_ExpectedResult)
		{
			Vector3D vec_to_translate(5.0f, 5.0f, 0.0f);
			Vector3D translate(10.0f, 0.0f, 0.0f);

			Vector3D result = vec_to_translate.Translate(translate);

			Vector3D expected(15.0f, 5.0f, 0.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);

		}

		TEST_METHOD(Transform_Rotate90InZ_ExpectedResult)
		{
			Vector3D vec_to_rotate(5.0f, 5.0f, 0.0f);
			Vector3D rotation(0.0f, 0.0f, 90.0f);

			Vector3D result = vec_to_rotate.Rotate(rotation);

			Vector3D expected(-5.0f, 5.0f, 0.0f);

			//give some tolerance
			Assert::AreEqual(expected.x, result.x, 1e-6f);
			Assert::AreEqual(expected.y, result.y, 1e-6f);
			Assert::AreEqual(expected.z, result.z, 1e-6f);

		}

		TEST_METHOD(Transform_RotateAllAxis_ExpectedResult)
		{
			Vector3D vec_to_rotate(5.0f, 5.0f, 5.0f);
			Vector3D rotation(45.0f, 2.0f, 34.0f);

			Vector3D result = vec_to_rotate.Rotate(rotation);

			Vector3D expected(4.35f, 2.935f, 6.895f);

			//give some tolerance
			Assert::AreEqual(expected.x, result.x, 1e-2f);
			Assert::AreEqual(expected.y, result.y, 1e-2f);
			Assert::AreEqual(expected.z, result.z, 1e-2f);
		}

		TEST_METHOD(Transform_ScaleByVector_ExpectedResult)
		{
			Vector3D vec_to_scale(5.0f, 5.0f, 0.0f);
			Vector3D scale(3.0f, 2.0f, 2.0f);

			Vector3D result = vec_to_scale.Scale(scale);

			Vector3D expected(15.0f, 10.0f, 0.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}

		TEST_METHOD(Transform_ScaleByPercentage_ExpectedResult)
		{
			Vector3D vec_to_scale(5.0f, 5.0f, 0.0f);
			float percentage = 100;

			Vector3D result = vec_to_scale.Scale(percentage);

			Vector3D expected(10.0f, 10.0f, 0.0f);

			Assert::AreEqual(expected.x, result.x);
			Assert::AreEqual(expected.y, result.y);
			Assert::AreEqual(expected.z, result.z);
		}
	};
}
