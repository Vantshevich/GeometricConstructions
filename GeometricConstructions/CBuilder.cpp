#include "CBuilder.h"

CBuilder::CBuilder(HWND hWnd)
	:m_hWnd(hWnd), m_nNumberOfPoints(0),
	m_nCrutchX(0), m_nCrutchY(0),
	m_pTrapezoid(nullptr)
{
	m_arrX = new int[4];
	m_arrY = new int[4];
}

CBuilder::~CBuilder()
{
	if (m_pTrapezoid != nullptr)
	{
		m_pTrapezoid = nullptr;
	}
	delete m_arrX;
	delete m_arrY;
	m_arrX = new int[4];
	m_arrY = new int[4];
	m_nCrutchX = 0;
	m_nCrutchY = 0;
	m_nNumberOfPoints = 0;
}

void CBuilder::OnMove(int x, int y)
{
	HDC hdc = GetDC(m_hWnd);
	int transfromedX = 1 + (x - 10) / 20;
	int transfromedY = 1 + (y - 10) / 20; 
	Redraw(transfromedX, transfromedY);

	 if (transfromedX != m_nCrutchX || transfromedY != m_nCrutchY)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brush);
		Ellipse(hdc, transfromedX * 20 - 5, transfromedY * 20 - 5, transfromedX * 20 + 5, transfromedY * 20 + 5);
		SelectObject(hdc, hOldBrush);
		DeleteObject(brush);
	}

	ReleaseDC(m_hWnd, hdc);
	m_nCrutchX = transfromedX;
	m_nCrutchY = transfromedY;
	
}

void CBuilder::OnClick(int x, int y)
{
	HDC hdc = GetDC(m_hWnd);
	switch (m_nNumberOfPoints)
	{
	case 0:
	{
		m_arrX[m_nNumberOfPoints] = 1 + (x - 10) / 20;
		m_arrY[m_nNumberOfPoints] = 1 + (y - 10) / 20;
		Ellipse(hdc, m_arrX[m_nNumberOfPoints] * 20 - 5, m_arrY[m_nNumberOfPoints] * 20 - 5,
					 m_arrX[m_nNumberOfPoints] * 20 + 5, m_arrY[m_nNumberOfPoints] * 20 + 5);
		++m_nNumberOfPoints;
		break;
	}
	case 1:
	{
		m_arrX[m_nNumberOfPoints] = 1 + (x - 10) / 20;
		m_arrY[m_nNumberOfPoints] = 1 + (y - 10) / 20;
		Ellipse(hdc, m_arrX[m_nNumberOfPoints] * 20 - 5, m_arrY[m_nNumberOfPoints] * 20 - 5, 
					 m_arrX[m_nNumberOfPoints] * 20 + 5, m_arrY[m_nNumberOfPoints] * 20 + 5);
		++m_nNumberOfPoints;
		break;
	}
	case 2:
	{
		if (((m_arrX[0] - m_arrX[1]) * (m_arrY[1] - (1 + (y - 10) / 20))) ==
			((m_arrY[0] - m_arrY[1]) * (m_arrX[1] - (1 + (x - 10) / 20)))) {}
		else
		{
			m_arrX[m_nNumberOfPoints] = 1 + (x - 10) / 20;
			m_arrY[m_nNumberOfPoints] = 1 + (y - 10) / 20;
			Ellipse(hdc, m_arrX[m_nNumberOfPoints] * 20 - 5, m_arrY[m_nNumberOfPoints] * 20 - 5,
						 m_arrX[m_nNumberOfPoints] * 20 + 5, m_arrY[m_nNumberOfPoints] * 20 + 5);
			++m_nNumberOfPoints;
		}
		break;
	}
	case 3:
	{
		if ((((m_arrX[0] - m_arrX[1]) * ((1 + (x - 10) / 20) - m_arrX[2]) > 0) ||
			((m_arrY[0] - m_arrY[1]) * ((1 + (y - 10) / 20) - m_arrY[2]) > 0)) &&
			(((m_arrY[0] - m_arrY[1]) * (m_arrX[2] - (1 + (x - 10) / 20))) ==
			((m_arrY[2] - (1 + (y - 10) / 20)) * (m_arrX[0] - m_arrX[1])))) {
			m_arrX[m_nNumberOfPoints] = 1 + (x - 10) / 20;
			m_arrY[m_nNumberOfPoints] = 1 + (y - 10) / 20;
			Ellipse(hdc, m_arrX[m_nNumberOfPoints] * 20 - 5, m_arrY[m_nNumberOfPoints] * 20 - 5,
				m_arrX[m_nNumberOfPoints] * 20 + 5, m_arrY[m_nNumberOfPoints] * 20 + 5);
			++m_nNumberOfPoints;
			int bottomLength =  20 * sqrt((m_arrX[0] - m_arrX[1]) * (m_arrX[0] - m_arrX[1]) +
									  (m_arrY[0] - m_arrY[1]) * (m_arrY[0] - m_arrY[1]));
			int topLength = 20 * sqrt((m_arrX[2] - m_arrX[3]) * (m_arrX[2] - m_arrX[3]) +
										 (m_arrY[2] - m_arrY[3]) * (m_arrY[2] - m_arrY[3]));
			int heigth;
			int shift;
			if (topLength > bottomLength)
			{
				int buffer = topLength;
				topLength = bottomLength;
				bottomLength = buffer;
			}
			heigth = 20 * (fabs((m_arrY[0] - m_arrY[1]) * m_arrX[2] - (m_arrX[0] - m_arrX[1]) * m_arrY[2] + m_arrX[0] * m_arrY[1] - m_arrX[1] * m_arrY[0]) /
				sqrt((m_arrY[0] - m_arrY[1]) * (m_arrY[0] - m_arrY[1]) + (m_arrX[0] - m_arrX[1]) * (m_arrX[0] - m_arrX[1])));
			double frontSide = sqrt((m_arrX[0] - m_arrX[3]) * (m_arrX[0] - m_arrX[3]) +
				(m_arrY[0] - m_arrY[3]) * (m_arrY[0] - m_arrY[3]));
			if ((frontSide * frontSide - (double)heigth * heigth) != 0)
			{
				shift = 20 * sqrt(fabs(frontSide * frontSide - (double)(heigth / 20) * (heigth / 20)));
			}
			else
				shift = 0;
			m_pTrapezoid = new CTrapezoid(topLength, bottomLength, heigth, shift);
			HDC hdc = GetDC(m_hWnd);
			HPEN pen = CreatePen(0, 1, RGB(255, 255, 255));
			HPEN hOldPen = (HPEN)SelectObject(hdc, pen);
			RECT rect;
			GetClientRect(m_hWnd, &rect);
			Rectangle(hdc, (&rect)->left, (&rect)->top, (&rect)->right, (&rect)->bottom);
			SelectObject(hdc, hOldPen);
			DeleteObject(pen);
			ReleaseDC(m_hWnd, hdc);
		}
		return;
	}
	default:
		break;
	}
	Redraw(m_arrX[m_nNumberOfPoints - 1], m_arrY[m_nNumberOfPoints - 1]);
	ReleaseDC(m_hWnd, hdc);
}

