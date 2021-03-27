#pragma once
#include "CTrapezoid.h"
#include "Geometry.h"
#include <Windows.h>
#include <wingdi.h>

class CRealTrapezoid
{
public:
	CRealTrapezoid(HWND hWnd, CTrapezoid* trp, int left, int bottom, COLORREF color = RGB(0, 0, 0));
	CRealTrapezoid(HWND hWnd, CTrapezoid* trp, COLORREF color = RGB(0, 0, 0));

	~CRealTrapezoid();

	void Put(int x, int y);

	void Draw() const;

	void SetColor(COLORREF color = RGB(0, 0, 0));

	bool Selected() const { return m_bSelected; }

	void Select() { m_bSelected = true; }

	void RemoveSelection();

	void ChangePosition(int xChange, int yChange);

	bool ClickOn(int x, int y);
private:
	CTrapezoid* m_pTrapezoid;

	HWND m_hWnd; 
	
	COLORREF GetColor() { return m_Color; }

	void ConvertToPoints(int left, int bottom);
	
	int* m_arrX;
	int* m_arrY;

	COLORREF m_Color;

	bool m_bSelected;
};

