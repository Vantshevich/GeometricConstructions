#include "CTrapezoid.h"

CTrapezoid::CTrapezoid(int TopLength, int BottomLength, int TrapezoidHeight, int Shift)
	:m_nTopLength(TopLength), m_nBottomLength(BottomLength),
	 m_nTrapezoidHeight(TrapezoidHeight), m_nShift(Shift)
{
}

bool CTrapezoid::Scale(double coefficient)
{
	if (coefficient > 0.1)
	{
		m_nTopLength *= coefficient;
		m_nBottomLength *= coefficient;
		m_nTrapezoidHeight *= coefficient;
		m_nShift *= coefficient;
		return true;
	}
	else
		return false;
	
}
