#include "myMain.h"


int myMain() {
	// Box2D world creation using Box2DEngine class form Box2DEngine.cpp
	Box2DEngine gameController(WIDTH, HEIGHT);
	b2World* world = gameController.getPhysicsWorld();
	sf::RenderWindow* window = gameController.getApp();
	MyContactListener myContactListenerInstance;
	world->SetContactListener(&myContactListenerInstance);
	
	//creation de la liste des platformes 
	std::vector<std::unique_ptr<Platform>>platforms;

	//creation de la liste des joueur 
	std::vector<std::unique_ptr<Player>> players; 
	std::unique_ptr<Player> player1(new Player(&gameController));
	std::unique_ptr<Player> player2(new Player(&gameController));
	players.push_back(std::move(player1));
	players.push_back(std::move(player2));
	
	
	//creation de la liste des monstres
	std::vector<std::unique_ptr<Monster>> monsters;
	std::unique_ptr <Monster> premier_monstre (new Monster(&gameController,300,300));
	monsters.push_back(std::move(premier_monstre));
		
	// Link the two players with a rope
	std::unique_ptr<Rope> rope(new Rope(800,400, 10 * RATIO, 30, &gameController));
	rope->linkPlayers(players[0].get(), players[1].get(), world);

	// Simulation parameters
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	while (window->isOpen())
	{
		// Events.cpp : handle mouse and keyboard events
		HookEvents(window, &gameController, &players,&platforms);
		window->clear(sf::Color::White);
		
		world->Step(timeStep, velocityIterations, positionIterations);
		//afichage et gestion des monstres 
		for (int i = 0; i < players.size(); i++) { //gestion des player 
			getPlayerData(players[i]->getBody())->decreaseJumpTimeout();// decrease le timout pour les jumps de joeur 
			players[i]->draw(sf::Color::Green, window);
		}

		
		//afichage des monstres et gestion des mouvements 
		for (int i = 0; i < monsters.size(); i++) {
			monsters[i]->decreace_reverspeed_timout();
			monsters[i]->updatespeed();
			monsters[i]->draw(sf::Color::Red,window);
		}
		//affichage des platformes 
		for (int i = 0; i < platforms.size(); i++)
			platforms[i]->draw(sf::Color::Red, window);
		//affichage de la corde 

		rope->draw(sf::Color::Green, window);

		window->display();
	}
	return 0;
}

