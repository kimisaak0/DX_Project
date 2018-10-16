#pragma once
#include "00_header_DX.h"

class CollisionC_DX
{
public:
	static CollisionC_DX& GetInstance();

public:
	ClsInfo RectInRect(uLTRB rtDest, uLTRB rtSrc);
	bool RectInPt(uLTRB rtDest, POINT pt);
	ClsInfo CircleInCircle(uLTRB rtDest, uLTRB rtSrc);
	bool CircleInPt(uLTRB rtDest, POINT pt);

protected:
	CollisionC_DX();

public:
	virtual ~CollisionC_DX();
};

#define I_ClsMgr CollisionC_DX::GetInstance()

