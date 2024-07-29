#include <DxLib.h>
#include"Operation.h"
#include "../../MyLib/Fade/Fade.h"
#include "../../MyLib/Input/Input.h"
#include "../../MyLib/Sound/Sound.h"

static const char OPERATION_PATH[] = { "" };

COperation::COperation()
{
	Init();	
}
COperation::~COperation()
{
	Exit();
}

//ループ
int COperation::Loop()
{
	//関数ポインタを宣言し関数を配列に入れる
	void (COperation:: * Operation[])() = {
		&COperation::Init,& COperation::Load,& COperation::Step,& COperation::Exit, & COperation::Next
	};
	//idに合わせて処理を実行
	(this->*Operation[m_eSceneID])();

	if (m_eSceneID == SCENE_NEXT)
		return 1;

	return -1;
}

//初期化
void COperation::Init()
{
	CSceneBase::Init();

}

//ロード
void COperation::Load()
{

	CSceneBase::Load();
}

//ステップ
void COperation::Step()
{
	//決定で次へ
	CSceneBase::Step();

}

//描画
void COperation::Draw()
{
	DrawGraph(0, 0, m_iHndl, true);
}

//破棄
void COperation::Exit()
{
	CSceneBase::Exit();
}

//次へ
void COperation::Next()
{
	CSceneBase::Next();
}


