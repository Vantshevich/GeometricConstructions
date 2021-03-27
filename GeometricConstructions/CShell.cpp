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
}

void CShell::OnLeftButtonDown(int x, int y)
{
	m_bLeftButtonDown = true;
	m_nPreviousX = x;
	m_nPreviousY = y;
	if (phase == Phase::BUILDING && !(builder->IsFinished()))
	{
		builder->OnClick(x, y);

		if (builder->IsFinished())
		{
			CRealTrapezoid* rtp = new CRealTrapezoid(m_hWnd, builder->IsFinished());
			trp.push_back(rtp);
			
			phase = Phase::USING;
			RECT Rect;
			GetWindowRect(m_hWnd, &Rect);
			int width = Rect.right - Rect.left;
			int height = Rect.bottom - Rect.top;
			rtp->Put(width / 2 - builder->IsFinished()->GetBottomLength() / 2, height / 2 - builder->IsFinished()->GetTrapezoidHeight() / 2);

			builder->~CBuilder();
		}
	}
	else
	{
	}
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
				trp[i]->Draw();
			}
		}
	}
}

void CShell::OnPaint(void)
{
	if (phase == Phase::BUILDING)
	{
		builder->Redraw(0,0);
	}
	else
	{
		for (int i = 0; i < trp.size(); i++)
			trp[i]->Draw();
	}
}

void CShell::OnButton1()
{
	phase = Phase::BUILDING;
}
