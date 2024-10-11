#pragma once

class CSceneBase
{
protected:
	int	m_iHndl;			//画像ハンドル

	enum tagScene
	{
		SCENE_INIT,		//初期化
		SCENE_LOAD,		//ロード
		SCENE_STEP,		//各処理
		SCENE_EXIT,		//破棄
		SCENE_NEXT,		//次へ
	}m_eSceneID;

public:
	virtual int Loop() = 0;
	virtual void Draw() = 0;

	void Init();		//初期化
	void Load();		//ロード
	void Step();		//ステップ
	void Exit();		//破棄
	void Next();		//次へ

};




