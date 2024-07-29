#include "SceneManager.h"
#include "../MyLib/Input/Input.h"
#include "../MyLib/Fade/Fade.h"
#include "../MyLib/Sound/Sound.h"

CSceneManager::CSceneManager()
{
	
	shadowHndl = -1;

	//ゲームオーバー
	cGameOverScene.Init();

	CSound::Init();
	CSound::AllLoad();

	//初期化
	m_eAllSceneID = SCENE_TITLE;

}
CSceneManager::~CSceneManager()
{
	cDay1PlayScene.Exit();
	cDay2PlayScene.Exit();

	CSound::Exit();
}

void CSceneManager::Init()
{
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

//毎フレーム呼ぶ処理
int CSceneManager::Loop()
{
	int iRet = 0;

	switch (m_eAllSceneID)
	{
	case SCENE_TITLE:
		if(cTitleScene.Loop())
			m_eAllSceneID = SCENE_OPERATION;

		break;

	case SCENE_OPERATION:
		if (cOperation.Loop())
			m_eAllSceneID = SCENE_PLAY_DAY1;

		break;

	case SCENE_PLAY_DAY1:
		cDay1PlayScene.Loop(); 

		////day1クリア処理まですべて終わる　二日目へ
		if (cDay1PlayScene.GetClearFlg())
		{
			//フェード
			CFade::GetInstance()->Request(4.0f, true);

			m_eAllSceneID = SCENE_PLAY_DAY2;

		}
		//水分がなくなればリザルト
		if (cDay1PlayScene.GetResultFlg())
		{
			//フェード
			CFade::GetInstance()->Request(4.0f, true);

			m_eAllSceneID = GAMEOVER_LACK;

		}

		break;

	//二日目
	case SCENE_PLAY_DAY2:
		cDay2PlayScene.Loop(); //Init~Exitまで回す関数を呼ぶ
		if (cDay2PlayScene.GetClearFlg())	
		{
			if (!cDay2PlayScene.GetWaterClear())
			{
				//フェード
				CFade::GetInstance()->Request(4.0f, true);
				m_eAllSceneID = GAMEOVER_PLACE;
			}
			else
			{
				//フェード
				CFade::GetInstance()->Request(4.0f, true);
				m_eAllSceneID = SCENE_RESULT;
			}

		}
		//食料水分がなくなればリザルト
		if (cDay2PlayScene.GetResultFlg())
		{
			//フェード
			CFade::GetInstance()->Request(4.0f, true);

			m_eAllSceneID = GAMEOVER_LACK;

		}	
		break;

	//リザルト
	case SCENE_RESULT:
		if (cClearScene.Loop())
			m_eAllSceneID = SCENE_TITLE;
		
		break;
	//ゲームオーバー
	case GAMEOVER:
		cGameOverScene.Step();
		if (CInput::IsInputPush(CInput::INPUT_NEXT) || (CPadInput::PadInput & PAD_INPUT_8))	//エンターを押すと次へ
		{
			CFade::GetInstance()->Request(4.0f, true);

			m_eAllSceneID = SCENE_TITLE;
		}
		break;

	//水分不足　ゲームオーバー
	case GAMEOVER_LACK:
		cGameOverScene.Step();
		if (CInput::IsInputPush(CInput::INPUT_NEXT) || (CPadInput::PadInput & PAD_INPUT_8))	//エンターを押すと次へ
		{
			CFade::GetInstance()->Request(4.0f, true);

			m_eAllSceneID = SCENE_TITLE;
		}
		break;

	//未達成　ゲームオーバー
	case GAMEOVER_PLACE:
		cGameOverScene.Step();
		if (CInput::IsInputPush(CInput::INPUT_NEXT) || (CPadInput::PadInput & PAD_INPUT_8))	//エンターを押すと次へ
		{
			CFade::GetInstance()->Request(4.0f, true);

			m_eAllSceneID = SCENE_TITLE;
		}
		break;


	}

	//フェード処理の更新
	CFade::GetInstance()->UpDate();


	return iRet;
}


//更新処理・描画
void CSceneManager::SceneDraw()
{
	switch (m_eAllSceneID)
	{
	//タイトル
	case SCENE_TITLE:
		cTitleScene.Draw();
		break;

	//操作説明
	case SCENE_OPERATION:
		cOperation.Draw();

	//一日目
	case SCENE_PLAY_DAY1:
		cDay1PlayScene.ShadowDraw();//影あり描画
		cDay1PlayScene.Draw();		//影なし描画
		break;

	//二日目
	case SCENE_PLAY_DAY2:
		cDay2PlayScene.ShadowDraw();
		cDay2PlayScene.Draw();
		break;

	//リザルト
	case SCENE_RESULT:
		cClearScene.Draw();
		break;

	//ゲームオーバ-
	case GAMEOVER:
		cGameOverScene.Draw();
		break;
	//水分不足　ゲームオーバー
	case GAMEOVER_LACK:
		cGameOverScene.LackDraw();
		break;
	//未達成　ゲームオーバー
	case GAMEOVER_PLACE:
		cGameOverScene.PlaceDraw();
		break;
	}

	//フェード関連
	CFade::GetInstance()->Draw();


}

void CSceneManager::Draw()
{
	//影の描画処理
	ShadowMap_DrawSetup(shadowHndl);//影の描画前に必ず行う
	cDay1PlayScene.ShadowDraw();
	cDay2PlayScene.ShadowDraw();
	ShadowMap_DrawEnd();			//影の描画後に必ず行う
	//通常の描画処理
	SetUseShadowMap(0, shadowHndl);	//反映させる影のハンドルと０～２のスロット番号セット
	SceneDraw();
	SetUseShadowMap(0, -1);			//終わったら使用したスロット番号をー１で終わらせる
}


void CSceneManager::Exit()
{
	DeleteShadowMap(shadowHndl);

}
