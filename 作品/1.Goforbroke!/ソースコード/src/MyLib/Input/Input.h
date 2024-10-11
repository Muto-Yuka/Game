#pragma once
#include <vector>
#include "PadInput/PadInput.h"

class CInput 
{
	static std::vector<int> m_vKeyButton;
	static std::vector<int> m_vController;

public:
	enum {
		INPUT_LEFT,		//左移動
		INPUT_RIGHT,	//右移動
		INPUT_UP,		//前移動
		INPUT_DOWN,		//後ろ移動
		INPUT_DASH,		//走る
		INPUT_TAKE,		//ものをとる		
		INPUT_ZOOM,		//ズーム
		INPUT_SHOT,		//弾を撃つ
		INPUT_REPAIR,	//修理する

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



