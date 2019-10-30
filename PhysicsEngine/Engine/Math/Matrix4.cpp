#include "Matrix4.h"

/*
Matrix4.cpp
Written by Matthew Fisher
Edited by Yoann Haffner

a 4x4 Matrix4 structure.  Used very often for affine vector transformations.
*/

Matrix4::Matrix4()
{

}

Matrix4::Matrix4(const Matrix4& M)
{
	for (GLuint Row = 0; Row < 4; Row++)
	{
		for (GLuint Col = 0; Col < 4; Col++)
		{
			_Entries[Row][Col] = M[Row][Col];
		}
	}
}

Matrix4::Matrix4(const Vector3& V0, const Vector3& V1, const Vector3& V2)
{
	_Entries[0][0] = V0.x;
	_Entries[0][1] = V0.y;
	_Entries[0][2] = V0.z;
	_Entries[0][3] = 0.0f;

	_Entries[1][0] = V1.x;
	_Entries[1][1] = V1.y;
	_Entries[1][2] = V1.z;
	_Entries[1][3] = 0.0f;

	_Entries[2][0] = V2.x;
	_Entries[2][1] = V2.y;
	_Entries[2][2] = V2.z;
	_Entries[2][3] = 0.0f;

	_Entries[3][0] = 0.0f;
	_Entries[3][1] = 0.0f;
	_Entries[3][2] = 0.0f;
	_Entries[3][3] = 1.0f;
}

#ifdef USE_D3D
Matrix4::Matrix4(const D3DXMATRIX& M)
{
	for (GLuint Row = 0; Row < 4; Row++)
	{
		for (GLuint Col = 0; Col < 4; Col++)
		{
			_Entries[Row][Col] = M(Row, Col);
		}
	}
}
#endif

Matrix4& Matrix4::operator = (const Matrix4& M)
{
	for (GLuint Row = 0; Row < 4; Row++)
	{
		for (GLuint Col = 0; Col < 4; Col++)
		{
			_Entries[Row][Col] = M[Row][Col];
		}
	}
	return (*this);
}

std::string Matrix4::CommaSeparatedString() const
{
	std::stringstream ss;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			ss << _Entries[i][i2];
			if (i2 != 3)
			{
				ss << ", ";
			}
		}
		if (i != 3)
		{
			ss << "\n";
		}
	}
	return ss.str();
}

std::string Matrix4::CommaSeparatedStringSingleLine() const
{
	std::stringstream ss;
	for (GLuint i = 0; i < 4; i++)
	{
		ss << "(";
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			ss << _Entries[i][i2];
			if (i2 != 3)
			{
				ss << ", ";
			}
		}
		ss << ")";
	}
	return ss.str();
}

std::string Matrix4::SpaceSeperatedStringSingleLine() const
{
	std::stringstream ss;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			ss << _Entries[i][i2];
			if (i2 != 3)
			{
				ss << " ";
			}
		}
	}
	return ss.str();
}

std::string Matrix4::TabSeperatedString()  const
{
	std::stringstream ss;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			ss << _Entries[i][i2];
			if (i2 != 3)
			{
				ss << ", ";
			}
		}
		if (i != 3)
		{
			ss << "\n";
		}
	}
	return ss.str();
}

Matrix4 Matrix4::Inverse() const
{
	//
	// Inversion by Cramer's rule.  Code taken from an Intel publication
	//
	double Result[4][4];
	double tmp[12]; /* temp array for pairs */
	double src[16]; /* array of transpose source matrix */
	double det; /* determinant */
	/* transpose matrix */
	for (GLuint i = 0; i < 4; i++)
	{
		src[i + 0] = (*this)[i][0];
		src[i + 4] = (*this)[i][1];
		src[i + 8] = (*this)[i][2];
		src[i + 12] = (*this)[i][3];
	}
	/* calculate pairs for first 8 elements (cofactors) */
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];
	/* calculate first 8 elements (cofactors) */
	Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
	/* calculate pairs for second 8 elements (cofactors) */
	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];

	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];
	/* calculate second 8 elements (cofactors) */
	Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
	/* calculate determinant */
	det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
	/* calculate matrix inverse */
	det = 1.0f / det;

	Matrix4 FloatResult;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint j = 0; j < 4; j++)
		{
			FloatResult[i][j] = float(Result[i][j] * det);
		}
	}
	return FloatResult;
}

Matrix4 Matrix4::Transpose() const
{
	Matrix4 Result;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			Result[i2][i] = _Entries[i][i2];
		}
	}
	return Result;
}

