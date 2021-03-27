#pragma once
#undef UNICODE 
#include <cstring>
#include <Windows.h>
#include <wingdi.h>
#include <math.h>
#include "CTrapezoid.h"

class CBuilder
{
public: 
	CBuilder(HWND hWnd);

	~CBuilder();

	void OnMove(int x, int y);

	void OnClick(int x, int y);

	CTrapezoid* IsFinished() const { return m_pTrapezoid; }

	void Redraw(int currentX, int currentY) const;

private:
	HWND m_hWnd;

	CTrapezoid* m_pTrapezoid;

	int *m_arrX;
	int *m_arrY;
	int m_nCrutchX;
	int m_nCrutchY;
	int m_nNumberOfPoints;
};