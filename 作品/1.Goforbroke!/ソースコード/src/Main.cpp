#include <DxLib.h>
#include <crtdbg.h>
#include "Scene/SceneManager.h"
#include "MyLib/FPS/FPS.h"
#include "MyLib/Input/Input.h"

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリ初期化処理・設定
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// メモリリークチェック用
	ChangeWindowMode(TRUE);											// ウィンドウモードで起動
	SetGraphMode(1280, 720, 32);									// ウィンドウサイズ
	SetMainWindowText("Goforbroke!!");								// 起動時に表示される文字
	if (DxLib_Init() == -1) return -1;								// Dxlib初期化関数
	SetDrawScreen(DX_SCREEN_BACK);									// スクリーン設定
	SetTransColor(255, 0, 255);										// 透過色設定

	//フォント読み込み 
	AddFontResourceEx("data/font/Font.TTF", FR_PRIVATE, NULL);

	//シーン
	CSceneManager cSceneManager;
	CInput cInput;

	//入力初期化
	cInput.Init();
	cSceneManager.Init();
	CFPS::Init();
	
	// ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);
		
		// エスケープキーが押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		//ＦＰＳが規定の時間に達してない
		if (!CFPS::CheckNext()) continue;

		ClearDrawScreen();		// 画像クリア

		//fps計算処理
		CFPS::Step();

		//ループ処理
		cSceneManager.Loop();
		//入力ステップ
		cInput.Update();
		//描画
		cSceneManager.Draw();

		//FPS描画
		//CMyFPS::DrawFps();


		ScreenFlip();			// フリップ関数
		
	}
	
	cSceneManager.Exit();
	RemoveFontResourceEx("data/font/Font.TTF", FR_PRIVATE, NULL);

	DxLib_End();			
	return 0;				
}


