#include "CShell.h"

CShell::CShell(HWND hWnd)
	:m_hWnd(hWnd), phase(Phase::BUILDING),
	 m_bLeftButtonDown(false)
{
	builder = new CBuilder(m_hWnd);
}

CShell::~CShell()
{
	if (builder != nullptr)
		delete builder;
	for (int i = 0; i < trp.size(); i++)
		if (trp[i] != nullptr)
			delete trp[i];
}

void CShell::OnMove(int x, int y)
{
	if (phase == Phase::BUILDING && !(builder->IsFinished()))
	{
		builder->OnMove(x, y);
	}
	else
	{
		if (m_bLeftButtonDown)
		{
			for (int i = 0; i < trp.size(); i++)
			{
				if (trp[i]->Selected())
				{
					if (trp[i]->ClickOn(x, y))
						trp[i]->ChangePosition(x - m_nPreviousX,
							y - m_nPreviousY);
					else
						trp[i]->RemoveSelection();
				}
			}
			m_nPreviousX = x;
			m_nPreviousY = y;
		}
	}
	OnPaint();
}

void CShell::OnLeftButtonDown(int x, int y)
{
	m_bLeftButtonDown = true;
	m_nPreviousX = x;
	m_nPreviousY = y;
	if (phase == Phase::BUILDING && !(builder->IsFinished()))
	{
		builder->OnClick(x, y);

		if (builder->IsFinished()){		
			HDC hdc = GetDC(m_hWnd);
			CRealTrapezoid* rtp = new CRealTrapezoid(builder->IsFinished());
			trp.push_back(rtp);
			
			phase = Phase::USING;
			RECT Rect;
			GetWindowRect(m_hWnd, &Rect);
			int width = Rect.right - Rect.left;
			int height = Rect.bottom - Rect.top;
			
			rtp->Put(hdc ,width / 2 - builder->IsFinished()->GetBottomLength() / 2, height / 2 - builder->IsFinished()->GetTrapezoidHeight() / 2);
			ReleaseDC(m_hWnd, hdc);
			builder->~CBuilder();
		}
	}
	else
	{
	}
	OnPaint();
}

void CShell::OnLeftButtonUp(int x, int y)
{
	m_bLeftButtonDown = false;
	if (phase != Phase::BUILDING)
	{
		for (int i = trp.size() - 1; i >= 0; i--)
		{
			if (trp[i]->ClickOn(x, y))
			{
				trp[i]->Select();
				trp[i]->SetColor(RGB(0, 0, 128));
				HDC hdc = GetDC(m_hWnd);
				//trp[i]->Draw(hdc);
				ReleaseDC(m_hWnd, hdc);
			}
		}
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

void CShell::OnButton1()
{
	phase = Phase::BUILDING;
}
