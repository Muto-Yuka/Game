#pragma once
#include "DxLib.h"
#include <math.h>

class CMyVector 
{
public:
	//ベクトル作成
	VECTOR VecCreate(VECTOR PosA, VECTOR PosB);
	//ベクトルの長さ
	float VecLong(VECTOR PosA, VECTOR PosB);
	//ベクトルの足し算
	VECTOR VecAdd(VECTOR vecA, VECTOR vecB);
	//ベクトルの引き算
	VECTOR VecSubtract(VECTOR vecA, VECTOR vecB);
	//ベクトルのスカラー倍
	VECTOR VecScale(VECTOR vec, float scale);
	//ベクトルの内積
	float VecDot(VECTOR vecA, VECTOR vecB);
	//ベクトルの外積
	VECTOR VecCross(VECTOR vecA, VECTOR vecB);
	//ベクトルの正規化
	VECTOR VecNormalize(VECTOR vec);
	//ベクトル×行列
	VECTOR Transform(MATRIX mat, VECTOR vec);

};


