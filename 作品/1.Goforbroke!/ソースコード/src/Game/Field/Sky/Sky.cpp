#include "Sky.h"

const char AM_SKY_MODEL_PATH[] = { "data/Game/Field/Sky/AmSky.x" };
const char PM_SKY_MODEL_PATH[] = { "data/Game/Field/Sky/PmSky.x" };

CSky::CSky()
{
	Init();
}

CSky::~CSky()
{
	Exit();
}

//初期化
void CSky::Init()
{
	m_iAmHndl = -1;
	m_iPmHndl = -1;
}

//ロード
void CSky::Load()
{
	if (m_iAmHndl == -1)
		m_iAmHndl = MV1LoadModel(AM_SKY_MODEL_PATH);

	if (m_iPmHndl == -1)
		m_iPmHndl = MV1LoadModel(PM_SKY_MODEL_PATH);
}

//ループ
void CSky::Loop()
{
	MV1SetScale(m_iAmHndl, VGet(30.0f, 30.0f, 30.0f));
	MV1SetScale(m_iPmHndl, VGet(30.0f, 30.0f, 30.0f));
}

//午前描画
void CSky::AmDraw()
{
	MV1DrawModel(m_iAmHndl);
}

//午後描画
void CSky::PmDraw()
{
	MV1DrawModel(m_iPmHndl);
}

void CSky::Exit()
{
	MV1DeleteModel(m_iAmHndl);
	MV1DeleteModel(m_iPmHndl);
}








