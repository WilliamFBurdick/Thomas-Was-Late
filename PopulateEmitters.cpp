#include "Engine.h"
using namespace sf;
using namespace std;

void Engine::populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel)
{
	//make sure the vector is empty
	vSoundEmitters.empty();
	//keep track of previous emitter so we don't make too many
	FloatRect previousEmitter;
	//search the level for fire
	for (int x = 0; x < (int)m_LM.getLevelSize().x; x++)
	{
		for (int y = 0; y < (int)m_LM.getLevelSize().y; y++)
		{
			if (arrayLevel[y][x] == 2) //fire tile
			{
				//skip over any fire tiles too close to previous emitter
				if (!FloatRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE).intersects(previousEmitter))
				{
					//add the coordinates of this block
					vSoundEmitters.push_back(Vector2f(x * TILE_SIZE, y * TILE_SIZE));
					//make a rectangle 6 x 6 so we don't make any more emitters close to this one
					previousEmitter.left = x * TILE_SIZE;
					previousEmitter.top = y * TILE_SIZE;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;
				}
			}
		}
	}
	return;
}