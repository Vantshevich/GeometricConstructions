#pragma once
#include "CBuilder.h"
#include "CRealTrapezoid.h"
#include "CTrapezoid.h"
#include <vector>

struct Point {
	int x;
	int y;
};

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

	void BuildTrapezoid();

private:
	//bool Select(int top, int left, int right, int bottom);    /*In developing*/

	CBuilder *builder;

	std::vector<CRealTrapezoid*> trp;

	CRealTrapezoid* m_pMoving;

	Phase phase;

	HWND m_hWnd;

	bool m_bLeftButtonDown;

	Point *m_PointPrevious;
};

