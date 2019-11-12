#include "Matrix4.h"


//Constructor
Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
	{
        if (i%5 == 0){matrix[i] = 1;}
        else{matrix[i] = 0;}
	}
}

Matrix4::Matrix4(Matrix4& copyMatrix)
{
    for (int i = 0; i < 16; i++) { matrix[i] = copyMatrix.matrix[i]; }
}

Matrix4::Matrix4(float matrixTable[])
{
    for (int i = 0; i < 16; i++)
	{
        if (i%5 == 0){matrix[i] = 1;}
        else{matrix[i] = 0;}
	}

	if (sizeof(matrixTable)/sizeof(float) < 16) {
		for (int i = 0; i < sizeof(matrixTable)/sizeof(float); i++)
		{
			matrix[i] = matrixTable[i];
		}
	}
	else
	{
        for (int i = 0; i < 16; i++) 
		{ 
			matrix[i] = matrixTable[i]; 
		}
	}
}


//Methode
float Matrix4::matrix4Det()
{
    return matrix[0] * matrix[5] * matrix[10] * matrix[15] +
           matrix[1] * matrix[6] * matrix[11] * matrix[12] +
           matrix[2] * matrix[7] * matrix[8] * matrix[13] +
           matrix[3] * matrix[4] * matrix[9] * matrix[14] -
           matrix[3] * matrix[6] * matrix[9] * matrix[12] -
           matrix[2] * matrix[5] * matrix[8] * matrix[15] -
           matrix[1] * matrix[4] * matrix[11] * matrix[14] -
           matrix[0] * matrix[7] * matrix[10] * matrix[13];
}

Matrix4 Matrix4::matrix4Inverse()
{
    float invDet;
    float index[16];
    Matrix3 m[16];


	m[0] = Matrix3(matrix[5], matrix[6], matrix[7], 
				 matrix[9], matrix[10], matrix[11], 
				 matrix[13], matrix[14], matrix[15]);

	m[1] = Matrix3(matrix[1], matrix[2], matrix[3], 
		         matrix[9], matrix[10], matrix[11], 
		         matrix[13], matrix[14], matrix[15]);

	m[2] = Matrix3(matrix[1], matrix[2], matrix[3], 
				 matrix[5], matrix[6], matrix[7],
                 matrix[13], matrix[14], matrix[15]);

	m[3] = Matrix3(matrix[1], matrix[2], matrix[3], 
				 matrix[5], matrix[6], matrix[7],
                 matrix[9], matrix[10], matrix[11]);


	m[4] = Matrix3(matrix[4], matrix[6], matrix[7],
				 matrix[8], matrix[10], matrix[11], 
				 matrix[12], matrix[14], matrix[15]);

    m[5] = Matrix3(matrix[0], matrix[2], matrix[3], 
				 matrix[8], matrix[10], matrix[11], 
				 matrix[12], matrix[14], matrix[15]);

    m[6] = Matrix3(matrix[0], matrix[2], matrix[3], 
				 matrix[4], matrix[6], matrix[7], 
				 matrix[12], matrix[14], matrix[15]);

    m[7] = Matrix3(matrix[0], matrix[2], matrix[3], 
				 matrix[4], matrix[6], matrix[7], 
				 matrix[8], matrix[10], matrix[11]);

	m[8] = Matrix3(matrix[4], matrix[5], matrix[7], 
				 matrix[8], matrix[9], matrix[11], 
				 matrix[12], matrix[13], matrix[15]);

    m[9] = Matrix3(matrix[0], matrix[1], matrix[3], 
				 matrix[8], matrix[9], matrix[11], 
				 matrix[12], matrix[13], matrix[15]);

    m[10] = Matrix3(matrix[0], matrix[1], matrix[3], 
				 matrix[4], matrix[5], matrix[7], 
				 matrix[12], matrix[13], matrix[15]);

    m[11] = Matrix3(matrix[0], matrix[1], matrix[3], 
				  matrix[4], matrix[5], matrix[7], 
				  matrix[8], matrix[9], matrix[11]);

    m[12] = Matrix3(matrix[4], matrix[5], matrix[6], 
				  matrix[8], matrix[9], matrix[10], 
				  matrix[12], matrix[13], matrix[14]);

    m[13] = Matrix3(matrix[0], matrix[1], matrix[2], 
				  matrix[8], matrix[9], matrix[10], 
				  matrix[12], matrix[13], matrix[14]);

    m[14] = Matrix3(matrix[0], matrix[1], matrix[2], 
				  matrix[4], matrix[5], matrix[6], 
				  matrix[12], matrix[13], matrix[14]);

    m[15] = Matrix3(matrix[0], matrix[1], matrix[2], 
				  matrix[4], matrix[5], matrix[6], 
				  matrix[8], matrix[9], matrix[10]);


    invDet = 1 / matrix4Det();

	for (int i = 0; i < 16; i++)
	{ 
		index[i] = invDet * m[i].matrix3Det();
	}

    return Matrix4(index);
}

