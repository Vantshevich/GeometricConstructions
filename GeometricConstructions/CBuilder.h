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

	int getX(int i) const { return m_arrX[i]; }

	int getSize() const { return m_nNumberOfPoints; }

	int getY(int i) const { return m_arrY[i]; }

	void Redraw() const;

	CTrapezoid* IsFinished() const { return m_pTrapezoid; }

private:
	HWND m_hWnd;

	CTrapezoid* m_pTrapezoid;

	int *m_arrX;
	int *m_arrY;
	int m_nCrutchX;
	int m_nCrutchY;
	int m_nNumberOfPoints;
};