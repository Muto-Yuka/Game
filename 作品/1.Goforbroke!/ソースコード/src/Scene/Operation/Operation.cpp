#include <DxLib.h>
#include"Operation.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Sound/Sound.h"

static const char OPERATION_PATH[] = { "data/Scene/Operation/Operation.png" };
static const int  OPERATION_TIME = 1200;

COperationScene::COperationScene()
{
	Init();	
}
COperationScene::~COperationScene()
{
	Exit();
	CFade::DeleteInstance();
}

//ループ
bool COperationScene::Loop()
{
	//関数ポインタを宣言し関数を配列に入れる
	void (COperationScene:: * Operation[])() = {
		&COperationScene::Init,&COperationScene::Load,& COperationScene::Step,& COperationScene::Exit, & COperationScene::Next
	};
	//idに合わせて処理を実行
	(this->*Operation[m_eOperationID])();

	if (m_eOperationID == SCENE_NEXT)
		return true;
	else
		return false;

}

//初期化
void COperationScene::Init()
{
	m_iHndl = -1;		
	m_iOperationTime = 0;
	m_eOperationID = SCENE_LOAD;
}

//ロード
void COperationScene::Load()
{
	if (m_iHndl == -1)
	{
		m_iHndl = LoadGraph(OPERATION_PATH);
	}
	m_eOperationID = SCENE_STEP;
	CFade::GetInstance()->Request(4.0f, true);
}

//ステップ
void COperationScene::Step()
{
	if (!CFade::GetInstance()->IsEnd()) return;

	//操作説明カウント
	m_iOperationTime++;
	//操作説明時間経過したら
	if (OPERATION_TIME <= m_iOperationTime)
	{
		CSound::AllStop();
		m_eOperationID = SCENE_EXIT;
		CFade::GetInstance()->Request(4.0f, false);
	}
	else if (CInput::IsInputPush(CInput::INPUT_NEXT) || (CPadInput::PadInput & PAD_INPUT_8))	//エンターを押すと次へ
	{
		CSound::AllStop();
		m_eOperationID = SCENE_EXIT;
		CFade::GetInstance()->Request(4.0f, false);
	}
}

//描画
void COperationScene::Draw()
{
	DrawGraph(0, 0, m_iHndl, true);
}

//破棄
void COperationScene::Exit()
{
	if (!CFade::GetInstance()->IsEnd()) return;

	DeleteGraph(m_iHndl);

	m_eOperationID = SCENE_NEXT;
}

//次へ
void COperationScene::Next()
{
	m_eOperationID = SCENE_INIT;
}


