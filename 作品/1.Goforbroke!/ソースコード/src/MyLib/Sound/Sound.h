#pragma once
#include <DxLib.h>

class CSound 
{
public:
	enum tag_Sound
	{
		SOUND_TITLE,		
		SOUND_PLAY,
		SOUND_CLEAR,
		SOUND_GAMEOVER,

		SOUND_NUM
	};

	CSound();
	~CSound();

	static void Init();		//初期化
	static void Exit();		//破棄
	static bool AllLoad();	//true;全ロード完了　false:失敗

	//再生
	static int Play(tag_Sound iID, int iType = DX_PLAYTYPE_BACK, bool isStart = true);
	//停止
	static int Stop(tag_Sound iID);
	//全停止
	static void AllStop();

	//再生時間取得
	static int GetSoundTime(tag_Sound iID);
	//再生総時間取得
	static int GetSoundAllTime(tag_Sound iID);
	//再生判定 true:再生中　false:停止中
	static bool IsPlay(tag_Sound iID);

	//ボリューム設定  (fVol 0.0～1.0)
	static void SetVolume(tag_Sound iID, float fVol);

private:
	static int m_iHndl[SOUND_NUM];	//サウンドハンドル

};









