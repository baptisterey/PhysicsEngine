#include "Matrix3.h"





//Constructor
Matrix3::Matrix3()
{
    for (int i = 0; i < 9; i++)
	{ 
		if (i%4 == 0){matrix[i] = 1;}
        else{matrix[i] = 0;}
	}
}

Matrix3::Matrix3(float matrixTable[9])
{
    for (int i = 0; i < 9; i++)
	{
        if (i%4 == 0){matrix[i] = 1;}
        else{matrix[i] = 0;}
	}

	{
        for (int i = 0; i < 9; i++) 
		{ 
			matrix[i] = matrixTable[i]; 
		}
	}
}

Matrix3::Matrix3(float i0, float i1, float i2, float i3, float i4, float i5, float i6, float i7, float i8)
{
    matrix[0] = i0;
    matrix[1] = i1;
    matrix[2] = i2;

    matrix[3] = i3;
    matrix[4] = i4;
    matrix[5] = i5;

    matrix[6] = i6;
    matrix[7] = i7;
    matrix[8] = i8;
}

Matrix3::Matrix3(Matrix3& copyMatrix) {
    for (int i = 0; i < 9; i++)
	{
		matrix[i] = copyMatrix.matrix[i];
	}
}

//Methode
float Matrix3::matrix3Det()
{
    return matrix[0] * matrix[4] * matrix[8] + 
		   matrix[3] * matrix[7] * matrix[2] +
           matrix[6] * matrix[1] * matrix[5] - 
		   matrix[0] * matrix[7] * matrix[5] -
           matrix[2] * matrix[4] * matrix[6] - 
		   matrix[3] * matrix[1] * matrix[8];
}

Matrix3 Matrix3::matrix3Inverse()
{
    float i0, i1, i2, i3, i4, i5, i6, i7, i8, invDet;
    invDet = 1 / matrix3Det();
    i0 = invDet * (matrix[4] * matrix[8] - matrix[5] * matrix[7]);
    i1 = invDet * (matrix[2] * matrix[7] - matrix[1] * matrix[8]);
    i2 = invDet * (matrix[1] * matrix[5] - matrix[2] * matrix[4]);

    i3 = invDet * (matrix[5] * matrix[6] - matrix[3] * matrix[8]);
    i4 = invDet * (matrix[0] * matrix[8] - matrix[2] * matrix[6]);
    i5 = invDet * (matrix[2] * matrix[3] - matrix[0] * matrix[5]);

    i6 = invDet * (matrix[3] * matrix[7] - matrix[4] * matrix[6]);
    i7 = invDet * (matrix[1] * matrix[6] - matrix[0] * matrix[7]);
    i8 = invDet * (matrix[0] * matrix[4] - matrix[1] * matrix[3]);

	return Matrix3(i0, i1, i2, i3, i4, i5, i6, i7, i8);
}

Matrix3 Matrix3::matrix3Transpose() {

	return Matrix3(matrix[0], matrix[3], matrix[6], matrix[1], matrix[4], matrix[7], matrix[2],
                   matrix[5], matrix[8]);
}

//Operator
Matrix3 Matrix3::operator*(Matrix3 const& mat)
{
    float index[9];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            index[3 * i + j] = matrix[3* i] * mat.matrix[j] + matrix[3*i + 1] * mat.matrix[j + 3] +  matrix[3*i + 2] * mat.matrix[j + 6];
        }
    }

    return Matrix3(index);
}

Vector3 Matrix3::operator*(Vector3 const& v)
{
    float x, y, z;
    x = matrix[0] * v.x + matrix[1] * v.y + matrix[2] * v.z;
    y = matrix[3] * v.x + matrix[4] * v.y + matrix[5] * v.z;
    z = matrix[6] * v.x + matrix[7] * v.y + matrix[8] * v.z;
    return Vector3(x, y, z);
}