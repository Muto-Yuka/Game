#include"Sound.h"

int CSound::m_iHndl[SOUND_NUM];

#define BGM_TITLE ("data/Sound/Title/Title.mp3")
#define BGM_PLAY ("data/Sound/Play/Pm.mp3")
#define BGM_CLEAR  ("data/Sound/Clear/Clear.mp3")
#define BGM_GAMEOVER ("data/Sound/Gameover/Gameover.mp3")

CSound::CSound()
{
	Init();
}
CSound::~CSound()
{
	Exit();
}

//èâä˙âª
void CSound::Init()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		m_iHndl[i] = -1;
	}
}

//ëSÉfÅ[É^ì«Ç›çûÇ›
bool CSound::AllLoad()
{
	bool isRet = true;

	const char pFileName[SOUND_NUM][128] =
	{
		BGM_TITLE, BGM_PLAY, BGM_CLEAR, BGM_GAMEOVER
	};

	for (int i = 0; i < SOUND_NUM; i++)
	{
		m_iHndl[i] = LoadSoundMem(pFileName[i]);

		if (m_iHndl[i] == -1) isRet = false;
	}
	return isRet;
}

//îjä¸
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

//çƒê∂
int CSound::Play(tag_Sound iID, int iType, bool isStart)
{
	return PlaySoundMem(m_iHndl[iID], iType, isStart);
}
//í‚é~
int CSound::Stop(tag_Sound iID)
{
	return StopSoundMem(m_iHndl[iID]);
}
//ëSí‚é~
void CSound::AllStop()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		StopSoundMem(m_iHndl[i]);
	}
}

//çƒê∂éûä‘éÊìæ
int CSound::GetSoundTime(tag_Sound iID)
{
	return (int)GetSoundCurrentTime(m_iHndl[iID]);
}
//çƒê∂ëçéûä‘éÊìæ
int CSound::GetSoundAllTime(tag_Sound iID)
{
	return (int)GetSoundTotalTime(m_iHndl[iID]);
}
//çƒê∂îªíË
bool CSound::IsPlay(tag_Sound iID)
{
	return CheckSoundMem(m_iHndl[iID]) == 1 ? true : false;
}

//âπó ê›íË
void CSound::SetVolume(tag_Sound iID, float fVol)
{
	if (fVol < 0.f || fVol > 1.f) return;
	ChangeVolumeSoundMem((int)(255.f * fVol), m_iHndl[iID]);
}