Matrix4 Matrix4::matrix4Transpose() { 
	float index[16];
	
	index[0] = matrix[0];
	index[1] = matrix[4];
	index[2] = matrix[8];
	index[3] = matrix[12];

	index[4] = matrix[1];
	index[5] = matrix[5];
	index[6] = matrix[9];
	index[7] = matrix[14];

	index[8] = matrix[2];
	index[9] = matrix[6];
	index[10] = matrix[10];
	index[11] = matrix[14];

	index[12] = matrix[3];
	index[13] = matrix[7];
	index[14] = matrix[11];
	index[15] = matrix[15];

    return Matrix4(index);
}

Matrix4 Matrix4::PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar)
{
	float Width = 1.0f / tanf(FOV / 2.0f), Height = Aspect / tanf(FOV / 2.0f);
	float index[16];

	index[0] = Width;
	index[1] = 0.0f;
	index[2] = 0.0f;
	index[3] = 0.0f;

	index[4] = 0.0f;
	index[5] = Height;
	index[6] = 0.0f;
	index[7] = 0.0f;

	index[8] = 0.0f;
	index[9] = 0.0f;
	index[10] = ZFar / (ZNear - ZFar);
	index[11] = ZFar * ZNear / (ZNear - ZFar);

	index[12] = 0.0f;
	index[13] = 0.0f;
	index[14] = -1.0f;
	index[15] = 0.0f;

	return Matrix4(index);
}

Matrix4 Matrix4::LookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up)
{
	Vector3 XAxis, YAxis, ZAxis;
	ZAxis = Vector3::Normalized(Eye - At);
	XAxis = Vector3::Normalized(Vector3::Cross(Up, ZAxis));
	YAxis = Vector3::Normalized(Vector3::Cross(ZAxis, XAxis));

	float index[16];
	index[0] = XAxis.x;
	index[1] = XAxis.y;
	index[2] = XAxis.z;
	index[3] = -Vector3::Dot(XAxis, Eye);

	index[4] = YAxis.x;
	index[5] = YAxis.y;
	index[6] = YAxis.z;
	index[7] = -Vector3::Dot(YAxis, Eye);

	index[8] = ZAxis.x;
	index[9] = ZAxis.y;
	index[10] = ZAxis.z;
	index[11] = -Vector3::Dot(ZAxis, Eye);

	index[12] = 0.0f;
	index[13] = 0.0f;
	index[14] = 0.0f;
	index[15] = 1.0f;
	return Matrix4(index);
}

Vector3 Matrix4::TransformPoint(const Vector3& point) const
{
	float w = point.x * matrix[3] + point.y * matrix[7] + point.z * matrix[11] + matrix[15];
	if (w)
	{
		const float invW = 1.0f / w;
		return Vector3((point.x * matrix[0] + point.y * matrix[4] + point.z * matrix[8] + matrix[12]) * invW,
			(point.x * matrix[1] + point.y * matrix[5] + point.z * matrix[9] + matrix[13]) * invW,
			(point.x * matrix[2] + point.y * matrix[6] + point.z * matrix[10] + matrix[14]) * invW);
	}
	else
	{
		return Vector3(0, 0, 0);
	}
}

//Operator
Matrix4 Matrix4::operator*(Matrix4 const& mat)
{
    float index[16];

	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

			index[4*i + j] = matrix[i*4] * mat.matrix[j] + matrix[i*4+1] * mat.matrix[j+4] + matrix[i*4+2] * mat.matrix[j+8] + matrix[i*4+3] * mat.matrix[j+12];
		}
	}

    return Matrix4(index);
}

Vector3 Matrix4::operator*(Vector3 const& v)// to multiplie a Vector3 with a Matrix4, this code act like Vector3 is Vector4 with the same 3 first component and with a 1 at last.
{
    float x, y, z;
    x = matrix[0] * v.x + matrix[1] * v.y + matrix[2] * v.z + matrix[3];
    y = matrix[4] * v.x + matrix[5] * v.y + matrix[6] * v.z + matrix[7];
    z = matrix[8] * v.x + matrix[9] * v.y + matrix[10] * v.z + matrix[11];
    return Vector3(x, y, z);
}//