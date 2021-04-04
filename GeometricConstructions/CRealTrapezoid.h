#pragma once
#include "CTrapezoid.h"
#include "Geometry.h"
#include <Windows.h>
#include <wingdi.h>

class CRealTrapezoid
{
public:
	CRealTrapezoid(CTrapezoid* trp, HDC hdc, int left, int bottom, COLORREF color = RGB(0, 0, 0));
	CRealTrapezoid(CTrapezoid* trp, COLORREF color = RGB(0, 0, 0));

	~CRealTrapezoid();

	void Draw(HDC hdc) const;

	void SetColor(COLORREF color = RGB(0, 0, 0)) { m_Color = color; };

	bool Selected() const { return m_bSelected; }

	void Select() { m_bSelected = true; }

	void RemoveSelection();

	void ChangePosition(int xDiffChange, int yDiffChange);

	bool ClickOn(int x, int y);
private:
	CTrapezoid* m_pTrapezoid;
	
	COLORREF GetColor() { return m_Color; }

	void ConvertToPoints(int left, int bottom);
	
	int* m_arrX;
	int* m_arrY;

	COLORREF m_Color;

	bool m_bSelected;
};

