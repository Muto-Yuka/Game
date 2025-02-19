#include"Sound.h"

int CSound::m_iHndl[SOUND_NUM];

#define BGM_TITLE ("data/Sound/Title.mp3")
#define BGM_STAGE1 ("data/Sound/Stage1/BGM.mp3")
#define BGM_STAGE2 ("data/Sound/Stage2/Stage2.mp3")
#define BGM_STAGE3 ("data/Sound/Stage3/Stage3.mp3")
#define BGM_STAGE4 ("data/Sound/Stage4/Pop.mp3")
#define BGM_CLEAR  ("data/Sound/Clear.mp3")
#define BGM_GAMEOVER ("data/Sound/Gamever.mp3")



CSound::CSound()
{
	Init();
}
CSound::~CSound()
{
	Exit();
}

//初期化
void CSound::Init()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		m_iHndl[i] = -1;
	}
}

//全データ読み込み
bool CSound::AllLoad()
{
	bool isRet = true;

	const char pFileName[SOUND_NUM][128] =
	{
		BGM_TITLE, BGM_STAGE1, BGM_STAGE2, BGM_STAGE3, BGM_STAGE4,
		BGM_CLEAR, BGM_GAMEOVER
	};

	for (int i = 0; i < SOUND_NUM; i++)
	{
		m_iHndl[i] = LoadSoundMem(pFileName[i]);

		if (m_iHndl[i] == -1) isRet = false;
	}
	return isRet;
}

//破棄
void CSound::Exit()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		if (m_iHndl[i] != -1)
		{
			DeleteSoundMem(m_iHndl[i]);
			m_iHndl[i] = -1;
		}
	}
}

//再生
int CSound::Play(tag_Sound iID, int iType, bool isStart)
{
	return PlaySoundMem(m_iHndl[iID], iType, isStart);
}
//停止
int CSound::Stop(tag_Sound iID)
{
	return StopSoundMem(m_iHndl[iID]);
}
//全停止
void CSound::AllStop()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		StopSoundMem(m_iHndl[i]);
	}
}

//再生時間取得
int CSound::GetSoundTime(tag_Sound iID)
{
	return (int)GetSoundCurrentTime(m_iHndl[iID]);
}
//再生総時間取得
int CSound::GetSoundAllTime(tag_Sound iID)
{
	return (int)GetSoundTotalTime(m_iHndl[iID]);
}
//再生判定
bool CSound::IsPlay(tag_Sound iID)
{
	return CheckSoundMem(m_iHndl[iID]) == 1 ? true : false;
}

//音量設定
void CSound::SetVolume(tag_Sound iID, float fVol)
{
	if (fVol < 0.f || fVol > 1.f) return;
	ChangeVolumeSoundMem((int)(255.f * fVol), m_iHndl[iID]);
}


