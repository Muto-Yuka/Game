#include <Dxlib.h>
#include "KeyInput.h"

static const int  KEY_BUF_LEN = (256);

//現在のフレームのキー情報
char currentKeyBuf[KEY_BUF_LEN] = { 0 };
//前フレームのキー情報
char preKeyBuf[KEY_BUF_LEN] = { 0 };

//初期化
void CKeyInput::InitInput()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}

//ステップ
void CKeyInput::StepInput()
{
	//前フレームのキー情報変数に記録しておく
	for (int index = 0; index < KEY_BUF_LEN; index++)
		preKeyBuf[index] = currentKeyBuf[index];

	//現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf);
}

//今押されたか
bool CKeyInput::IsKeyPush(int key_code)
{
	//前フレで押されてない　かつ　現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	return false;
}

//押し続けられているか
bool CKeyInput::IsKeyKeep(int key_code)
{
	//前フレで押されている　かつ　現フレで押されている
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
		return true;

	return false;
}

//たった今離されたか
bool CKeyInput::IsKeyRelese(int key_code)
{
	//前フレで押されている　かつ　現フレで押されていない
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
		return true;

	return false;
}

//単純に押されているか
bool CKeyInput::IsKeyDown(int key_code)
{
	//現フレで押されている（前フレの状態は関係なし）
	if (currentKeyBuf[key_code] == 1)
		return true;

	return false;
}