Matrix4 Matrix4::Identity()
{
	Matrix4 Result;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			if (i == i2)
			{
				Result[i][i2] = 1.0f;
			}
			else
			{
				Result[i][i2] = 0.0f;
			}
		}
	}
	return Result;
}

Matrix4 Matrix4::Rotation(const Vector3& _Basis1, const Vector3& _Basis2, const Vector3& _Basis3)
{
	//
	// Verify everything is normalized
	//
	Vector3 Basis1 = Vector3::Normalized(_Basis1);
	Vector3 Basis2 = Vector3::Normalized(_Basis2);
	Vector3 Basis3 = Vector3::Normalized(_Basis3);

	Matrix4 Result;
	Result[0][0] = Basis1.x;
	Result[1][0] = Basis1.y;
	Result[2][0] = Basis1.z;
	Result[3][0] = 0.0f;

	Result[0][1] = Basis2.x;
	Result[1][1] = Basis2.y;
	Result[2][1] = Basis2.z;
	Result[3][1] = 0.0f;

	Result[0][2] = Basis3.x;
	Result[1][2] = Basis3.y;
	Result[2][2] = Basis3.z;
	Result[3][2] = 0.0f;

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = 0.0f;
	Result[3][3] = 1.0f;
	return Result;
}

Matrix4 Matrix4::Camera(const Vector3& Eye, const Vector3& _Look, const Vector3& _Up, const Vector3& _Right)
{
	//
	// Verify everything is normalized
	//
	Vector3 Look = Vector3::Normalized(_Look);
	Vector3 Up = Vector3::Normalized(_Up);
	Vector3 Right = Vector3::Normalized(_Right);

	Matrix4 Result;
	Result[0][0] = Right.x;
	Result[1][0] = Right.y;
	Result[2][0] = Right.z;
	Result[3][0] = -Vector3::Dot(Right, Eye);

	Result[0][1] = Up.x;
	Result[1][1] = Up.y;
	Result[2][1] = Up.z;
	Result[3][1] = -Vector3::Dot(Up, Eye);

	Result[0][2] = Look.x;
	Result[1][2] = Look.y;
	Result[2][2] = Look.z;
	Result[3][2] = -Vector3::Dot(Look, Eye);

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = 0.0f;
	Result[3][3] = 1.0f;
	return Result;
}

Matrix4 Matrix4::LookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up)
{
	Vector3 XAxis, YAxis, ZAxis;
	ZAxis = Vector3::Normalized(Eye - At);
	XAxis = Vector3::Normalized(Vector3::Cross(Up, ZAxis));
	YAxis = Vector3::Normalized(Vector3::Cross(ZAxis, XAxis));

	Matrix4 Result;
	Result[0][0] = XAxis.x;
	Result[1][0] = XAxis.y;
	Result[2][0] = XAxis.z;
	Result[3][0] = -Vector3::Dot(XAxis, Eye);

	Result[0][1] = YAxis.x;
	Result[1][1] = YAxis.y;
	Result[2][1] = YAxis.z;
	Result[3][1] = -Vector3::Dot(YAxis, Eye);

	Result[0][2] = ZAxis.x;
	Result[1][2] = ZAxis.y;
	Result[2][2] = ZAxis.z;
	Result[3][2] = -Vector3::Dot(ZAxis, Eye);

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = 0.0f;
	Result[3][3] = 1.0f;
	return Result;
}

Matrix4 Matrix4::Orthogonal(float Width, float Height, float ZNear, float ZFar)
{
	Matrix4 Result;
	Result[0][0] = 2.0f / Width;
	Result[1][0] = 0.0f;
	Result[2][0] = 0.0f;
	Result[3][0] = 0.0f;

	Result[0][1] = 0.0f;
	Result[1][1] = 2.0f / Height;
	Result[2][1] = 0.0f;
	Result[3][1] = 0.0f;

	Result[0][2] = 0.0f;
	Result[1][2] = 0.0f;
	Result[2][2] = 1.0f / (ZNear - ZFar);
	Result[3][2] = ZNear / (ZNear - ZFar);

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = 0.0f;
	Result[3][3] = 1.0f;
	return Result;
}

