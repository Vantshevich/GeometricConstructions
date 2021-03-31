#pragma once
#include "CBuilder.h"
#include "CRealTrapezoid.h"
#include "CTrapezoid.h"
#include <vector>

enum class Phase
{
	BUILDING,
	USING
};

class CShell
{
public:
	CShell(HWND hWnd);

	~CShell();

	void OnMove(int x, int y);

	void OnLeftButtonDown(int x, int y);

	void OnLeftButtonUp(int x, int y);

	void OnPaint();

	void OnButton1();
private:
	CBuilder *builder;

	std::vector<CRealTrapezoid*> trp;

	Phase phase;

	HWND m_hWnd;

	bool m_bLeftButtonDown;

	int m_nPreviousX;
	int m_nPreviousY;
};

