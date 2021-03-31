#include "CRealTrapezoid.h"

CRealTrapezoid::CRealTrapezoid(CTrapezoid* trp, int left, int bottom, COLORREF color)
	:m_pTrapezoid(trp),
	m_Color(color), m_bSelected(0)
{
	m_arrX = new int[4];
	m_arrY = new int[4];
	ConvertToPoints(left, bottom);
}

CRealTrapezoid::CRealTrapezoid(CTrapezoid* trp, COLORREF color)
	:m_pTrapezoid(trp),
	m_Color(color), m_bSelected(0)
{
	m_arrX = new int[4];
	m_arrY = new int[4];
}

void CRealTrapezoid::Put(HDC hdc, int x, int y)
{
	ConvertToPoints(x, y);
	Draw(hdc);	
}

CRealTrapezoid::~CRealTrapezoid()
{
	if (m_pTrapezoid != nullptr)
	{
		delete m_pTrapezoid;
		m_pTrapezoid = nullptr;
	}
	if (m_arrX != nullptr)
	{
		delete m_arrX;
		m_arrX = nullptr;
	}
	if (m_arrY != nullptr)
	{
		delete m_arrY;
		m_arrY = nullptr;
	}
	
}

void CRealTrapezoid::Draw(HDC hdc) const
{
	HBRUSH brush = CreateSolidBrush(m_Color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(0, 3, m_Color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, pen);

	for (int i = 0; i < 4; i++)
	{
		if(i != 0)
			LineTo(hdc, m_arrX[i], m_arrY[i]);
		Ellipse(hdc, m_arrX[i] - 5, m_arrY[i] - 5,
			m_arrX[i] + 5, m_arrY[i] + 5);
		MoveToEx(hdc, m_arrX[i], m_arrY[i], NULL);
		if(i == 3)
			LineTo(hdc, m_arrX[0], m_arrY[0]);
	}

	SelectObject(hdc, hOldBrush);
	DeleteObject(brush);
	SelectObject(hdc, hOldPen);
	DeleteObject(pen);
}

void CRealTrapezoid::SetColor(COLORREF color)
{
	m_Color = color;
}

void CRealTrapezoid::RemoveSelection()
{
	m_bSelected = false;
	m_Color = RGB(0, 0, 0);
}

void CRealTrapezoid::ChangePosition(int xChange, int yChange)
{
	for (int i = 0; i < 4; i++)
	{
		m_arrX[i] += xChange;
		m_arrY[i] += yChange;
	}
}

bool CRealTrapezoid::ClickOn(int x, int y)
{
	return PointInFigure(4, m_arrX, m_arrY, x, y);
}

void CRealTrapezoid::ConvertToPoints(int left, int bottom)
{
	m_arrX[0] = left;
	m_arrY[0] = bottom;
	m_arrX[1] = m_arrX[0] + m_pTrapezoid->GetBottomLength();
	m_arrY[1] = m_arrY[0];
	m_arrX[2] = m_arrX[1] - m_pTrapezoid->GetBottomLength() + m_pTrapezoid->GetTopLength() + m_pTrapezoid->GetShift();
	m_arrY[2] = m_arrY[1] - m_pTrapezoid->GetTrapezoidHeight();
	m_arrX[3] = m_arrX[2] - m_pTrapezoid->GetTopLength();
	m_arrY[3] = m_arrY[2];
}

