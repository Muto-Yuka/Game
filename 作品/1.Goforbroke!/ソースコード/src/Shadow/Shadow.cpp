#include "Shadow.h"

void CShadow::Init()
{
	//影＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//シャドウマップを作成する（サイズは解像度に関係する）
	//サイズは必ず２べき乗で
	shadowHndl = MakeShadowMap(2048, 2048);

	//光の方向を設定する	  シャドウマップハンドル、斜めの影ができる
	SetShadowMapLightDirection(shadowHndl, VGet(-1.5f, -3.0f, -2.8f));

	//影を描画する範囲をセット（エリアを決めないと処理がすごく重たくなる）
	//シャドウマップハンドル、
	SetShadowMapDrawArea	//設定した座標の内側にいるときだけ影が反映
	(shadowHndl, VGet(-50.0f, -1.0f, -50.0f), VGet(250.0f, 10.0f, 200.0f));
	//(shadowHndl, VGet(-50.0f, -1.0f, -50.0f), VGet(150.0f, 10.0f, 100.0f));
	//				範囲の最小値、			範囲の最大値


}

void CShadow::Draw()
{
	//影の描画処理
	ShadowMap_DrawSetup(shadowHndl);//影の描画前に必ず行う
	cSceneManager.Draw();
	ShadowMap_DrawEnd();			//影の描画後に必ず行う
	//通常の描画処理
	SetUseShadowMap(0, shadowHndl);	//反映させる影のハンドルと０～２のスロット番号セット
	cSceneManager.Draw();
	SetUseShadowMap(0, -1);			//終わったら使用したスロット番号をー１で終わらせる

}

void CShadow::Exit()
{
	//シャドウマップ破棄
	DeleteShadowMap(shadowHndl);

}

void CShadow::Loop()
{
	//計算処理
	cSceneManager.Loop();

}


