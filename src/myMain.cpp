#include "myMain.h"


int myMain() {

	// Retrieve game config
	XMLParser configParser("C:/Users/alexi/source/repos/Jeu_jin/resources/config.xml");
	configParser.readConfig();


	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);

	//creation de la liste des platformes 

	std::vector<std::unique_ptr<Platform>>platforms;
	platforms.push_back(std::make_unique<Platform>(&gameController,WIDTH / 2, HEIGHT, WIDTH/2, HEIGHT / 10 )); //sol 
	platforms.push_back(std::make_unique<Platform>(&gameController, WIDTH / 4, HEIGHT*  8/10, WIDTH / 8, HEIGHT / 20)); //sol 
	// Cr�ation des joueurs 
	std::vector<std::unique_ptr<Player>> players;
	players.push_back(std::unique_ptr<Player>(new Player(&gameController, 40 * RATIO,  HEIGHT * 7 / 10)));
	players.push_back(std::unique_ptr<Player>(new Player(&gameController, 30 * RATIO, HEIGHT * 7 / 10)));

	// Cr�ation d'un monstre 
	std::vector<std::unique_ptr<Monster>> monsters;
	monsters.push_back(std::unique_ptr <Monster>(new Monster(&gameController, 900, 600)));

	// Link the two players with a rope
	std::unique_ptr<Rope> rope(new Rope(5 * RATIO, 15, &gameController));
	rope->linkPlayers(players[0].get(), players[1].get(), world);

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	sf::Color playercolor[2] = { sf::Color::Green,sf::Color::Blue };

	while (window->isOpen())
	{
		// Events.cpp : handle mouse and keyboard events
		HookEvents(window, &gameController, &players, &platforms, &(configParser.getKeyboardCommandsPlayer1()), &(configParser.getKeyboardCommandsPlayer2()));
		window->clear(sf::Color::White);

		world->Step(timeStep, velocityIterations, positionIterations);
		// Gestion des joueurs 
		for (int i = 0; i < players.size(); i++) {
			getPlayerData(players[i]->getBody())->decreaseJumpTimeout();// decrease le timeout pour les jumps de joueur 
			players[i]->draw(playercolor[i], window);
		}

		// Gestion des monstres 
		for (int i = 0; i < monsters.size(); i++) {
			monsters[i]->decreaseReverseSpeedTimeout();
			monsters[i]->updateSpeed();
			monsters[i]->draw(sf::Color::Magenta, window);
		}
		// Gestion des plateformes 
		for (int i = 0; i < platforms.size(); i++)
			platforms[i]->draw(sf::Color::Red, window);

		// Gestion de la corde 
		rope->draw(sf::Color::Green, window);

		window->display();
	}
	return 0;
}

