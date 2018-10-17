#include "09_CollisionC_DX.h"


CollisionC_DX& CollisionC_DX::GetInstance()
{
	static CollisionC_DX inst;
	return inst;
}

CollisionC_DX::CollisionC_DX()
{

}

ClsInfo CollisionC_DX::RectInRect(iLTRB rtDest, iLTRB rtSrc)
{
	ClsInfo ret;
	ZeroMemory(&ret, sizeof(ClsInfo));

	//두 물체의 사이즈 구하기
	POINT ptDestSize, ptSrcSize;
	ptDestSize.x = rtDest.right - rtDest.left;
	ptDestSize.y = rtDest.bottom - rtDest.top;
	ptSrcSize.x = rtSrc.right - rtSrc.left;
	ptSrcSize.y = rtSrc.bottom - rtSrc.top;

	//중점 구하기
	POINT ctpDest, ctpSrc;
	ctpDest.x = (rtDest.left + rtDest.right) / 2;
	ctpDest.y = (rtDest.top + rtDest.bottom) / 2;
	ctpSrc.x = (rtSrc.left + rtSrc.right) / 2;
	ctpSrc.y = (rtSrc.top + rtSrc.bottom) / 2;

	//두 중점간의 거리 구하기.
	POINT ptClsPos, ctpDist;
	ptClsPos.x = ctpDest.x - ctpSrc.x;
	ptClsPos.y = ctpDest.y - ctpSrc.y;
	ctpDist.x = abs(ptClsPos.x);
	ctpDist.y = abs(ptClsPos.y);


	if (ctpDist.x < (ptDestSize.x/2 + ptSrcSize.x/2) &&
		ctpDist.y < (ptDestSize.y/2+ ptSrcSize.y/2)) {
		ret.bDoCls = true;
		if (ptClsPos.x * ptDestSize.y < ptClsPos.y * ptDestSize.x) {
			if (-1 * ptClsPos.x * ptDestSize.y < ptClsPos.y * ptDestSize.x) {
				//위에서 아래로
				ret.drClsDest = d_TOP;
				ret.drClsSrc = d_BOTTOM;
				ret.ptInLength.x = 0;
				ret.ptInLength.y = rtDest.top - rtSrc.bottom;
			}
			else {
				//왼쪽에서 오른쪽으로
				ret.drClsDest = d_RIGHT;
				ret.drClsSrc = d_LEFT;
				ret.ptInLength.x = rtDest.right - rtSrc.left;
				ret.ptInLength.y = 0;
			}	
		}
		else {
			if (-1 * ptClsPos.x * ptDestSize.y < ptClsPos.y * ptDestSize.x) {
				//오른쪽에서 왼쪽으로
				ret.drClsDest = d_LEFT;
				ret.drClsSrc = d_RIGHT;
				ret.ptInLength.x = rtDest.left - rtSrc.right;
				ret.ptInLength.y = 0;
			}
			else {
				//위에서 아래로
				ret.drClsDest = d_BOTTOM;
				ret.drClsSrc = d_TOP;
				ret.ptInLength.x = 0;
				ret.ptInLength.y = rtDest.bottom - rtSrc.top;
			}
		}
	}

	return ret;
}

bool CollisionC_DX::RectInPt(iLTRB rtDest, POINT pt)
{
	if ((rtDest.left <= pt.x && rtDest.right >= pt.x) &&
		(rtDest.top <= pt.y && rtDest.bottom >= pt.y)) {
		return true;
	}
	return false;
}

ClsInfo CollisionC_DX::CircleInCircle(iLTRB rtDest, iLTRB rtSrc)
{
	ClsInfo ret;
	ZeroMemory(&ret, sizeof(ClsInfo));

	//두 물체의 사이즈 구하기
	uPOINT ptDestSize, ptSrcSize;
	ptDestSize.x = rtDest.right - rtDest.left;
	ptDestSize.y = rtDest.bottom - rtDest.top;
	ptSrcSize.x = rtSrc.right - rtSrc.left;
	ptSrcSize.y = rtSrc.bottom - rtSrc.top;

	//물체의 대각선 길이를 반지름으로 하는 원
	circle oDest, oSrc;
	oDest.pCenter.x = (rtDest.left + rtDest.right) / 2;
	oDest.pCenter.y = (rtDest.top + rtDest.bottom) / 2;
	oDest.dRadius = sqrt(pow(ptDestSize.x, 2) + pow(ptDestSize.y, 2)) / 2;
	oSrc.pCenter.x = (rtSrc.left + rtSrc.right) / 2;
	oSrc.pCenter.y = (rtSrc.top + rtSrc.bottom) / 2;
	oSrc.dRadius = sqrt(pow(ptSrcSize.x, 2) + pow(ptSrcSize.y, 2)) / 2;
	
	//두 중점간의 길이 구하기
	POINT ptClsPos;
	ptClsPos.x = oDest.pCenter.x - oSrc.pCenter.x;
	ptClsPos.y = oDest.pCenter.y - oSrc.pCenter.y;
	double dDistance = sqrt(pow(ptClsPos.x, 2) +pow(ptClsPos.y, 2));

	if (dDistance < (oDest.dRadius + oSrc.dRadius)) {
		ret.bDoCls = true;
		if (ptClsPos.x * ptDestSize.y < ptClsPos.y * ptDestSize.x) {
			if (-1 * ptClsPos.x * ptDestSize.y < ptClsPos.y * ptDestSize.x) {
				//아래에서 위로
				ret.drClsDest = d_BOTTOM;
				ret.drClsSrc = d_TOP;
				ret.ptInLength.x = 0;
				ret.ptInLength.y = rtDest.bottom - rtSrc.top;
			}
			else {
				//왼쪽에서 오른쪽으로
				ret.drClsDest = d_LEFT;
				ret.drClsSrc = d_RIGHT;
				ret.ptInLength.x = rtDest.left - rtSrc.right;
			}	ret.ptInLength.y = 0;
		}
		else {
			if (-1 * ptClsPos.x * ptDestSize.y < ptClsPos.y * ptDestSize.x) {
				//오른쪽에서 왼쪽으로
				ret.drClsDest = d_RIGHT;
				ret.drClsSrc = d_LEFT;
				ret.ptInLength.x = rtDest.right - rtSrc.left;
				ret.ptInLength.y = 0;
			}
			else {
				//위에서 아래로
				ret.drClsDest = d_TOP;
				ret.drClsSrc = d_BOTTOM;
				ret.ptInLength.x = 0;
				ret.ptInLength.y = rtDest.top - rtSrc.bottom;
			}
		}
	}

	return ret;
}

bool CollisionC_DX::CircleInPt(iLTRB rtDest, POINT pt)
{
	uPOINT ptDestSize;
	ptDestSize.x = rtDest.right - rtDest.left;
	ptDestSize.y = rtDest.bottom - rtDest.top;

	circle oDest;
	oDest.pCenter.x = (rtDest.left + rtDest.right) / 2;
	oDest.pCenter.y = (rtDest.top + rtDest.bottom) / 2;
	oDest.dRadius = sqrt(pow(ptDestSize.x, 2) + pow(ptDestSize.y, 2)) / 2;

	double dDistance =
		sqrt(pow((oDest.pCenter.x - pt.x), 2) + pow((oDest.pCenter.y - pt.y), 2));

	if (dDistance < oDest.dRadius) {
		return true;
	}

	return false;
}


CollisionC_DX::~CollisionC_DX()
{

}