Matrix4 Matrix4::Perspective(float Width, float Height, float ZNear, float ZFar)
{
	Matrix4 Result;
	Result[0][0] = 2.0f * ZNear / Width;
	Result[1][0] = 0.0f;
	Result[2][0] = 0.0f;
	Result[3][0] = 0.0f;

	Result[0][1] = 0.0f;
	Result[1][1] = 2.0f * ZNear / Height;
	Result[2][1] = 0.0f;
	Result[3][1] = 0.0f;

	Result[0][2] = 0.0f;
	Result[1][2] = 0.0f;
	Result[2][2] = ZFar / (ZNear - ZFar);
	Result[3][2] = ZFar * ZNear / (ZNear - ZFar);

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = -1.0f;
	Result[3][3] = 0.0f;
	return Result;
}

Matrix4 Matrix4::PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar)
{
	float Width = 1.0f / tanf(FOV / 2.0f), Height = Aspect / tanf(FOV / 2.0f);

	Matrix4 Result;
	Result[0][0] = Width;
	Result[1][0] = 0.0f;
	Result[2][0] = 0.0f;
	Result[3][0] = 0.0f;

	Result[0][1] = 0.0f;
	Result[1][1] = Height;
	Result[2][1] = 0.0f;
	Result[3][1] = 0.0f;

	Result[0][2] = 0.0f;
	Result[1][2] = 0.0f;
	Result[2][2] = ZFar / (ZNear - ZFar);
	Result[3][2] = ZFar * ZNear / (ZNear - ZFar);

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = -1.0f;
	Result[3][3] = 0.0f;
	return Result;
}

Matrix4 Matrix4::PerspectiveMultiFov(float FovX, float FovY, float ZNear, float ZFar)
{
	float Width = 1.0f / tanf(FovX / 2.0f), Height = 1.0f / tanf(FovY / 2.0f);

	Matrix4 Result;
	Result[0][0] = Width;
	Result[1][0] = 0.0f;
	Result[2][0] = 0.0f;
	Result[3][0] = 0.0f;

	Result[0][1] = 0.0f;
	Result[1][1] = Height;
	Result[2][1] = 0.0f;
	Result[3][1] = 0.0f;

	Result[0][2] = 0.0f;
	Result[1][2] = 0.0f;
	Result[2][2] = ZFar / (ZNear - ZFar);
	Result[3][2] = ZFar * ZNear / (ZNear - ZFar);

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = -1.0f;
	Result[3][3] = 0.0f;
	return Result;
}

Matrix4 Matrix4::Rotation(const Vector3& Axis, float Angle)
{
	float c = cosf(Angle);
	float s = sinf(Angle);
	float t = 1.0f - c;

	Vector3 NormalizedAxis = Vector3::Normalized(Axis);
	float x = NormalizedAxis.x;
	float y = NormalizedAxis.y;
	float z = NormalizedAxis.z;

	Matrix4 Result;
	Result[0][0] = 1 + t * (x * x - 1);
	Result[0][1] = z * s + t * x * y;
	Result[0][2] = -y * s + t * x * z;
	Result[0][3] = 0.0f;

	Result[1][0] = -z * s + t * x * y;
	Result[1][1] = 1 + t * (y * y - 1);
	Result[1][2] = x * s + t * y * z;
	Result[1][3] = 0.0f;

	Result[2][0] = y * s + t * x * z;
	Result[2][1] = -x * s + t * y * z;
	Result[2][2] = 1 + t * (z * z - 1);
	Result[2][3] = 0.0f;

	Result[3][0] = 0.0f;
	Result[3][1] = 0.0f;
	Result[3][2] = 0.0f;
	Result[3][3] = 1.0f;
	return Result;
}

Matrix4 Matrix4::Rotation(float Yaw, float Pitch, float Roll)
{
	return RotationY(Yaw) * RotationX(Pitch) * RotationZ(Roll);
}

Matrix4 Matrix4::Rotation(const Vector3& Axis, float Angle, const Vector3& Center)
{
	return Translation(-Center) * Rotation(Axis, Angle) * Translation(Center);
}

Matrix4 Matrix4::RotationX(float Theta)
{
	float CosT = cosf(Theta);
	float SinT = sinf(Theta);

	Matrix4 Result = Identity();
	Result[1][1] = CosT;
	Result[1][2] = SinT;
	Result[2][1] = -SinT;
	Result[2][2] = CosT;
	return Result;
}

Matrix4 Matrix4::RotationY(float Theta)
{
	float CosT = cosf(Theta);
	float SinT = sinf(Theta);

	Matrix4 Result = Identity();
	Result[0][0] = CosT;
	Result[0][2] = SinT;
	Result[2][0] = -SinT;
	Result[2][2] = CosT;
	return Result;
}

