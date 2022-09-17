#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		loadLevel();
	}
	if (m_Playing)
	{
		m_Thomas.update(dtAsSeconds);
		m_Bob.update(dtAsSeconds);

		//detect collisions
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
		{
			//reached the end of the level
			m_NewLevelRequired = true;
			//play sound
			m_SM.playReachGoal();
		}
		else
		{
			detectCollisions(m_Bob);
		}
		//let bob and thomas jump on each other's heads
		if (m_Bob.getFeet().intersects(m_Thomas.getHead())) m_Bob.stopFalling(m_Thomas.getHead().top);
		if (m_Thomas.getFeet().intersects(m_Bob.getHead())) m_Thomas.stopFalling(m_Bob.getHead().top);


		//count down remaining time
		m_TimeRemaining -= dtAsSeconds;
		if (m_TimeRemaining <= 0) m_NewLevelRequired = true;
	}

	//check if fire sound needs to be played
	vector<Vector2f>::iterator it;
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		//where is this emitter?  store its location in pos
		float posX = (*it).x;
		float posY = (*it).y;
		//is it near the player?  Make a 500 pixel rectangle around emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);
		if (m_Thomas.getPosition().intersects(localRect)) m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
	}

	if (m_SplitScreen)
	{
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else
	{
		if (m_Character1) m_MainView.setCenter(m_Thomas.getCenter());
		else m_MainView.setCenter(m_Bob.getCenter());
	}
	
	//time to update HUD?
	m_FramesSinceLastHUDUpdate++;
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		stringstream ssTime, ssLevel;
		ssTime << (int)m_TimeRemaining;
		m_HUD.setTime(ssTime.str());
		ssLevel << "Level: " << m_LM.getCurrentLevel();
		m_HUD.setLevel(ssLevel.str());
		m_FramesSinceLastHUDUpdate = 0;
	}

	//update the particles
	if (m_PS.running()) m_PS.update(dtAsSeconds);
}