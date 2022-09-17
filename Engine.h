#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

using namespace sf;

class Engine {
private:
	TextureHolder th;
	//Particle System
	ParticleSystem m_PS;
	//The playable characters, Thomas and Bob
	Thomas m_Thomas;
	Bob m_Bob;
	//The level manager
	LevelManager m_LM;
	//the sound manager
	SoundManager m_SM;
	//HUD manager
	HUD m_HUD;
	int m_FramesSinceLastHUDUpdate = 500;
	int m_TargetFramesPerHUDUpdate = 500;
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;
	const int GRAVITY = 300;
	RenderWindow m_Window;

	//the main views
	View m_MainView, m_LeftView, m_RightView;
	//the views for the background
	View m_BGMainView, m_BGLeftView, m_BGRightView, m_HudView;
	//background shader
	Shader m_RippleShader;
	//create a sprite and texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	//
	bool m_Playing;
	//are we controlling character1?
	bool m_Character1 = true;
	//are we playing split screen?  (default no)
	bool m_SplitScreen = false;
	//
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;
	//do we change levels?
	bool m_NewLevelRequired = true;
	//the vertex map of the level
	VertexArray m_VALevel;
	//2d array with the map of the level
	int** m_ArrayLevel = NULL;
	//Texture for the level tiles
	Texture m_TextureTiles;

	//private functions
	void input();
	void update(float dtAsSeconds);
	void draw();
	//load new level
	void loadLevel();
	bool detectCollisions(PlayableCharacter& character);
	//make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel);
	//a vector of VEctor2f for the fire emitter locations
	vector <Vector2f> m_FireEmitters;
public:
	Engine();
	//run calls all private methods
	void run();
};