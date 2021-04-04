#include "CShell.h"

CShell::CShell(HWND hWnd)
	:m_hWnd(hWnd), phase(Phase::BUILDING),
	 m_bLeftButtonDown(false), m_pMoving(nullptr),
	 m_PointPrevious(nullptr)
{
	builder = new CBuilder(m_hWnd);
}

CShell::~CShell()
{
	if (builder != nullptr)
		delete builder;

	for (int i = 0; i < trp.size(); i++)
	{
		if (trp[i] != nullptr)
		{
			delete trp[i];
		}
	}
	trp.clear();
	
	if (m_PointPrevious)
	{
		delete m_PointPrevious;
		m_PointPrevious = nullptr;
	}
}

void CShell::OnMove(int x, int y)
{
	if (phase == Phase::BUILDING && !(builder->IsFinished()))
		builder->OnMove(x, y);
	else
	{
		if (!m_PointPrevious)
			m_PointPrevious = new Point();
		if (m_bLeftButtonDown)
		{
			if (m_pMoving)
			{
				m_pMoving->ChangePosition(x - m_PointPrevious->x,
					y - m_PointPrevious->y);
			}
		}
		m_PointPrevious->x = x;
		m_PointPrevious->y = y;

		OnPaint();
	}
}

void CShell::OnLeftButtonDown(int x, int y)
{
	if (phase == Phase::BUILDING && !(builder->IsFinished()))
	{
		builder->OnClick(x, y);

		if (builder->IsFinished()){		
			HDC hdc = GetDC(m_hWnd);
			
			RECT Rect;
			GetClientRect(m_hWnd, &Rect);
			int width = Rect.right - Rect.left;
			int height = Rect.bottom - Rect.top;

			CRealTrapezoid* rtp = new CRealTrapezoid(builder->IsFinished(), hdc, width / 2 - builder->IsFinished()->GetBottomLength() / 2, 
													 height / 2 - builder->IsFinished()->GetTrapezoidHeight() / 2);
			trp.push_back(rtp);
			
			builder->~CBuilder();
			ReleaseDC(m_hWnd, hdc);
			phase = Phase::USING;
		}
	}
	else
	{
		m_bLeftButtonDown = true;
		m_PointPrevious->x = x;
		m_PointPrevious->y = y;
		for (int i = trp.size() - 1; i >= 0; i--)
		{
			if (trp[i]->ClickOn(x, y))
			{
				if (trp[i]->Selected())
					m_pMoving = trp[i];
				else
				{
					trp[i]->Select();
					trp[i]->SetColor(RGB(0, 0, 128));
				}
				break;
			}
			else
			{
				if (trp[i]->Selected())
				{
					trp[i]->RemoveSelection();
					break;
				}
			}
		}
	}
}

void CShell::OnLeftButtonUp(int x, int y)
{
	if (phase != Phase::BUILDING)
	{
		m_pMoving = nullptr;
		m_bLeftButtonDown = false;
	}
	OnPaint();
}

void CShell::OnPaint()
{
	if (phase == Phase::BUILDING)
	{
		builder->Redraw(0,0);
	}
	else
	{
		HDC hdc, bufferDC;
		HBITMAP hBM, hoBM;
		
		RECT Rect;
		RECT Rect2;
		GetClientRect(m_hWnd, &Rect);
		GetWindowRect(m_hWnd, &Rect2);
		int width = Rect.right - Rect.left;
		int height = Rect.bottom - Rect.top;
		ClientToScreen(m_hWnd, (LPPOINT)&Rect.left);
		ClientToScreen(m_hWnd, (LPPOINT)&Rect.right);
		int diffY = Rect.top - Rect2.top;
		int diffX = Rect.left - Rect2.left;

		hdc = GetWindowDC(m_hWnd);
		bufferDC = CreateCompatibleDC(hdc);
		hBM = CreateCompatibleBitmap(hdc, width, height);
		hoBM = (HBITMAP)SelectObject(bufferDC, hBM);

		HPEN pen = CreatePen(0, 1, RGB(255, 255, 255));
		HPEN hOldPen = (HPEN)SelectObject(bufferDC, pen);
		Rectangle(bufferDC, 0, 0, width, height);
		SelectObject(bufferDC, hOldPen);
		DeleteObject(pen);

		for (int i = 0; i < trp.size(); i++)
			trp[i]->Draw(bufferDC);

		BitBlt(hdc, diffX, diffY, width, height, bufferDC, 0, 0, SRCCOPY);
		SelectObject(bufferDC, hoBM);
		
		DeleteDC(bufferDC);
		ReleaseDC(m_hWnd, hdc);
	}
}

void CShell::BuildTrapezoid()
{
	phase = Phase::BUILDING;
}