#pragma once
#include "DxLib.h"
#include <math.h>

class CMyMatrix
{
public:
	//単位行列を取得
	static MATRIX GetIdentityMatrix();
	//平行移動行列を取得
	static MATRIX GetTranslateMatrix(VECTOR a);
	//拡縮行列を取得
	static MATRIX GetScalMatrix(VECTOR a);
	//X軸回転行列を取得（回転値ラジアン）
	static MATRIX GetPitchMatrix(float rot);	
	//Y軸回転行列を取得（回転値ラジアン）
	static MATRIX GetYawMatrix(float rot);	
	//Z軸回転行列を取得（回転値ラジアン）
	static MATRIX GetRollMatrix(float rot);	
	//足し算する行列
	static MATRIX MatAdd(MATRIX a, MATRIX b);
	//引数で渡された行列をスカラー倍する（引数行列とスカラー値）
	static MATRIX MatScale(MATRIX a, float s);	
	//掛け算をする
	static MATRIX MatMult(MATRIX a, MATRIX b);
	//行列Xベクトルを行う(変換計算)
	static VECTOR MatTransform(MATRIX a, VECTOR b);
	//行列転値を行う
	static MATRIX MatTranspose(MATRIX a);

};


