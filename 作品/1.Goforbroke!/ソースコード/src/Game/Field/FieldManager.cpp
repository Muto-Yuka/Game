#include "FieldManager.h"

//初期化
void CFieldManager::Init()
{
	cGround.Init();
	cSky.Init();
}

//ロード
void CFieldManager::Load()
{
	m_eSceneID = SCENE_AM;

	cGround.Load();
	cSky.Load();
}

//ループ
void CFieldManager::Loop()
{
	cGround.Loop();
	cSky.Loop();
}

//描画
void CFieldManager::Draw(int m_eSceneID)
{
	cGround.Draw();

	switch (m_eSceneID)
	{
	case SCENE_AM:
		cSky.AmDraw();
		break;

	case SCENE_PM:
		cSky.PmDraw();
		break;
	}
}

//破棄
void CFieldManager::Exit()
{
	cGround.Exit();
	cSky.Exit();
}





