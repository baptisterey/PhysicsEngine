#include "Matrix4.h"


//Constructor
Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
	{
        if (i%5 == 0){matrix.push_back(1);}
		else { matrix.push_back(0); }
	}
}

Matrix4::Matrix4(Matrix4& copyMatrix)
{
    for (int i = 0; i < 16; i++) { matrix.push_back(copyMatrix.matrix[i]); }
}

Matrix4::Matrix4(std::vector<float> matrixTable)
{
	for (int i = 0; i < 16; i++)
	{
		if (i % 5 == 0) { matrix.push_back(1); }
		else { matrix.push_back(0); }
	}

	for (int i = 0; i < matrixTable.size(); i++)
	{
		matrix[i] = matrixTable[i];
	}
}


//Methode
float Matrix4::matrix4Det()
{

	Matrix3 m[4];
	m[0] = Matrix3(matrix[1], matrix[2], matrix[3], matrix[5], matrix[6], matrix[7], matrix[9], matrix[10], matrix[11]);
	m[1] = Matrix3(matrix[0], matrix[2], matrix[3], matrix[4], matrix[6], matrix[7], matrix[8], matrix[10], matrix[11]);
	m[2] = Matrix3(matrix[0], matrix[1], matrix[3], matrix[4], matrix[5], matrix[7], matrix[8], matrix[9], matrix[11]);
	m[3] = Matrix3(matrix[0], matrix[1], matrix[2], matrix[4], matrix[5], matrix[6], matrix[8], matrix[9], matrix[10]);



	return  matrix[13] * m[1].matrix3Det() + matrix[15] * m[3].matrix3Det() - matrix[12] * m[0].matrix3Det() - matrix[14] * m[2].matrix3Det();
}

Matrix4 Matrix4::matrix4Inverse()
{
    float invDet;
	std::vector<float> index;
    Matrix3 m[16];

	//transposé de la comatrice
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

	if (matrix4Det() != 0) {
		invDet = 1 / matrix4Det();

		for (int i = 0; i < 16; i++)
		{
			int signe = (i / 4) + 1 + (i % 4) * 4;
			index.push_back(invDet * m[i].matrix3Det() * pow(-1, signe + i+1) );
		}

		return Matrix4(index);
	}
	return Matrix4();
}

Matrix4 Matrix4::matrix4Transpose() { 

	std::vector<float> index;
	

	for (int i = 0; i < 16; i++)
	{
		index.push_back(matrix[(i / 4) + (i % 4) * 4]);
	}

    return Matrix4(index);
}

Matrix4 Matrix4::PerspectiveFov(float FOV, float Aspect, float ZNear, float ZFar)
{
	float Width = 1.0f / tanf(FOV / 2.0f), Height = Aspect / tanf(FOV / 2.0f);
	std::vector<float> index;

	index.push_back(Width);
	index.push_back(0.0f);
	index.push_back(0.0f);
	index.push_back(0.0f);

	index.push_back(0.0f);
	index.push_back(Height);
	index.push_back(0.0f);
	index.push_back(0.0f);

	index.push_back(0.0f);
	index.push_back(0.0f);
	index.push_back(ZFar / (ZNear - ZFar));
	index.push_back(ZFar * ZNear / (ZNear - ZFar));

	index.push_back(0.0f);
	index.push_back(0.0f);
	index.push_back(-1.0f);
	index.push_back(0.0f);

	return Matrix4(index);
}

Matrix4 Matrix4::LookAt(const Vector3& Eye, const Vector3& At, const Vector3& Up)
{
	Vector3 XAxis, YAxis, ZAxis;
	ZAxis = Vector3::Normalized(Eye - At);
	XAxis = Vector3::Normalized(Vector3::Cross(Up, ZAxis));
	YAxis = Vector3::Normalized(Vector3::Cross(ZAxis, XAxis));

	std::vector<float> index;
	index.push_back(XAxis.x);
	index.push_back(XAxis.y);
	index.push_back(XAxis.z);
	index.push_back(-Vector3::Dot(XAxis, Eye));

	index.push_back(YAxis.x);
	index.push_back(YAxis.y);
	index.push_back(YAxis.z);
	index.push_back(-Vector3::Dot(YAxis, Eye));

	index.push_back(ZAxis.x);
	index.push_back(ZAxis.y);
	index.push_back(ZAxis.z);
	index.push_back(-Vector3::Dot(ZAxis, Eye));

	index.push_back(0.0f);
	index.push_back(0.0f);
	index.push_back(0.0f);
	index.push_back(1.0f);

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
    std::vector<float> index;

	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

			index.push_back(matrix[i*4] * mat.matrix[j] + matrix[i*4+1] * mat.matrix[j+4] + matrix[i*4+2] * mat.matrix[j+8] + matrix[i*4+3] * mat.matrix[j+12]);
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