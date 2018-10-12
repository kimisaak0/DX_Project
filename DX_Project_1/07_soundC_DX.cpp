#pragma once
#include "07_soundC_DX.h"


Sound_DX::Sound_DX()
{
	m_iSoundList = 0;
}

bool	Sound_DX::Init()
{
	System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);

	return true;
}

bool	Sound_DX::Frame()
{
	m_pSystem->update();

	unsigned total = 0;
	unsigned ms = 0;

	m_pSound[0]->getLength(&total, FMOD_TIMEUNIT_MS);
	m_pChannel[0]->getPosition(&ms, FMOD_TIMEUNIT_MS);

	return true;
}

bool	Sound_DX::Render()
{
	return true;
}

bool	Sound_DX::Release()
{
	for (int iSound = 0; iSound < g_iMaxSound; iSound++) {
		m_pSound[iSound]->release();
	}

	m_pSystem->close();
	m_pSystem->release();

	return true;
}


int     Sound_DX::Load(const char* pLoadName, bool bPlay)
{
	Channel* pChannel = nullptr;

	m_pSystem->createSound(pLoadName, FMOD_DEFAULT, 0, &m_pSound[m_iSoundList++]);

	if (bPlay == true) {
		m_pSystem->playSound(m_pSound[m_iSoundList - 1], 0, false, &pChannel);
		m_pChannel[m_iSoundList - 1] = pChannel;
	}

	return m_iSoundList - 1;
}

void    Sound_DX::Play(int iIndex, bool bPlay, bool bLoop)
{
	bool playing = false;

	if (m_pChannel[iIndex] != NULL) {
		m_pChannel[iIndex]->isPlaying(&playing);
	}

	if (playing == false) {
		if (bLoop) {
			m_pSound[iIndex]->setMode(FMOD_LOOP_NORMAL);
		}
		else {
			m_pSound[iIndex]->setMode(FMOD_LOOP_OFF);
		}

		m_pSystem->playSound(m_pSound[iIndex], false, false, &m_pChannel[iIndex]);
	}
}

void    Sound_DX::PlayEffect(int iIndex)
{
	Channel* pChannel = NULL;
	m_pSystem->playSound(m_pSound[iIndex], false, false, &pChannel);
	m_pChannel[iIndex] = pChannel;
}

void    Sound_DX::Stop(int iIndex)
{
	m_pChannel[iIndex]->stop();
}

void    Sound_DX::paused(int iIndex)
{
	bool paused;

	m_pChannel[iIndex]->getPaused(&paused);
	m_pChannel[iIndex]->setPaused(!paused);
}

void    Sound_DX::Volume(int iIndex, float fVolume, bool bUp)
{
	float fCurrentVolume;
	m_pChannel[iIndex]->getVolume(&fCurrentVolume);

	if (bUp == true) {
		fCurrentVolume += fVolume;
		fCurrentVolume = min(1.0f, fCurrentVolume);
	}
	else {
		fCurrentVolume -= fVolume;
		fCurrentVolume = max(0.0f, fCurrentVolume);
	}

	m_pChannel[iIndex]->setVolume(fCurrentVolume);
}

Sound_DX::~Sound_DX()
{

}