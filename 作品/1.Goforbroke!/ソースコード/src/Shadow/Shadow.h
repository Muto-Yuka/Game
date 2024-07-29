#pragma once
#include <DxLib.h>
#include "../Scene/PlaySceneManager.h"
class CShadow
{
private:
	int shadowHndl;
	SceneManager cSceneManager;

public:
	void Init();
	void Exit();
	void Draw();
	void Loop();

};



