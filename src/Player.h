#pragma once
#include "Box2DEngine.h"
#include "Global.h"
#include "Circle.h"
#include "Shape.h"
#include "Rectangle.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "ViewFieldData.h"
class Player
{
public:
	Player(Box2DEngine* gameController, int x = 40*RATIO, int y = 40*RATIO, float height = 1.f*RATIO, float width = 1.f*RATIO);

	b2Body* getBody() {return Player::body;};
	void draw(sf::Color color, sf::RenderWindow* window);
	void actionLef();
	void actionRight();
	void actionDown();
	void actionUp();
	b2Body* addBodyPlayer(Box2DEngine* gameController, int x, int y, float height, float width);

private:
	b2Body* body;
	std::unique_ptr<HandData> my_handdata;
	std::unique_ptr<FootData> my_footdata;
	std::unique_ptr<PlayerData> my_playerdata;
	std::unique_ptr<Shape> shape;
};