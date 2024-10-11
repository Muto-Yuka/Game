#include <DxLib.h>
#include "FPS.h"

//一秒間に６０
static const int FRAME_RATE = 60;		
//1フレームが何ミリ秒か？
static const int FRAME_RATE_MILL_SECOND = 1000 / 60;	

int CFPS::m_currentTime;
int CFPS::m_lastTime;
int CFPS::m_count;
int CFPS::m_updateFrameRateTime;
double CFPS::m_frameRate;

//初期化
void CFPS::Init()
{
	m_currentTime = GetNowCount();	
	m_lastTime = m_currentTime;		
	m_frameRate = 0.0;
	m_count = 0;
	m_updateFrameRateTime = m_currentTime;
}

//true:次の処理へ　false:待機
bool CFPS::CheckNext()
{
	//最新時間取得
	m_currentTime = GetNowCount();	
	//前回の時間と最新の時間の差分（どれくらい経過したか）
	int difTime = m_currentTime - m_lastTime;
	
	//前回から今回までで指定された時間を経過したか　〇経過時間より大きい　×小さい
	if (difTime >= FRAME_RATE_MILL_SECOND)
		return true;
	else 
		return false;

}

//フレームレートの計算
void CFPS::Step()
{
	m_lastTime = m_currentTime;
}

//フレームレート表示(デバック用)
void CFPS::DrawFps()
{
	m_count++;	
	//前回の時間と最新の時間の差分（どれくらい経過したか）
	int difTime = m_currentTime - m_updateFrameRateTime;

	//前回の時間から１秒経つまではこの処理は実行しない
	if (difTime > 1000)
	{
		float frameCnt = (float)(m_count * 1000);
		m_frameRate = frameCnt / difTime;
		m_count = 0;
		m_updateFrameRateTime = m_currentTime;
	}

	DrawFormatString(16, 16, GetColor(255, 255, 255), "FPS : %.02lf", m_frameRate);	//%.02lf 02は小数点二桁まで　lfはdouble型

}





