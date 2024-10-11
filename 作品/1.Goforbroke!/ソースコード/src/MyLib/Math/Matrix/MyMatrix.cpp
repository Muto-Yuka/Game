#include "MyMatrix.h"

//単位行列を取得
MATRIX CMyMatrix::GetIdentityMatrix()
{
	MATRIX matrix;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (i == k)
				matrix.m[i][k] = 1;
			else
				matrix.m[i][k] = 0;
		}
	}
	return matrix;
}

//平行移動行列を取得
MATRIX CMyMatrix::GetTranslateMatrix(VECTOR a)
{
	MATRIX matrix = GetIdentityMatrix();
	matrix.m[0][3] = a.x;
	matrix.m[1][3] = a.y;
	matrix.m[2][3] = a.z;

	return matrix;
}

//拡縮行列を取得
MATRIX CMyMatrix::GetScalMatrix(VECTOR a)
{
	MATRIX matrix = GetIdentityMatrix();
	matrix.m[0][0] = a.x;
	matrix.m[1][1] = a.y;
	matrix.m[2][2] = a.z;

	return matrix;
}

//X軸回転行列を取得 //回転値ラジアン
MATRIX CMyMatrix::GetPitchMatrix(float rot)
{
	MATRIX matrix = GetIdentityMatrix();
	matrix.m[1][1] = cosf(rot);
	matrix.m[1][2] = -sinf(rot);
	matrix.m[2][1] = sinf(rot);
	matrix.m[2][2] = cosf(rot);

	return matrix;
}

//Y軸回転行列を取得 //回転値ラジアン
MATRIX CMyMatrix::GetYawMatrix(float rot)
{
	MATRIX matrix = GetIdentityMatrix();
	matrix.m[0][0] = cosf(rot);
	matrix.m[2][0] = -sinf(rot);
	matrix.m[0][2] = sinf(rot);
	matrix.m[2][2] = cosf(rot);

	return matrix;
}
//Z軸回転行列を取得		//回転値ラジアン
MATRIX CMyMatrix::GetRollMatrix(float rot)
{
	MATRIX matrix = GetIdentityMatrix();
	matrix.m[0][0] = cosf(rot);
	matrix.m[0][1] = -sinf(rot);
	matrix.m[1][0] = sinf(rot);
	matrix.m[2][2] = cosf(rot);

	return matrix;
}

//足し算する行列
MATRIX CMyMatrix::MatAdd(MATRIX a, MATRIX b)
{
	MATRIX matrix;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			matrix.m[i][k] = a.m[i][k] + b.m[i][k];
		}
	}
	return matrix;
}

//引数で渡された行列をスカラー倍する//引数行列とスカラー値
MATRIX CMyMatrix::MatScale(MATRIX a, float scale)
{
	MATRIX matrix;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			matrix.m[i][k] = a.m[i][k] * scale;
		}
	}
	return matrix;
}

//掛け算をする
MATRIX CMyMatrix::MatMult(MATRIX a, MATRIX b)
{
	MATRIX matrix;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				matrix.m[i][j] += (a.m[i][k] * b.m[k][j]);
			}
		}
	}
	return matrix;
}

//行列Xベクトルを行う(変換計算)
VECTOR CMyMatrix::MatTransform(MATRIX a, VECTOR b)
{
	float work[4] = { 0 };
	float result_buf[4] = { 0 };
	VECTOR result_vec;
	work[0] = b.x;
	work[1] = b.y;
	work[2] = b.z;
	work[3] = 1;

	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			result_buf[i] += (a.m[i][k] * work[k]);
		}
	}
	result_vec.x = result_buf[0];
	result_vec.y = result_buf[1];
	result_vec.z = result_buf[2];

	return result_vec;
}

//行列転値を行う
MATRIX CMyMatrix::MatTranspose(MATRIX a)
{
	MATRIX matrix = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix.m[j][i] = a.m[i][j];
		}
	}

	return matrix;
}





