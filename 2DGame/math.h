#ifndef MATH_H
#define MATH_H

#define PI 3.141592653589793f

union v3
{
	struct
	{
		float x, y, z;
	};
	struct
	{
		float r, g, b;
	};
	float Arr[3];

	v3() : x(0.0f), y(0.0f), z(0.0f) {}

	v3(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	v3 & operator=(v3& B)
	{
		x = B.x;
		y = B.y;
		z = B.z;
		return *this;
	}
};

inline v3
operator+(v3 A, v3 B)
{
	v3 Result;

	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;

	return(Result);
}

inline v3
operator-(v3 A)
{
	v3 Result;

	Result.x = -A.x;
	Result.y = -A.y;
	Result.z = -A.z;

	return(Result);
}

inline v3
operator-(v3 A, v3 B)
{
	v3 Result;

	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;

	return(Result);
}

inline v3
operator*(float A, v3 B)
{
	v3 Result;

	Result.x = A*B.x;
	Result.y = A*B.y;
	Result.z = A*B.z;

	return(Result);
}

inline v3
operator*(v3 B, float A)
{
	v3 Result = A * B;

	return(Result);
}

inline v3
operator*(v3 A, v3 B)
{
	v3 Result;

	Result.x = A.x * B.x;
	Result.y = A.y * B.y;
	Result.z = A.z * B.z;

	return(Result);
}

union m4
{
	struct
	{
		float a, b, c, d;
		float e, f, g, h;
		float i, j, k, l;
		float m, n, o, p;
	};
	float Rc[4][4];
	float Arr[16];

	m4()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Rc[i][j] = 0.0f;
			}
		}
		Rc[0][0] = 1.0f;
		Rc[1][1] = 1.0f;
		Rc[2][2] = 1.0f;
		Rc[3][3] = 1.0f;
	}

	m4 & operator=(m4& B)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Rc[i][j] = B.Rc[i][j];
			}
		}
		return *this;
	}
};

m4
operator*(m4 &A, m4 &B);

inline float
Math_InnerProduct(v3* A, v3* B)
{
	float Result = A->x*B->x + A->y*B->y + A->z*B->z;

	return(Result);
}

float
Math_SquareRoot(float Value);

inline float
Math_Length(v3 A)
{
	float Result = Math_InnerProduct(&A, &A);
	Result = Math_SquareRoot(Result);
	return(Result);
}

inline v3
Math_Normalize(v3 A)
{
	v3 Result = A * (1.0f / Math_Length(A));

	return(Result);
}


inline float
Math_AbsVal(float Value)
{
	if (Value < 0.0f)
	{
		return -Value;
	}
	else
	{
		return Value;
	}
}

m4
Math_OrthographicMarix(float Left, float Right, float Bottom, float Top,
	float Near, float Far);
m4
Math_LookAtMatrix(v3 &Eye, v3 &Target, v3 &Up);
v3
Math_CrossProduct(v3 &A, v3 &B);
m4
Math_TranslateMatrix(m4 *Matrix, v3 *Vector);
m4
Math_IdentityMatrix();
m4
Math_PerspectiveMatrix(float FieldOfView, float AspectRatio, 
	float NearPlane, float FarPlane);
int
Math_Factorial(int Value);
int
Math_Power(int Base, int Exponent);
float
Math_Power(float Base, int Exponent);
float
Math_Tangent(float Radians);
float
Math_Cosine(float Radians);
float
Math_Sine(float Radians);

#endif