#pragma once
#include "../../WindowsSize.h"

class CFade {
public:
	enum FadeState{
		FADE_NON,	//何もなし
		FADE_IN,	//徐々に表示
		FADE_OUT,	//徐々に消える
	};

private:
	static CFade* m_instance;		//シングルトンに必要なインスタンス

	int		m_windowX, m_windowY;	//ウィンドウのサイズ
	float	m_cnt;					//フェード時に必要なアルファ値
	float	m_speed;				//フェードの時間
	FadeState m_state;				//現在のフェードの状態

public:
	static CFade* GetInstance();		//インスタンス取得
	static void Alloc();				//クラスを生成してメモリ確保
	static void DeleteInstance();		//不要になったら破棄

private:
	CFade(){}
	~CFade(){}

	//コピーコンストラクタ・代入を封印(外部からアクセスできないよう)
	CFade(const CFade& other) {}
	CFade& operator=(const CFade& other){}

public:
	//フェードを強制的に消す
	void Reset() { m_state = FADE_NON; }
	//(フェードの速さ(1～255)、trueフェードインfalseフェードアウト)
	void Request(float speed, bool isFadeIn);
	//更新処理
	void UpDate();
	//描画処理
	void Draw();
	//終了判定
	bool IsEnd();
	//現在のフェード状態を取得
	FadeState GetState() { return m_state; }

};



