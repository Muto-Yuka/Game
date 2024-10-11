#pragma once

//コントローラー情報をinputクラスに返す
class CPadInput
{
public:	
	static int PadInput;

	static void InitInput();			//入力制御初期化
	static void StepInput();			//入力制御ステップ
	static bool IsPadDown(int code);	//押されているか

};



