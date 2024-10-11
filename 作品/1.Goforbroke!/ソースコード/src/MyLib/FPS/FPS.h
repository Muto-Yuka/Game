#pragma once

class CFPS
{
	static int m_currentTime;		  //現在のＰＣ時間
	static int m_lastTime;			  //ひとつ前のＰＣ時間
	static double m_frameRate;		  //現在のフレームレート(デバック用)
	static int m_count;				  //フレーム数カウント(デバック用)
	static int m_updateFrameRateTime; //フレームレート更新時間(デバック用)

public:
	static void Init();			//初期化
	static bool CheckNext();	// true：次の処理　false：待機
	static void Step();			//計算
	static void DrawFps();		//表示(デバック用)

};


