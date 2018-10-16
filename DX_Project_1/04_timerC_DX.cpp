#include "04_timerC_DX.h"

double g_dGameTime = 0;
double g_dSPF = 0;
int    g_iFPS = 0;

timerC_DX::timerC_DX()
{
	m_liFrequency.QuadPart = 0;
	m_liCurTime.QuadPart = 0;
	m_liBefTime.QuadPart = 0;
	m_liBef1sTime.QuadPart = 0;

	m_iFPSGether  = 0;

	m_BefTickTime.QuadPart = 0;
	m_curTickTime.QuadPart = 0;

	//�ý����� ���ļ� �������� ���� //
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_liFrequency);
}

bool	timerC_DX::Init()
{
	//�ϴ� ī���� ��������
	QueryPerformanceCounter(&m_liBefTime);
	QueryPerformanceCounter(&m_liBef1sTime);

	//Ÿ�̸� ���� ���� Ȯ��
	if (m_liBefTime.QuadPart == 0) {
		return false;
	}

	m_iFPSGether   = 0;
	
	return true;
}

bool	timerC_DX::Frame()
{
	//Ÿ�̸� ���е�
	double precision = 0.001;

	//���� �ð� Ȯ��
	QueryPerformanceCounter(&m_liCurTime);
	g_dSPF = static_cast<double>(m_liCurTime.QuadPart - m_liBefTime.QuadPart) / static_cast<double>(m_liFrequency.QuadPart);
	

	if (((m_liCurTime.LowPart-m_liBefTime.LowPart) / (m_liFrequency.LowPart/1000) ) >= precision) {
		m_liBefTime = m_liCurTime;
		g_dGameTime += precision;
	}

	if (((m_liCurTime.LowPart - m_liBef1sTime.LowPart) / (m_liFrequency.LowPart)) >= 1.0) {
		m_liBef1sTime = m_liCurTime;
		g_iFPS = m_iFPSGether;
		m_iFPSGether = 0;
	}

	m_iFPSGether++;

	return true;
}

bool	timerC_DX::Render()
{
	return true;
}
bool	timerC_DX::Release()
{
	return true;
}

bool    timerC_DX::tickAlram(double tick)
{
	QueryPerformanceCounter(&m_curTickTime);
	if (((m_curTickTime.LowPart - m_BefTickTime.LowPart) / (m_liFrequency.LowPart)) >= tick) {
		m_BefTickTime = m_curTickTime;
		return true;
	}
	return false;
}


timerC_DX::~timerC_DX()
{

}