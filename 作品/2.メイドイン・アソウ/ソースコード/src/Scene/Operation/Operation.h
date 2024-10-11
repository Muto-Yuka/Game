#pragma once
#include "../SceneBase.h"

static const int OPERATION_NUM = 2;	//表示する説明画像の数 縦の枚数

class COperation : public CSceneBase
{
public:
	COperation();
	~COperation();

	int Loop();		//ループ 
	void Draw();		//描画

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Exit();		//破棄
	void Next();		//次へ

};




