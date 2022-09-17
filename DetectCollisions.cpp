#include "Engine.h"
#include <iostream>
bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;
	//make a rect for all parts
	FloatRect detectionZone = character.getPosition();
	//make a flaotrect to check each hitbox
	FloatRect block;
	block.width = TILE_SIZE;
	block.height = TILE_SIZE;
	//build a zone around to detect collisions
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	//check a few tiles above
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;
	//ensure we didn't check any positions lower than 0 or higher than the end of the level
	if (startX < 0)startX = 0;
	if (startY < 0) startY = 0;
	if (endX >= m_LM.getLevelSize().x) endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y) endY = m_LM.getLevelSize().y;

	//has the character fallen out of the level?
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level)) character.spawn(m_LM.getStartPosition(), GRAVITY);

	//loop through all the blocks near the player
	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			//initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;
			//has the character fallen into a hazard?  check head first
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					//character has drowned or burned
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					//which sound to play?
					if (m_ArrayLevel[y][x] == 2) //fire
					{
						//play sound
						m_SM.playFallInFire();
					}
					else //water
					{
						//play sound
						m_SM.playFallInWater();
					}
				}
			}

			//is character colliding with block
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block)) character.stopRight(block.left);
				else if (character.getLeft().intersects(block)) character.stopLeft(block.left);
				if (character.getFeet().intersects(block)) character.stopFalling(block.top);
				else if (character.getHead().intersects(block)) character.stopJump();
			}

			//if the character's feet touched fire or water start the paricles if not already running
			if (!m_PS.running())
			{
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block)) m_PS.emitParticles(character.getCenter());
				}
			}

			//more collisions here
			if (m_ArrayLevel[y][x] == 4)
			{
				//character has reached the end
				reachedGoal = true;
			}
		}
	}
	return reachedGoal;
}