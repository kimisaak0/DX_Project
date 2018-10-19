#pragma once

#pragma comment(lib, "fmod64_vc.lib")

#include "00_header_DX.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"

using namespace FMOD;
const int g_iMaxSound = 32;

class Sound_DX
{
protected:
	System * m_pSystem;
	Sound*    m_pSound[g_iMaxSound];
	Channel*  m_pChannel[g_iMaxSound];

	int       m_iSoundList;
	TCHAR     m_szBuffer[MAX_PATH];

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();


public:
	int     Load(const char* pLoadName, bool bPlay);

	void    Play(int iIndex, bool bPlay = true, bool bLoop = false);
	void    PlayEffect(int iIndex);
	void    Stop(int iIndex);
	void    paused(int iIndex);

	void    Volume(int iIndex, float fVolume, bool bUp);


public:
	static Sound_DX& GetInstance();

protected:
	Sound_DX();
	~Sound_DX();
};

#define I_SoundMgr Sound_DX::GetInstance()



