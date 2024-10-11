#include <DxLib.h>
#include "Input.h"
#include "KeyInput/KeyInput.h"

std::vector<int> CInput::m_vKeyButton;
std::vector<int> CInput::m_vController;

//初期化
void CInput::Init()
{
	CKeyInput::InitInput();
	CPadInput::InitInput();

	//キー入力セット
	m_vKeyButton.push_back(KEY_INPUT_A);		//左移動
	m_vKeyButton.push_back(KEY_INPUT_D);		//右移動
	m_vKeyButton.push_back(KEY_INPUT_W);		//前移動
	m_vKeyButton.push_back(KEY_INPUT_S);		//後ろ移動
	m_vKeyButton.push_back(KEY_INPUT_LSHIFT);	//走る
	m_vKeyButton.push_back(KEY_INPUT_E);		//ものをとる
	m_vKeyButton.push_back(KEY_INPUT_RSHIFT);	//ズーム
	m_vKeyButton.push_back(KEY_INPUT_SPACE);	//弾を撃つ
	m_vKeyButton.push_back(KEY_INPUT_Q);		//修理する
	m_vKeyButton.push_back(KEY_INPUT_RETURN);	//決定ボタン

	//コントローラー用
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_LEFT);		//左移動
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_RIGHT);		//右移動
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_UP);		//前移動
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_DOWN);		//後ろ移動
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_9);		//走る
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_9);		//ものをとる
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_9);		//ズーム
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_9);		//弾を撃つ
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_9);		//修理する
	m_vController.push_back(CPadInput::PadInput & PAD_INPUT_9);		//決定ボタン

}

//更新
void CInput::Update()
{
	CKeyInput::StepInput();
	CPadInput::StepInput();
}

//今押された　
bool CInput::IsInputPush(int key)
{
	return CKeyInput::IsKeyPush(m_vKeyButton[key]);
}

//押し続けられているか
bool CInput::IsInputKeep(int key)
{
	return CKeyInput::IsKeyKeep(m_vKeyButton[key]);
}

//たった今離されたか
bool CInput::IsInputRelese(int key)
{
	return CKeyInput::IsKeyRelese(m_vKeyButton[key]);
}

//単純に押されているか
bool CInput::IsInputDown(int key)
{
	return CKeyInput::IsKeyDown(m_vKeyButton[key]);

	return CPadInput::IsPadDown(m_vController[key]);
}


