#pragma once
#include <DxLib.h>
#include <math.h>

class CMath 
{
public:
	//角度を取得(Y軸)
	float GetAngleY(VECTOR vec1, VECTOR vec2);
	//角度を取得(X軸)
	float GetAngleX(VECTOR vec1, VECTOR vec2);
	//角度を取得(Z軸)
	float GetAngleZ(VECTOR vec1, VECTOR vec2);
	//絶対値の取得
	float MyAbsf(float i_fNum);

};





