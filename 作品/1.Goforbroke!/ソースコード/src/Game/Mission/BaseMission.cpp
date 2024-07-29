#include "BaseMission.h"
#include "DxLib.h"

//食料ゲージイラストをずらす
#define SHIFT_ITEM_PICTURE	(28)



//コンストラクタ
CBaseMission::CBaseMission()
{
	//ハンドルに保存				フォントの種類　サイズ　太さ　タイプ
	FontHandle = CreateFontToHandle("HGP行書体", 40, 10, DX_FONTTYPE_NORMAL);
	Init();
}

//初期化
void CBaseMission::Init()
{
	//画像ハンドル初期化
	for (int i = 0; i < 5; i++)
	{
		m_iOnHndl[i] = -1;
		m_iUnderHndl[i] = -1;

	}

	m_iMissionCnt = 0;
	m_bClear = false;
	m_iDrawNum = GAUGE_NUM;
	HitFlg = false;
	m_iDrawPictureY = 0;
	m_iWordX = MISSION_WORD_X;
	m_iWordY = MISSION_WORD_Y;

}

//ループ
void CBaseMission::Step()
{
	m_iMissionCnt++;

	//ミッション開始から五秒経ったら文字を右上へ移動
	if (m_iMissionCnt > 300)
	{
		if (m_iWordX < 680)
			m_iWordX += 2;		//速さを足す
		if (m_iWordY > 0)
			m_iWordY -= 2;
	}

}

//常に描画
void CBaseMission::AlwaysDraw()
{
	//食料ゲージ描画(どれくらいおなかがへっているかわかるように暗く描画)
	for (int i = 0; i < GAUGE_NUM; i++)
		DrawGraph(i * SHIFT_ITEM_PICTURE, m_iDrawPictureY, m_iUnderHndl[i], true);

	for (int k = 0; k < m_iDrawNum; k++)
		DrawGraph(k * SHIFT_ITEM_PICTURE, m_iDrawPictureY, m_iOnHndl[k], true);


}


//終了
void CBaseMission::Exit()
{
	for (int i = 0; i < GAUGE_NUM; i++)
	{
		DeleteGraph(m_iOnHndl[i]);
		DeleteGraph(m_iUnderHndl[i]);

	}

	DeleteFontToHandle(FontHandle);
}






