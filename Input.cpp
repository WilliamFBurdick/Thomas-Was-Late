#include "Engine.h"

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			//handle quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape)) m_Window.close();
			//handle starting game
			if (Keyboard::isKeyPressed(Keyboard::Return)) m_Playing = true;
			//switch characters
			if (Keyboard::isKeyPressed(Keyboard::Q)) m_Character1 = !m_Character1;
			//Switch between full and split screen
			if (Keyboard::isKeyPressed(Keyboard::E)) m_SplitScreen = !m_SplitScreen;
		}
	}
	//handle Thomas input
	if (m_Thomas.handleInput())
	{
		//play jump sound
		m_SM.playJump();
	}
	//handle Bob input
	if (m_Bob.handleInput())
	{
		//play jump sound
		m_SM.playJump();
	}
}