#pragma once
class CTrapezoid
{
public:
	CTrapezoid(int TopLength, int BottomLength, int TrapezoidHeight, int Shift);

	int GetTopLength() const { return m_nTopLength; }
	int GetBottomLength() const { return m_nBottomLength; }
	int GetTrapezoidHeight() const { return m_nTrapezoidHeight; }
	int GetShift() const { return m_nShift; }

private:
	int m_nTopLength;
	int m_nBottomLength;
	int m_nTrapezoidHeight;
	int m_nShift;
};
