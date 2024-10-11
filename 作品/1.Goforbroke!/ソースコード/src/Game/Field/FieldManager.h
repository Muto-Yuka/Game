#pragma once
#include "Ground/Ground.h"
#include "Sky/Sky.h"

//フィールドをまとめるマネージャークラス
class CFieldManager
{
	enum tagSceneID
	{
		SCENE_AM = 2,	//午前
		SCENE_PM,		//午後

	}m_eSceneID;

	CGround cGround;
	CSky	cSky;

public:
	void Init();		//初期化
	void Load();		//ロード
	void Loop();		//ループ
	void Draw(int m_eSceneID);		//描画 引数：SceneID朝か夜か受け取る
	void Exit();		//破棄

	//当たり判定用（相手の座標と半径）return:押し戻す距離と方向
	VECTOR	HitCheck(VECTOR anotherPos, float anotherRadius)
	{ return cGround.HitCheck(anotherPos, anotherRadius);};

};



