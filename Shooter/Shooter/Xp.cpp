#include "Xp.hpp"

namespace Level
{
	int m_Level = 0;
	int m_XP = 0;

	void GainXP(int _xp)
	{
		Level::m_XP += _xp;
		if (Level::m_XP > 28510)
		{
			Level::m_XP = 28510;
		}
		while (CalculateLvL());
	}

	bool CalculateLvL()
	{
		int target = int((std::pow(Level::m_Level + 1, 3) / (2 * (Level::m_Level + 2))) * 42 + 100 * (Level::m_Level + 2) - 100);
		if (Level::m_XP >= target)
		{
			++Level::m_Level;
			return true;
		}
		return false;
	}

	int GetLvl()
	{
		return Level::m_Level;
	}
	int& GetXp()
	{
		return Level::m_XP;
	}
}