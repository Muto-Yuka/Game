#include <DxLib.h>
#include "PadInput.h"

int CPadInput::PadInput = 0;

//初期化
void CPadInput::InitInput()
{
	//コントローラーを指定
	CPadInput::PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

//ステップ
void CPadInput::StepInput()
{

}

//押されているか
bool CPadInput::IsPadDown(int code)
{
	if ((GetJoypadInputState(DX_INPUT_PAD1) & code) == 0)
	{
		return true;
	}

	return false;
}




