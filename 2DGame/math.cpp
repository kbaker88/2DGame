#include "math.h"

m4
operator*(m4 &A, m4 &B)
{
	m4 Result;

	float Hold = 0;
	int j = 0;

	for (int k = 0; k < 4; k++)
	{
		for (int m = 0; m < 4; m++)
		{
			for (int i = 0; i < 4; i++)
			{
				Hold += A.Rc[k][j] * B.Rc[i][m];

				j++;
			}
			Result.Rc[k][m] = Hold;
			j = 0;
			Hold = 0;
		}
	}

	return Result;
}

m4
Math_OrthographicMarix(float Left, float Right, float Bottom, float Top,
	float Near, float Far)
{
	m4 Matrix;

	Matrix.Rc[0][0] = 2.0f / (Right - Left);
	Matrix.Rc[1][1] = 2.0f / (Top - Bottom);
	Matrix.Rc[2][2] = -2.0f / (Far - Near);
	Matrix.Rc[3][0] = -(Right + Left) / (Right - Left);
	Matrix.Rc[3][1] = -(Top + Bottom) / (Top - Bottom);
	Matrix.Rc[3][2] = -(Far + Near) / (Far - Near);

	return Matrix;
}

m4
Math_LookAtMatrix(v3 &Eye, v3 &Target, v3 &Up)
{
	v3 ZAxis = Math_Normalize(Target - Eye);
	v3 XAxis = Math_Normalize(Math_CrossProduct(ZAxis, Up));
	v3 YAxis = Math_CrossProduct(XAxis, ZAxis);

	m4 Result;
	Result.Rc[0][0] = XAxis.x;
	Result.Rc[1][0] = XAxis.y;
	Result.Rc[2][0] = XAxis.z;
	Result.Rc[0][1] = YAxis.x;
	Result.Rc[1][1] = YAxis.y;
	Result.Rc[2][1] = YAxis.z;
	Result.Rc[0][2] = -ZAxis.x;
	Result.Rc[1][2] = -ZAxis.y;
	Result.Rc[2][2] = -ZAxis.z;
	Result.Rc[3][0] = -Math_InnerProduct(&XAxis, &Eye);
	Result.Rc[3][1] = -Math_InnerProduct(&YAxis, &Eye);
	Result.Rc[3][2] = Math_InnerProduct(&ZAxis, &Eye);
	Result.Rc[3][3] = 1.0f;
	return Result;
}

float
Math_SquareRoot(float Value)
{
	if (Value == 1.0f)
	{
		return 1.0f;
	}
	else if (Value == 0.0f)
	{
		return 0.0f;
	}
	else if (Value < 0.0f)
	{
		return -1.0f; // Error
	}

	float Result = Value * 0.5f; //TODO: Find a better initial guess.
	float HalfValue = Result;
	float Precision = 0.0000001f;

	for (unsigned int i = 0; i < 100; i++)
	{
		Result -= (Result * 0.5f) - (HalfValue / Result);
		if (Math_AbsVal(Result) <= Precision)
			break;
	}

	return Result;
}

v3
Math_CrossProduct(v3 &A, v3 &B)
{
	v3 Result = {};
	Result.x = (A.y * B.z) - (A.z * B.y);
	Result.y = (A.z * B.x) - (A.x * B.z);
	Result.z = (A.x * B.y) - (A.y * B.x);

	return Result;
}

m4
Math_TranslateMatrix(m4 *Matrix, v3 *Vector)
{
	m4 Result = *Matrix;

	Result.Rc[3][0] += Vector->Arr[0];
	Result.Rc[3][1] += Vector->Arr[1];
	Result.Rc[3][2] += Vector->Arr[2];

	return Result;
}

m4
Math_IdentityMatrix()
{
	m4 Result;

	Result.Rc[0][0] = 1.0f;
	Result.Rc[1][1] = 1.0f;
	Result.Rc[2][2] = 1.0f;
	Result.Rc[3][3] = 1.0f;

	return Result;
}

m4
Math_PerspectiveMatrix(float FieldOfView, float AspectRatio, float NearPlane, float FarPlane)
{
	m4 Matrix;
	float HalfVal = (float)Math_Tangent(FieldOfView * 0.5f);

	Matrix.Arr[0] = 1.0f / (AspectRatio * HalfVal);
	Matrix.Arr[1] = 0;
	Matrix.Arr[2] = 0;
	Matrix.Arr[3] = 0;

	Matrix.Arr[4] = 0;
	Matrix.Arr[5] = 1.0f / HalfVal;
	Matrix.Arr[6] = 0;
	Matrix.Arr[7] = 0;

	Matrix.Arr[8] = 0;
	Matrix.Arr[9] = 0;
	Matrix.Arr[10] = -(FarPlane + NearPlane) / (FarPlane - NearPlane);
	Matrix.Arr[11] = -1.0f;

	Matrix.Arr[12] = 0;
	Matrix.Arr[13] = 0;
	Matrix.Arr[14] = -(2.0f * FarPlane * NearPlane) / (FarPlane - NearPlane);
	Matrix.Arr[15] = 0;

	return Matrix;
}

int
Math_Factorial(int Value)
{
	int Result = Value;

	for (int i = 1; i < Value; i++)
	{
		Result *= (Value - i);
	}

	return Result;
}

float
Math_Power(float Base, int Exponent)
{
	float Result = 1.0f;
	while (Exponent)
	{
		if (Exponent & 1)
			Result *= Base;
		Exponent >>= 1;
		Base *= Base;
	}

	return Result;
}

int
Math_Power(int Base, int Exponent)
{
	int Result = 1;
	while (Exponent)
	{
		if (Exponent & 1)
			Result *= Base;
		Exponent >>= 1;
		Base *= Base;
	}

	return Result;
}

float
Math_Sine(float Radians)
{
	while (Radians < -PI)
	{
		Radians += 2.0f * PI;
	}

	while (Radians > PI)
	{
		Radians -= 2.0f * PI;
	}

	double Result = Radians;
	bool FlipSign = false;

	//TODO: Pre-compute the factorials on startup.
	for (unsigned int i = 3; i < 11; i = i + 2)
	{
		if (FlipSign)
		{
			Result += Math_Power(Radians, i) / (double)Math_Factorial(i);
			FlipSign = 0;
		}
		else
		{
			Result -= Math_Power(Radians, i) / (double)Math_Factorial(i);
			FlipSign = 1;
		}
	}
	return (float)Result;
	//return sinf(Radians);
}

float
Math_Cosine(float Radians)
{
	while (Radians < -PI)
	{
		Radians += 2.0f * PI;
	}

	while (Radians > PI)
	{
		Radians -= 2.0f * PI;
	}

	double Result = 1;
	bool FlipSign = false;

	//TODO: Pre-compute the factorials on startup.
	for (unsigned int i = 2; i < 11; i = i + 2)
	{
		if (FlipSign)
		{
			Result += Math_Power(Radians, i) / (double)Math_Factorial(i);
			FlipSign = 0;
		}
		else
		{
			Result -= Math_Power(Radians, i) / (double)Math_Factorial(i);
			FlipSign = 1;
		}
	}
	return (float)Result;
	//return cosf(Radians);
}

float
Math_Tangent(float Radians)
{
	return (Math_Sine(Radians) / Math_Cosine(Radians));
	//return tanf(Radians);
}