#include "DxLib.h"
#include "Scene/SceneManager.h"
#include "MyLib/Input/Input.h"
#include "MyLib/Fps/Fps.h"
#include "WindowsSize.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// メモリリークチェック用
	ChangeWindowMode(FALSE);											// ウィンドウモードで起動
	SetGraphMode(WINDOWS_X, WINDOWS_Y, 32);
	if (DxLib_Init() == -1) return -1;								// Dxlib初期化関数
	SetDrawScreen(DX_SCREEN_BACK);									// スクリーン設定
	SetTransColor(255, 0, 255);										// 透過色設定

	//シーン
	CSceneManager cSceneManager;
	CInput cInput;

	//初期化
	cInput.Init();
	cSceneManager.Init();
	CFPS::Init();

	// ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);

		// エスケープキーで終了
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

		////FPS描画
		//CFPS::DrawFps();

		ScreenFlip();			
	}
	cSceneManager.Exit();

	DxLib_End();			
	return 0;				
}




