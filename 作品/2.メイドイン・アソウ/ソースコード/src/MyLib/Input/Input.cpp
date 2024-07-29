#include <DxLib.h>
#include "Input.h"
#include "KeyInput/KeyInput.h"

std::vector<int> CInput::m_vKeyButton;

//初期化
void CInput::Init()
{
	CKeyInput::InitInput();

	//キー入力セット
	m_vKeyButton.push_back(KEY_INPUT_A);		//左移動
	m_vKeyButton.push_back(KEY_INPUT_D);		//右移動
	m_vKeyButton.push_back(KEY_INPUT_W);		//上移動
	m_vKeyButton.push_back(KEY_INPUT_S);		//下移動
	m_vKeyButton.push_back(KEY_INPUT_SPACE);	//移動以外
	m_vKeyButton.push_back(KEY_INPUT_R);	//リスポーン

	m_vKeyButton.push_back(KEY_INPUT_RETURN);	//決定ボタン
	m_vKeyButton.push_back(KEY_INPUT_ESCAPE);	//決定ボタン

}

//更新
void CInput::Update()
{
	CKeyInput::StepInput();
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

}


