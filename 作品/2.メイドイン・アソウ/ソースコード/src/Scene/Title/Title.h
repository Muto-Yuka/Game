#pragma once
#include "../SceneBase.h"

class CTitle :public CSceneBase
{
	float m_fVolume;
public:
	CTitle();
	~CTitle();

	int  Loop();		//ループ 
	void Draw();		//描画

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Exit();		//破棄
	void Next();		//次へ

	//音量調整
	void Volume();

};




