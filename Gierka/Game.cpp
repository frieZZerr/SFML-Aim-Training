#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame			 = false;
	this->points			 = 0;
	this->health			 = 100;
	this->enemySize			 = 50.f;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer	 = this->enemySpawnTimerMax;
	this->maxEnemies		 = 5;
	this->mouseHeld			 = false;
	this->mouseHeldEnemy	 = false;
	this->keyHeld			 = false;
	this->combo				 = 0;
	this->bestCombo			 = 0;
	this->maxBullets		 = 20;
	this->bullets			 = this->maxBullets;
	this->money				 = 0;
	this->canShoot			 = true;
}

void Game::initWindow()
{
	this->videoMode.width = 1280;
	this->videoMode.height = 720;

	this->window = new sf::RenderWindow(this->videoMode, "Aim Training ! ", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);

	this->window->setMouseCursorVisible(false);
}

void Game::initTextures()
{
	if (!ctTexture.loadFromFile("Textures/ct.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'ct.png' ! " << std::endl;

	if (!ttTexture.loadFromFile("Textures/tt.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'tt.png' ! " << std::endl;

	if (!hostageTexture.loadFromFile("Textures/hostage.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'hostage.png' ! " << std::endl;

	if (!backgroundTexture.loadFromFile("Textures/background1.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'background1.png' ! " << std::endl;

	if (!hudTexture.loadFromFile("Textures/hud.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'hud.png' ! " << std::endl;

	if (!healthTexture.loadFromFile("Textures/health.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'health.png' ! " << std::endl;

	if (!bulletsTexture.loadFromFile("Textures/bullets.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'bullets.png' ! " << std::endl;

	if (!glockTexture.loadFromFile("Textures/glock.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'glock.png' ! " << std::endl;

	if (!crosshairTexture.loadFromFile("Textures/crosshair.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'crosshair.png' ! " << std::endl;

	if (!handsTexture.loadFromFile("Textures/hands.png"))
		std::cout << " ! ERROR::GAME::INITTEXTURES::Could not load 'hands.png' ! " << std::endl;
}

void Game::initBackground()
{
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setTexture(&backgroundTexture);
}

void Game::initHUD()
{
	//HUD
	hud.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	hud.setTexture(&hudTexture);

	//Hands
	hands.setSize(sf::Vector2f(250.f, 200.f));
	hands.setTexture(&handsTexture);
	hands.setPosition(sf::Vector2f(window->getSize().x / 1.85f, window->getSize().y - 200.f));

	//Crosshair
	crosshair.setSize(sf::Vector2f(25.f, 25.f));
	crosshair.setTexture(&crosshairTexture);
	crosshair.setPosition(sf::Vector2f(mousePosWindow.x - 12.5f, mousePosWindow.y - 12.5f));

	//Health icon
	healthBar.setSize(sf::Vector2f(25.f, 25.f));
	healthBar.setTexture(&healthTexture);
	healthBar.setPosition(sf::Vector2f(5.f, window->getSize().y - 35.f));

	//Bullets icon
	bulletsBar.setSize(sf::Vector2f(20.f, 20.f));
	bulletsBar.setTexture(&bulletsTexture);
	bulletsBar.setPosition(sf::Vector2f(window->getSize().x - 40.f, window->getSize().y - 30.f));

	//Weapon icon
	hudGun.setSize(sf::Vector2f(40.f, 30.f));
	hudGun.setTexture(&glockTexture);
	hudGun.setPosition(sf::Vector2f(window->getSize().x - 50.f, window->getSize().y - 95.f));
}

void Game::initSounds()
{
	if(!backgroundMusic.openFromFile("Sounds/background.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'background.wav' ! " << std::endl;
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(15);
	backgroundMusic.play();

	if (!ct_1.loadFromFile("Sounds/ct1.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'ct1.wav' ! " << std::endl;
	ct1.setBuffer(ct_1);
	ct1.setVolume(50);

	if (!ct_2.loadFromFile("Sounds/ct2.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'ct2.wav' ! " << std::endl;
	ct2.setBuffer(ct_2);
	ct2.setVolume(50);

	if (!ct_3.loadFromFile("Sounds/ct3.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'ct3.wav' ! " << std::endl;
	ct3.setBuffer(ct_3);
	ct3.setVolume(50);

	if (!ct_4.loadFromFile("Sounds/ct4.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'ct4.wav' ! " << std::endl;
	ct4.setBuffer(ct_4);
	ct4.setVolume(50);

	if (!ct_5.loadFromFile("Sounds/ct5.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'ct5.wav' ! " << std::endl;
	ct5.setBuffer(ct_5);
	ct5.setVolume(50);

	if (!tt_1.loadFromFile("Sounds/tt1.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'tt1.wav' ! " << std::endl;
	tt1.setBuffer(tt_1);
	tt1.setVolume(50);

	if (!tt_2.loadFromFile("Sounds/tt2.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'tt2.wav' ! " << std::endl;
	tt2.setBuffer(tt_2);
	tt2.setVolume(50);

	if (!tt_3.loadFromFile("Sounds/tt3.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'tt3.wav' ! " << std::endl;
	tt3.setBuffer(tt_3);
	tt3.setVolume(50);

	if (!hostage_1.loadFromFile("Sounds/hostage1.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'hostage1.wav' ! " << std::endl;
	hostage1.setBuffer(hostage_1);
	hostage1.setVolume(50);

	if (!hostage_2.loadFromFile("Sounds/hostage2.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'hostage2.wav' ! " << std::endl;
	hostage2.setBuffer(hostage_2);
	hostage2.setVolume(50);

	if (!hostage_3.loadFromFile("Sounds/hostage3.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'hostage3.wav' ! " << std::endl;
	hostage3.setBuffer(hostage_3);
	hostage3.setVolume(50);

	if (!glock_reload.loadFromFile("Sounds/glock_reload.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'glock_reload.wav' ! " << std::endl;
	glockReload.setBuffer(glock_reload);

	if (!glock_shoot.loadFromFile("Sounds/glock_shoot.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'glock_shoot.wav' ! " << std::endl;
	this->glockShoot.setBuffer(glock_shoot);
	this->glockShoot.setVolume(20);

	if (!glock_empty.loadFromFile("Sounds/glock_empty.wav"))
		std::cout << " ! ERROR::GAME::INITSOUNDS::Could not open 'glock_empty.wav' ! " << std::endl;
	this->glockEmpty.setBuffer(glock_empty);
}

void Game::initFonts()
{
	if (!this->uiFont.loadFromFile("Fonts/Hack-Bold.ttf"))
		std::cout << " ! ERROR::GAME::INITFONTS::Failed to load 'Hack-Bold.ttf' ! " << std::endl;

	if (!this->hudFont.loadFromFile("Fonts/Teko-Light.ttf"))
		std::cout << " ! ERROR::GAME::INITFONTS::Failed to load 'Teko-Light.ttf' ! " << std::endl;
}

void Game::initText()
{
	//UItext
	this->uiText.setFont(this->uiFont);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setOutlineColor(sf::Color::Black);
	this->uiText.setOutlineThickness(2.f);
	this->uiText.setString("NONE");
	this->uiText.setPosition(25.f, 25.f);

	//HEALTHtext
	this->healthText.setFont(this->hudFont);
	this->healthText.setCharacterSize(40);
	this->healthText.setFillColor(sf::Color::White);
	this->healthText.setOutlineColor(sf::Color::Black);
	this->healthText.setOutlineThickness(2.f);
	this->healthText.setString("NONE");
	this->healthText.setPosition(50.f, window->getSize().y - 50.f);

	//BULLETtext
	this->bulletText.setFont(this->hudFont);
	this->bulletText.setCharacterSize(35);
	this->bulletText.setFillColor(sf::Color::White);
	this->bulletText.setOutlineColor(sf::Color::Black);
	this->bulletText.setOutlineThickness(2.f);
	this->bulletText.setString("NONE");
	this->bulletText.setPosition(window->getSize().x - 125.f, window->getSize().y - 45.f);

	//MONEYtext
	this->moneyText.setFont(this->hudFont);
	this->moneyText.setCharacterSize(35);
	this->moneyText.setFillColor(sf::Color::White);
	this->moneyText.setOutlineColor(sf::Color::Black);
	this->moneyText.setOutlineThickness(2.f);
	this->moneyText.setString("NONE");
	this->moneyText.setPosition(15.f, 245.f);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setRadius(enemySize);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initBackground();
	this->initHUD();
	this->initSounds();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions
void Game::spawnEnemy()
{
	/*
		@return void
		Spawns enemies and sets their types and colors. Spawns them at random positions.
		-Sets a random type (diff).
		-Sets a random position.
		-Sets a random color.
		-Adds enemy to the vector.
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getRadius() - 50.f)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getRadius() - 50.f))
	);

	//Randomize enemy type
	int type = rand() % 100;

	if (type >= 0 && type < 25)
	{
		this->enemy.setRadius(enemySize);
		this->enemy.setTexture(&ctTexture);
	}
	else if (type >= 25 && type < 95)
	{
		this->enemy.setRadius(enemySize);
		this->enemy.setTexture(&ttTexture);
	}
	else
	{
		this->enemy.setRadius(enemySize);
		this->enemy.setTexture(&hostageTexture);
	}

	//Spawn the enemy and start timer
	this->clock;
	this->enemies.push_back(this->enemy);
}

void Game::ctSounds()
{
	int type = rand() % 5 + 1;

	switch (type)
	{
	case 1:
		ct1.play();
		break;
	case 2:
		ct2.play();
		break;
	case 3:
		ct3.play();
		break;
	case 4:
		ct4.play();
		break;
	case 5:
		ct5.play();
		break;
	default:
		break;
	}
}

void Game::ttSounds()
{
	int type = rand() % 3 + 1;

	switch (type)
	{
	case 1:
		tt1.play();
		break;
	case 2:
		tt2.play();
		break;
	case 3:
		tt3.play();
		break;
	default:
		break;
	}
}

void Game::hostageSounds()
{
	int type = rand() % 3 + 1;

	switch (type)
	{
	case 1:
		hostage1.play();
		break;
	case 2:
		hostage2.play();
		break;
	case 3:
		hostage3.play();
		break;
	default:
		break;
	}
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/**
		@ return void
		Updates the mouse positions:
		- Mouse position relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	this->crosshair.setPosition(sf::Vector2f(mousePosWindow.x - 12.5f, mousePosWindow.y - 12.5f));
}

void Game::updateText()
{
	std::stringstream ui;
	std::stringstream he;
	std::stringstream bu;
	std::stringstream mo;

	//UI
	ui << "Points: " << this->points << "\n"
		<< "Combo: " << this->combo << "\n"
		<< "Best Combo: " << this->bestCombo << "\n";
	this->uiText.setString(ui.str());

	//Health
	he << this->health << "\n";
	this->healthText.setString(he.str());

	//Bullets
	bu << this->bullets << " / " << this->maxBullets << "\n";
	this->bulletText.setString(bu.str());

	//Money
	mo << this->money << "$" << "\n";
	this->moneyText.setString(mo.str());
}

void Game::updateEnemies()
{
	/**
		@return void
		Updates the enemy spawn timer and spawns enemies
		When the total amount of enemies is smaller than the maximum.
		Moves the enemies downwards.
		Removes the enemies at the edge of the screen.
	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}


	//Getting time from spawn and deleting
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.f)
	{
		this->enemies.erase(this->enemies.begin());
		clock.restart();
	}

	//Removing enemies from edge of the screen
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
			this->enemies.erase(this->enemies.begin() + i);
	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->canShoot)
	{
		if (this->mouseHeldEnemy == false)
		{
			this->mouseHeldEnemy = true;

			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					if (this->enemies[i].getTexture() == &ctTexture)
					{
						ctSounds();
						this->points -= 3;
						this->health -= 5;
						this->combo--;
					}
					else if (this->enemies[i].getTexture() == &ttTexture)
					{
						ttSounds();
						this->points += 10;
						this->money += 50;
						this->combo++;
						if (this->combo >= this->bestCombo)
							bestCombo = combo;
					}
					else if (this->enemies[i].getTexture() == &hostageTexture)
					{
						hostageSounds();
						this->points -= 10;
						this->health -= 20;
						this->combo = 0;
						this->money -= 500;
					}

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
		this->mouseHeldEnemy = false;
}

void Game::updateWeapon()
{
	//Reload
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && this->bullets != this->maxBullets)
	{
		if (this->keyHeld == false)
		{
			this->keyHeld = true;

			this->reloadClock;
			glockReload.play();
			this->money -= 300;

			elapsedReloadTime = reloadClock.getElapsedTime();

			if (this->elapsedReloadTime.asSeconds() < 1.5f)
			{
				this->canShoot = false;
			}
			else
			{
				this->canShoot = true;
				this->bullets = this->maxBullets;
				reloadClock.restart();
			}
		}
	}
	else
		this->keyHeld = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
			if (this->mouseHeld == false)
			{
				this->mouseHeld = true;

				//Shots bullet and plays sound
				if (this->canShoot)
				{
					this->bullets--;
					this->glockShoot.play();
				}

				//Checks for empty magazine
				if (this->bullets > 0 && this->canShoot )
				{
					this->canShoot = true;
				}
				else
				{
					this->canShoot = false;
					glockEmpty.play();
				}
			}
	}
	else
		this->mouseHeld = false;
	
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateWeapon();

		this->updateEnemies();
	}

	//End game condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderBackground(sf::RenderTarget& target)
{
	target.draw(this->background);
}

void Game::renderHUD(sf::RenderTarget& target)
{
	target.draw(this->hud);
	target.draw(this->hands);
	target.draw(this->healthBar);
	target.draw(this->bulletsBar);
	target.draw(this->hudGun); //Optional
	target.draw(this->crosshair);
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->healthText);
	target.draw(this->bulletText);
	target.draw(this->moneyText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	/**
		@return void
		- clear old frame
		- render objects
		- display frame in window
		Renders the game objects.
	*/

	this->window->clear(); // If commented makes enemies fade out when shot BUT decreases the FPS and makes screen blurry

	//Draw game objects
	this->renderBackground(*this->window);

	this->renderEnemies(*this->window);

	this->renderHUD(*this->window);
	this->renderText(*this->window);

	this->window->display();
}