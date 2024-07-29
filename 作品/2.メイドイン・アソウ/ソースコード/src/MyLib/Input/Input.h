#pragma once
#include <vector>

class CInput 
{
	static std::vector<int> m_vKeyButton;

public:
	enum {
		INPUT_LEFT,		//左移動 A
		INPUT_RIGHT,	//右移動 D
		INPUT_UP,		//上移動 W
		INPUT_DOWN,		//下移動 S
		INPUT_SPACE,	//移動以外
		INPUT_RESPAWN,	//リスポーン

		INPUT_NEXT,		//Enter決定ボタン
		INPUT_END,		//Escゲーム終了
	};

	static void Init();		//初期化
	static void Update();	//更新

	static bool IsInputPush(int key);	//今押された 
	static bool IsInputKeep(int key);	//押し続けられているか　
	static bool IsInputRelese(int key);	//たった今離されたか　
	static bool IsInputDown(int key);	//単純に押されているか

};



