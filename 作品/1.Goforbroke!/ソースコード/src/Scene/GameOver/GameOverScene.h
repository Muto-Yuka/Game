#pragma once

class CGameOverScene
{
private:
	int m_iHndl;		//通常ゲームオーバー
	int m_iWaterlack;	//水分不足ハンドル
	int m_iWaterplace;	//水場の条件未達成

public:

	//コンストラクタ・デストラクタ
	CGameOverScene();
	~CGameOverScene();

	//通常描画処理
	void Draw();
	//水分不足
	void LackDraw();
	//未達成
	void PlaceDraw();
	//初期化
	void Init(void);
	//終了処理
	void Exit();
	//データロード
	void Load();
	//毎フレーム呼ぶ処理
	void Step();

};