Matrix4 Matrix4::RotationZ(float Theta)
{
	float CosT = cosf(Theta);
	float SinT = sinf(Theta);

	Matrix4 Result = Identity();
	Result[0][0] = CosT;
	Result[0][1] = SinT;
	Result[1][0] = -SinT;
	Result[1][1] = CosT;
	return Result;
}

Matrix4 Matrix4::Scaling(const Vector3& ScaleFactors)
{
	Matrix4 Result;
	Result[0][0] = ScaleFactors.x;
	Result[1][0] = 0.0f;
	Result[2][0] = 0.0f;
	Result[3][0] = 0.0f;

	Result[0][1] = 0.0f;
	Result[1][1] = ScaleFactors.y;
	Result[2][1] = 0.0f;
	Result[3][1] = 0.0f;

	Result[0][2] = 0.0f;
	Result[1][2] = 0.0f;
	Result[2][2] = ScaleFactors.z;
	Result[3][2] = 0.0f;

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = 0.0f;
	Result[3][3] = 1.0f;
	return Result;
}

Matrix4 Matrix4::Translation(const Vector3& Pos)
{
	Matrix4 Result;
	Result[0][0] = 1.0f;
	Result[1][0] = 0.0f;
	Result[2][0] = 0.0f;
	Result[3][0] = Pos.x;

	Result[0][1] = 0.0f;
	Result[1][1] = 1.0f;
	Result[2][1] = 0.0f;
	Result[3][1] = Pos.y;

	Result[0][2] = 0.0f;
	Result[1][2] = 0.0f;
	Result[2][2] = 1.0f;
	Result[3][2] = Pos.z;

	Result[0][3] = 0.0f;
	Result[1][3] = 0.0f;
	Result[2][3] = 0.0f;
	Result[3][3] = 1.0f;
	return Result;
}

Matrix4 Matrix4::ChangeOfBasis(const Vector3& Source0, const Vector3& Source1, const Vector3& Source2, const Vector3& SourceOrigin,
	const Vector3& Target0, const Vector3& Target1, const Vector3& Target2, const Vector3& TargetOrigin)
{
	Matrix4 RotationComponent = Matrix4(Source0, Source1, Source2).Inverse() * Matrix4(Target0, Target1, Target2);
	//Matrix4 TranslationComponent = Translation(TargetOrigin - SourceOrigin);
	Matrix4 Result = Translation(-SourceOrigin) * RotationComponent * Translation(TargetOrigin);
	return Result;
	//return Translation(TargetOrigin - SourceOrigin);
}

Matrix4 Matrix4::Viewport(float Width, float Height)
{
	return Matrix4::Scaling(Vector3(Width * 0.5f, -Height * 0.5f, 1.0f)) * Matrix4::Translation(Vector3(Width * 0.5f, Height * 0.5f, 0.0f));
}

float Matrix4::CompareMatrices(const Matrix4& Left, const Matrix4& Right)
{
	float Sum = 0.0f;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			Sum += abs(Left[i][i2] - Right[i][i2]);
		}
	}
	return Sum / 16.0f;
}

#ifdef USE_D3D
Matrix4::operator D3DXMATRIX() const
{
	D3DXMATRIX M;
	int i, i2;
	for (i = 0;i < 4;i++)
		for (i2 = 0;i2 < 4;i2++)
		{
			M(i, i2) = _Entries[i][i2];
		}

	return M;
}
#endif

Matrix4 operator * (const Matrix4& Left, const Matrix4& Right)
{
	Matrix4 Result;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			float Total = 0.0f;
			for (GLuint i3 = 0; i3 < 4; i3++)
			{
				Total += Right[i][i3] * Left[i3][i2];
			}
			Result[i][i2] = Total;
		}
	}
	return Result;
}

Matrix4 operator * (const Matrix4& Left, float& Right)
{
	Matrix4 Result;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			Result[i][i2] = Left[i][i2] * Right;
		}
	}
	return Result;
}

Matrix4 operator * (float& Left, const Matrix4& Right)
{
	Matrix4 Result;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			Result[i][i2] = Right[i][i2] * Left;
		}
	}
	return Result;
}

Matrix4 operator + (const Matrix4& Left, const Matrix4& Right)
{
	Matrix4 Result;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			Result[i][i2] = Left[i][i2] + Right[i][i2];
		}
	}
	return Result;
}

Matrix4 operator - (const Matrix4& Left, const Matrix4& Right)
{
	Matrix4 Result;
	for (GLuint i = 0; i < 4; i++)
	{
		for (GLuint i2 = 0; i2 < 4; i2++)
		{
			Result[i][i2] = Left[i][i2] - Right[i][i2];
		}
	}
	return Result;
}