#pragma once

class CKeyInput
{
public:
	static void InitInput();				//入力制御初期化
	static void StepInput();				//入力制御ステップ

	static bool IsKeyPush(int key_code);	//今押された
	static bool IsKeyKeep(int key_code);	//押し続けられているか
	static bool IsKeyRelese(int key_code);	//たった今離されたか
	static bool IsKeyDown(int key_code);	//単純に押されているか

};



