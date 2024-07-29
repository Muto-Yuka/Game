#pragma once
#include <dxlib.h>

class CSky
{
	int	m_iAmHndl;		//午前
	int	m_iPmHndl;		//午後

public:
	CSky();
	~CSky();

	void Init();		//初期化
	void Load();		//ロード
	void Loop();		//ループ
	void AmDraw();		//午前描画
	void PmDraw();		//午後描画
	void Exit();		//破棄	
};




