#include "CDraw.h"
CDraw::CDraw(HWND hWnd, CTrapezoid* trp, int left, int top)
	:m_hWnd(hWnd), m_pTrapezoid(trp),
	 m_nLeft(left), m_nTop(top)
{
}

void CDraw::Draw(COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
}

CDraw::~CDraw()
{
	m_pTrapezoid = nullptr;
	m_nTop = 0;
	m_nLeft = 0;
}

bool CDraw::Draw(int x, int y) const
{
	HDC hdc = GetDC(m_hWnd);
	int nextX = x, nextY = y;

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(0, 3, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, pen);

	Ellipse(hdc, nextX - 5, nextY - 5,
		nextX + 5, nextY + 5);
	MoveToEx(hdc, nextX, nextY, NULL);

	nextX = nextX + m_pTrapezoid->GetTopLength();
	LineTo(hdc, nextX, nextY);

	Ellipse(hdc, nextX - 5, nextY - 5,
		nextX + 5, nextY + 5);
	MoveToEx(hdc, nextX, nextY, NULL);

	nextX = nextX + m_pTrapezoid->GetBottomLength() - m_pTrapezoid->GetTopLength() - m_pTrapezoid->GetShift();
	nextY = nextY + m_pTrapezoid->GetTrapezoidHeight();
	LineTo(hdc, nextX, nextY);

	Ellipse(hdc, nextX - 5, nextY - 5,
		nextX + 5, nextY + 5);
	MoveToEx(hdc, nextX, nextY, NULL);

	nextX = nextX - m_pTrapezoid->GetBottomLength();
	LineTo(hdc, nextX, nextY);

	Ellipse(hdc, nextX - 5, nextY - 5,
		nextX + 5, nextY + 5);
	MoveToEx(hdc, nextX, nextY, NULL);

	LineTo(hdc, x, y);

	SelectObject(hdc, hOldBrush);
	DeleteObject(brush);
	SelectObject(hdc, hOldPen);
	DeleteObject(pen);
	
	ReleaseDC(m_hWnd, hdc);
	//Draw(RGB(10, 10, 10));
	return true;
}



