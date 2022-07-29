#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	//Fonts
	sf::Font uiFont;
	sf::Font hudFont;

	//Textures
	sf::Texture backgroundTexture;
	sf::Texture hudTexture;

	sf::Texture ctTexture;
	sf::Texture ttTexture;
	sf::Texture hostageTexture;
	sf::Texture healthTexture;
	sf::Texture bulletsTexture;
	sf::Texture glockTexture;
	sf::Texture crosshairTexture;
	sf::Texture handsTexture;

	//Sounds and music
	sf::Music backgroundMusic;
	sf::SoundBuffer hostage_1;
	sf::Sound hostage1;
	sf::SoundBuffer hostage_2;
	sf::Sound hostage2;
	sf::SoundBuffer hostage_3;
	sf::Sound hostage3;
	sf::SoundBuffer ct_1;
	sf::Sound ct1;
	sf::SoundBuffer ct_2;
	sf::Sound ct2;
	sf::SoundBuffer ct_3;
	sf::Sound ct3;
	sf::SoundBuffer ct_4;
	sf::Sound ct4;
	sf::SoundBuffer ct_5;
	sf::Sound ct5;
	sf::SoundBuffer tt_1;
	sf::Sound tt1;
	sf::SoundBuffer tt_2;
	sf::Sound tt2;
	sf::SoundBuffer tt_3;
	sf::Sound tt3;
	sf::SoundBuffer glock_reload;
	sf::Sound glockReload;
	sf::SoundBuffer glock_shoot;
	sf::Sound glockShoot;
	sf::SoundBuffer glock_empty;
	sf::Sound glockEmpty;

	//Text
	sf::Text uiText;
	sf::Text healthText;
	sf::Text bulletText;
	sf::Text moneyText;

	//Game logic
	bool endGame;
	int points;
	int health;
	float enemySize;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	bool mouseHeldEnemy;
	bool keyHeld;
	int combo;
	int bestCombo;
	int bullets;
	int maxBullets;
	int money;
	bool canShoot;

	//Game objects
	std::vector<sf::CircleShape> enemies;
	sf::CircleShape enemy;

	sf::RectangleShape background;

	sf::RectangleShape hud;
	sf::RectangleShape healthBar;
	sf::RectangleShape bulletsBar;
	sf::RectangleShape hudGun;
	sf::RectangleShape crosshair;
	sf::RectangleShape hands;

	sf::Clock clock;
	sf::Clock reloadClock;
	sf::Time elapsedReloadTime;
	sf::Time elapsed;

	//Private functions
	void initVariables();
	void initWindow();
	void initTextures();
	void initBackground();
	void initHUD();
	void initSounds();
	void initFonts();
	void initText();
	void initEnemies();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void ctSounds();
	void ttSounds();
	void hostageSounds();

	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void updateWeapon();
	void update();

	void renderBackground(sf::RenderTarget& target);
	void renderHUD(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};