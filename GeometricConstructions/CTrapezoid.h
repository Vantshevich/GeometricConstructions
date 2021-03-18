#pragma once
class CTrapezoid
{
public:
	CTrapezoid(int TopLength, int BottomLength, int TrapezoidHeight, int Shift);

	~CTrapezoid();
private:
	int m_nTopLength;
	int m_nBottomLength;
	int m_nTrapezoidHeight;
	int m_nShift;
};