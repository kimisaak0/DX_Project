#pragma once
#include "00_header_DX.h"

class CollisionC_DX
{
public:
	static CollisionC_DX& GetInstance();

public:
	ClsInfo RectInRect(RECT rtDest, RECT rtSrc);
	bool RectInPt(RECT rtDest, POINT pt);
	ClsInfo CircleInCircle(RECT rtDest, RECT rtSrc);
	bool CircleInPt(RECT rtDest, POINT pt);

protected:
	CollisionC_DX();

public:
	virtual ~CollisionC_DX();
};

#define I_ClsMgr CollisionC_DX::GetInstance()

