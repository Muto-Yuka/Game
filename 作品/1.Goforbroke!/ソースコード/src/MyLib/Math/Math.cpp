#include "Math.h"

//角度を取得（X軸）
float CMath::GetAngleX(VECTOR vec1, VECTOR vec2)
{
	return -(atan2f(vec1.y - vec2.y, vec1.z - vec2.z));
}

//角度を取得（Y軸）
float CMath::GetAngleY(VECTOR vec1, VECTOR vec2)
{
	return atan2f(vec1.x - vec2.x, vec1.z - vec2.z);
}

//角度を取得（Z軸）
float CMath::GetAngleZ(VECTOR vec1, VECTOR vec2)
{
	return -(atan2f(vec1.y - vec2.y, vec1.x - vec2.x));
}

//絶対値の取得
float CMath::MyAbsf(float i_fNum)
{
	if (i_fNum < 0.0f)
	{
		i_fNum = -i_fNum;
	}
	return i_fNum;
}