void CBuilder::Redraw(int currentX, int currentY) const
{
	HDC hdc = GetDC(m_hWnd);

	if (m_nCrutchX != 0 && m_nCrutchY != 0 && (m_nCrutchX != currentX || m_nCrutchY != currentY))
	{
		HPEN pen = CreatePen(0, 1, RGB(255, 255, 255));
		HPEN hOldPen = (HPEN)SelectObject(hdc, pen);
		Ellipse(hdc, m_nCrutchX * 20 - 5, m_nCrutchY * 20 - 5, m_nCrutchX * 20 + 5, m_nCrutchY * 20 + 5);
		SelectObject(hdc, hOldPen);
		DeleteObject(pen);
	}

	for (int i = 1; i < 34; i++)
	{
		MoveToEx(hdc, i * 20, 0, NULL);
		LineTo(hdc, i * 20, 500);
	}
	for (int i = 1; i < 24; i++)
	{
		MoveToEx(hdc, 0, i * 20, NULL);
		LineTo(hdc, 700, i * 20);
	}
	
	for (int i = 0; i < m_nNumberOfPoints; i++)
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brush);
		Ellipse(hdc, m_arrX[i] * 20 - 5, m_arrY[i] * 20 - 5, 
					 m_arrX[i] * 20 + 5, m_arrY[i] * 20 + 5);
		SelectObject(hdc, hOldBrush);
		DeleteObject(brush);
		
		MoveToEx(hdc, m_arrX[i] * 20, m_arrY[i] * 20, NULL);
		if (i != m_nNumberOfPoints - 1 || i == 3)
		{
			HPEN pen = CreatePen(0, 3, RGB(0, 0, 0));
			HPEN hOldPen = (HPEN)SelectObject(hdc, pen);
			
			if ((i == 3))
				LineTo(hdc, m_arrX[0] * 20, m_arrY[0] * 20);
			else
				LineTo(hdc, m_arrX[i + 1] * 20, m_arrY[i + 1] * 20);

			SelectObject(hdc, hOldPen);
			DeleteObject(pen);
		}	
	}
	ReleaseDC(m_hWnd, hdc);
}