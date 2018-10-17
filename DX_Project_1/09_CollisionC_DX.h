#pragma once
#include "00_header_DX.h"

class CollisionC_DX
{
public:
	static CollisionC_DX& GetInstance();

public:
	ClsInfo RectInRect(iLTRB rtDest, iLTRB rtSrc);
	bool RectInPt(iLTRB rtDest, POINT pt);
	ClsInfo CircleInCircle(iLTRB rtDest, iLTRB rtSrc);
	bool CircleInPt(iLTRB rtDest, POINT pt);

protected:
	CollisionC_DX();

public:
	virtual ~CollisionC_DX();
};

#define I_ClsMgr CollisionC_DX::GetInstance()

