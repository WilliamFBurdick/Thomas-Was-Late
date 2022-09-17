#include "Engine.h"

void Engine::draw()
{
	m_Window.clear(Color::White);
	//update the shader parameters
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());
	//game is not splitscreen, just draw the main views
	if (!m_SplitScreen)
	{
		//switch to background view
		m_Window.setView(m_BGMainView);
		//draw background with a shader effect
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		//switch to main view
		m_Window.setView(m_MainView);
		//draw the level
		m_Window.draw(m_VALevel, &m_TextureTiles);
		//draw thomas and bob
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());

		//draw particles
		if (m_PS.running()) m_Window.draw(m_PS);
	}
	//game is split screen, draw the left/right views
	else
	{
		//begin with left hand view
		//begin with left background view
		m_Window.setView(m_BGLeftView);
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		//switch to left foreground view
		m_Window.setView(m_LeftView);
		//draw the level
		m_Window.draw(m_VALevel, &m_TextureTiles);
		//draw thomas and bob
		m_Window.draw(m_Bob.getSprite());
		m_Window.draw(m_Thomas.getSprite());
		//draw particles
		if (m_PS.running()) m_Window.draw(m_PS);

		//switch to right hand view
		//begin with right background view
		m_Window.setView(m_BGRightView);
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);
		//switch to right foreground view
		m_Window.setView(m_RightView);
		//draw the level
		m_Window.draw(m_VALevel, &m_TextureTiles);
		//draw bob and thomas
		m_Window.draw(m_Thomas.getSprite());
		m_Window.draw(m_Bob.getSprite());
		//draw particles
		if (m_PS.running()) m_Window.draw(m_PS);
		
	}

	//Draw the HUD elements
	m_Window.setView(m_HudView);
	m_Window.draw(m_HUD.getLevel());
	m_Window.draw(m_HUD.getTime());
	if (!m_Playing) m_Window.draw(m_HUD.getMessage());
	/* DRAW THE REST OF THE HUD HERE */

	//display frame
	m_Window.display();
}