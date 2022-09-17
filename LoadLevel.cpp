#include "Engine.h"

void Engine::loadLevel()
{
	m_Playing = false;
	//delete old level's memmory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i) delete[] m_ArrayLevel[i];
	delete[] m_ArrayLevel;
	//load the next array with the map for the level
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);
	//prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);
	m_TimeRemaining = m_LM.getTimeLimit();
	//spawn thomas and bob
	m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
	m_Bob.spawn(m_LM.getStartPosition(), GRAVITY);
	//set new level required to false, so level doesn't skip
	m_NewLevelRequired = false;
}