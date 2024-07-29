#pragma once
#include "DxLib.h"
#include "../Item/ItemManager.h"

class CMission
{
private:
	//**画像ハンドル**
	int m_iHndl;			//ミッション２ｄ画像ハンドル
	int m_iPaperHndl;		//ミッション用紙描画

	int count;				//フレーム数カウント
	int m_iTransparency;	//画像透明度 0=透明　255=不透明
	bool m_bDraw;			//２ｄ画像を描画しているかどうか　true:描画中　false:描画していない
	int m_iMissionCnt;
	int DrawCount;			//２d画像を描画する回数カウント
	int L_DrawX, L_DrawY;	//画像の左側ｘ座標、左側ｙ座標
	int R_DrawX, R_DrawY;	//画像の右側ｘ座標、右側ｙ座標
	bool SceneId;			// true=一日目 false=二日目
	bool MissionTitle;		//ミッション内容描画するかしないか true:する　false:しない

//**ミッションアイテム変数**
	int m_iStraw;			//藁の個数
	int m_iBranch;			//枝の個数
	int m_iIvy;				//ツタの個数

	//アイテムのクリアフラグを入れる構造体
	struct ItemClearFrg
	{
		bool s_bStraw = false;
		bool s_bBranch = false;
		bool s_bIvy = false;
	};

	ItemClearFrg m_sItemClearFrg;

public:

	//コンストラクタ.デストラクタ
	CMission();
	~CMission();

	//初期化
	void Init();
	//データ関連のロード
	void Load();
	//毎フレーム呼ぶ処理
	void Step(CItemManager& cItemManager);
	//常に描画
	void Draw();
	//終了
	void Exit();

	//ミッション透過処理
	void StepMission();
	//ミッション中のみ描画
	void MissionDraw();
	//ミッション内容を右上に移動する
	void MoveMIssion();
	//ミッション内容文章を表示する
	void StringMission();

		//一日目セット   true=一日目　false=二日目
	void SetDay1Scene() { SceneId = true; }
	void SetDay2Scene() { SceneId = false; }

	//ミッションクリアかどうか　true:クリア　false:ミッション失敗
	bool GetMissionClearFrg();


};


