#include "Mission.h"

static const char MODEL_PATH[] = { "data/Game/Mission/Mission.png" };
static const char M_PAPER_PATH[] = { "data/Game/Mission/Paper.png" };

//ミッション２ｄ画像が何回大きく画面に表示するか　その後は常に描画しておく
#define MISSION_DRAW_NUM  (1)
//２ｄ画像初期値　左X
#define L_DRAW_X		(0)
//２ｄ画像初期値　左Y
#define L_DRAW_Y		(40)
//２ｄ画像初期値　右X
#define R_DRAW_X		(1280)
//２ｄ画像初期値　右1Y
#define R_DRAW_Y		(190)

//ミッションの移動する速さ
#define MOVE_MISSION_SPEED	(2)

//ミッションアイテムを集める数
#define M_STRAW		(12)	//藁
#define M_BRANCH	(6)		//枝
#define M_IVY		(4)		//ツタ

CMission::CMission()
{

}

CMission::~CMission()
{
	Exit();
}

//初期化
void CMission::Init()
{
	m_iHndl = -1;
	m_iPaperHndl = -1;
	m_iTransparency = 0;
	count = 0;
	m_bDraw = false;
	m_iMissionCnt = 0;
	DrawCount = 0;
	L_DrawX = L_DRAW_X;
	L_DrawY = L_DRAW_Y;
	R_DrawX = R_DRAW_X;
	R_DrawY = R_DRAW_Y;

	//ミッションアイテム初期化
	m_iStraw = 0;
	m_iBranch = 0;
	m_iIvy = 0;

	MissionTitle = true;

}

//ロード
void CMission::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(MODEL_PATH);
	}

	if (m_iPaperHndl == -1)
	{
		m_iPaperHndl = LoadGraph(M_PAPER_PATH);
	}

}

//毎フレーム呼ぶ処理
void CMission::Step(CItemManager& cItemManager)
{
	count++;
	m_iMissionCnt++;

	//ミッション透過処理
	StepMission();

	//わらの数を取得してくる
	m_iStraw = cItemManager.GetStrawNum();

}

//描画
void CMission::Draw()
{
	//一日目
	if (SceneId == true)
	{
		if (MissionTitle == true)
		{
			DrawFormatString(445, 200, GetColor(165, 42, 42), "<１日目：夜襲ってくる敵に注意せよ>");
		}
	}
	else 
	{
		if (MissionTitle == true)
		{
			DrawFormatString(445, 200, GetColor(165, 42, 42), "<２日目：水場を50％以上にせよ>");
		}
	}

	//指定の回数分ミッションを描画する
	if (DrawCount == MISSION_DRAW_NUM)
	{
		//指定回数描画した後　常に描画しだしたら
		if (m_iTransparency >= 255)
		{
			//ミッション内容を右上に描画する
			StringMission();
		}
	}
	//ミッションを描画する
	MissionDraw();

}
//終了
void CMission::Exit()
{
	DeleteGraph(m_iHndl);
	DeleteGraph(m_iPaperHndl);

}

//ミッション透過処理 透過用変数に値を代入する
void CMission::StepMission()
{

	//指定の回数分ミッションを描画する
	if (DrawCount != MISSION_DRAW_NUM)
	{
		//ミッションの透過を繰り返す処理
		//１００フレームごとに透過するしないを交互に繰り返す
		if (count == 100)
		{

			if (m_bDraw == true)
			{
				m_bDraw = false;
				DrawCount++;
			}
			else
				m_bDraw = true;

			count = 0;
		}

		if (m_bDraw == true)	//true（描画中）だったら透明に 0=透明
			m_iTransparency -= 3;
		else
			m_iTransparency += 3; //false（何も描画してない）だったら透明度を上げる　255=不透明

	}
	else //常に描画させる
	{
		m_iTransparency += 3; //false（何も描画してない）だったら透明度を上げる　255=不透明

		//指定回数描画した後　常に描画しだしたら
		if (m_iTransparency >= 255)
		{
			//画像右上に移動
			MoveMIssion();
			MissionTitle = false;

		}

	}
}

//ミッションの２ｄ画像描画
void CMission::MissionDraw()
{
	//ミッション画面の描画処理
	//ブレンドモードを変更 ０＝透明　２５５＝不透明
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_iTransparency);
	//				   0        40      1280     190
	DrawExtendGraph(L_DrawX, L_DrawY, R_DrawX, R_DrawY, m_iHndl, true);
	//設定を元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//ミッション画像を右上に移動する
void CMission::MoveMIssion()
{
	//DrawExtendGraph(900, 0, 1280, 50, m_iHndl, true)に設定する

	//左上
	if (L_DrawX <= 900)
		L_DrawX += MOVE_MISSION_SPEED + 8;
	//左下
	if (L_DrawY >= 0)
		L_DrawY -= MOVE_MISSION_SPEED;
	//右下
	if (R_DrawY >= 50)
		R_DrawY -= MOVE_MISSION_SPEED;

}

//ミッション内容の分を表示する
void CMission::StringMission()
{

	//アイテムをすべて取り終わったらずっと０表示
	if (m_iStraw >= M_STRAW)
	{
		//藁のミッションクリア
		m_sItemClearFrg.s_bStraw = true;
		m_iStraw = M_STRAW;
	}

	if (SceneId == true)
	{
		DrawFormatString(900, 60, GetColor(165, 42, 42), "《襲ってくる敵に注意せよ》");
	}
	else
	{
		DrawFormatString(900, 60, GetColor(165, 42, 42), "《水場を50%以上にせよ》");
	}
}


//**ゲッター・セッター**
//ミッション成功かどうか　true:成功 false:失敗
bool CMission::GetMissionClearFrg()
{
	//わらミッションが失敗なら
	if (m_sItemClearFrg.s_bStraw == false)
		return false;
	//枝ミッションが失敗なら
	if (m_sItemClearFrg.s_bBranch == false)
		return false;
	//つたミッションが失敗なら
	if (m_sItemClearFrg.s_bIvy == false)
		return false;


	//すべて成功してたらtrueを返す
	return true;
}


