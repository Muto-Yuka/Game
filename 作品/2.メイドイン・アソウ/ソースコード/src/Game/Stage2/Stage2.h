#pragma once
#include "../GameBase.h"

//釘打ち
class CStage2 : public CGameBase
{
private:
	//イラスト関連
	enum tagIMAGE
	{
		tag_BG,			//背景
		tag_DESK,		//机
		tag_HAMMER,		//ハンマー
		tag_NAIL,		//釘
		tag_SPACE,		//スペースキー

		tag_NUM
	};
	int		m_iGraph[tag_NUM];	//全画像格納
	int		m_iKeyCount;		//キー押したカウント
	int		m_iTime;			//制限時間
	float	m_fRot;				//ハンマーの回転角度

public:
	CStage2();
	~CStage2();

	void Init();		//初期化
	void Load();		//ロード
	int  Step();		//ステップ
	void Exit();		//破棄
	void Draw();		//描画

	//リザルト情報を返す 0:待機　1:クリア　2:ゲームオーバー
	int GetResult();	

};




