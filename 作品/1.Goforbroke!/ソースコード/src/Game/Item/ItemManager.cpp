#include "ItemManager.h"

//コンストラクタ
CItemManager::CItemManager()
{

}

//デストラクタ
CItemManager::~CItemManager()
{
	Exit();
}

//初期化
void CItemManager::Init(CPlayer& cPlayer)
{
	cApple.Init(cPlayer);
	cBranch.Init();
	cStraw.Init();
	cTree.Init();
	cWater.Init();
	//cLear.Init();
	//cTent.Init();

}

//ロード
void CItemManager::Load()
{
	cApple.Load();
	cBranch.Load();
	cStraw.Load();
	cTree.Load();
	cWater.Load();
	//cLear.Load();
	//cTent.Load();

}

//ループ
void CItemManager::Step()
{
	cApple.Step();
	cBranch.Step();
	cStraw.Step();
	cTree.Step();
	cWater.Step();
	//cLear.Step();
	//cTent.Step();

	//当たり判定

}

//描画
void CItemManager::Draw()
{
	cApple.Draw();
	cBranch.Draw();
	cStraw.Draw();
	cTree.Draw();
	cWater.Draw();
	//cLear.Draw();
	//cTent.Draw();

}

//終了
void CItemManager::Exit()
{
	cApple.Exit();
	cBranch.Exit();
	cStraw.Exit();
	cTree.Exit();
	cWater.Exit();
	//cLear.Exit();
	//cTent.Exit();

}

//各当たり判定球描画
void CItemManager::MyDbug()
{
	////リンゴの当たり判定描画
	//for (int i = 0; i < APPLE_NUM; i++)
	//DrawSphere3D(cApple.m_cApple[i].GetPosition(), cApple.m_cApple[i].GetRadius(), 16, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
	//水場が壊れたら描画
	if (!cWater.GetSurvivalFrg())
	{
		//水飲み場の当たり判定描画
		DrawSphere3D(cWater.GetPosition(), cWater.GetRadius(), 16, GetColor(0, 0, 255), GetColor(255, 255, 255), false);

	}
	////木の枝の当たり判定
	//DrawSphere3D(cBranch.GetPosition(), cBranch.GetRadius(), 16, GetColor(0, 255, 0), GetColor(255, 255, 255), false);
	////わらの当たり判定
	//DrawSphere3D(cStraw.GetPosition(), cStraw.GetRadius(), 16, GetColor(0, 255, 0), GetColor(255, 255, 255), false);
}

//リザルトへ行くか判断 true:リザルトへ false:リザルトに行かない
bool CItemManager::GetResultFrg()
{
	////食料ゲージがなくなった
	//if (cApple.GetResultFrg())
	//	return true;

	//水分ゲージがなくなった
	if (cWater.GetResultFrg())
		return true;


	return false;
}


//水場が達成できているかどうか true:達成　false:未達成
bool CItemManager::GetWaterClearFrg()
{
	//８０％以上なら
	if (cWater.GetWaterClearFrg() > 4)
		return true;


	return false;
}

