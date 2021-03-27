#pragma once
#include "CTrapezoid.h"
#include <Windows.h>
#include <wingdi.h>


class CDraw
{
public:
	CDraw(HWND hWnd, CTrapezoid* trp, int left, int top);

	~CDraw();

	bool Draw(int x, int y) const;

private:
	CTrapezoid* m_pTrapezoid;

	HWND m_hWnd;

	void Draw(COLORREF color);

	int *m_arrCurrentX;
	int m_nTop;

	bool n_bIsDrawnn;

	int m_nLeft;// m_nTop;
	//int m_nPointRotationX;
	//int m_nPointRotationY;

	int m_nAngle;

};

