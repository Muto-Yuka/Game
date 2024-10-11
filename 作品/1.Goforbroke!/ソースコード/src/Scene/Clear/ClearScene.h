#pragma once

class CClearScene
{
	int m_iHndl;	//画像ハンドル

	enum tagClear
	{
		SCENE_INIT,		//初期化
		SCENE_LOAD,		//ロード
		SCENE_STEP,		//各処理
		SCENE_EXIT,		//破棄
		SCENE_NEXT,		//次へ
	}m_eClearID;

public:
	CClearScene();
	~CClearScene();

	bool Loop();		//ループ

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Draw();		//描画
	void Exit();		//破棄
	void Next();		//次へ

};