#include "Rope.h"



Rope::Rope(float length, int nb_links, Box2DEngine* gameController) :
	length(length), nb_links(nb_links)
{
	Rope::elements = addBodyRope(gameController, length, nb_links);
	Rope::shape = std::unique_ptr<Circle>(new Circle());
}


std::vector<b2Body*> Rope::addBodyRope(Box2DEngine* gameController,float length, int nb_links) {

	// Link width and height
	float width = length / nb_links;

	// Vector of bodies
	std::vector<b2Body*> elements;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(width * UNRATIO, width * UNRATIO);
	fixtureDef.shape = &polygonShape;

	//filter
	fixtureDef.filter.categoryBits = MOVING_OBJECT;
	fixtureDef.filter.groupIndex = default;

	b2Body* link = gameController->getPhysicsWorld()->CreateBody(&bodyDef);
	b2Fixture* Fixture = link->CreateFixture(&fixtureDef);
	FixtureData* data = std::unique_ptr<FixtureData>(new FixtureData(sf::Color::Cyan, rope)).get();
	Fixture->SetUserData(static_cast<void*>(data));

	elements.push_back(link);

	// Joint properties
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.localAnchorA.Set(width * UNRATIO, 0);
	revoluteJointDef.localAnchorB.Set(-width * UNRATIO, 0);
	//filtre 
	b2Filter link_filter;
	link_filter.categoryBits = MOVING_OBJECT;
	link_filter.groupIndex = default;

	for (int i = 1; i < nb_links; i++) {
		// Create a new body
		b2Body* newLink = gameController->getPhysicsWorld()->CreateBody(&bodyDef);
		// add userData
		b2Fixture* newFixture = newLink->CreateFixture(&fixtureDef);
		newFixture->SetUserData(static_cast<void*> (data));

		newFixture->SetFilterData(link_filter);
		revoluteJointDef.bodyA = link;
		revoluteJointDef.bodyB = newLink;
		gameController->getPhysicsWorld()->CreateJoint(&revoluteJointDef);
		elements.push_back(newLink);

		link = newLink;

	}
	return elements;
}


void Rope::linkPlayers(Player* player1, Player* player2, b2World* world) {
	float width = length / nb_links;


    b2Body* body_player1 = player1->getBody();
	float player1_width = getBodyDimensions(body_player1).first;
    b2Body* body_player2 = player2->getBody();
	float player2_width = getBodyDimensions(body_player2).first;
    b2Body* beginBody = Rope::getElements()[0];
    b2Body* endBody = Rope::getElements()[nb_links-1];

    // Revolution Joints
	b2RevoluteJointDef revoluteJointDef1;
	revoluteJointDef1.localAnchorA.Set(-(player1_width*2 - 1)* UNRATIO, 0);
	revoluteJointDef1.localAnchorB.Set((width/2+1)* UNRATIO, 0);


	
    // Link player1 to beginBody
    revoluteJointDef1.bodyA = endBody;
    revoluteJointDef1.bodyB = body_player1;
	world->CreateJoint(&revoluteJointDef1);

	// Revolution Joints
	b2RevoluteJointDef revoluteJointDef2;
	revoluteJointDef2.localAnchorA.Set((player2_width*2 -1)*UNRATIO, 0);
	revoluteJointDef2.localAnchorB.Set((-width/2 - 1)* UNRATIO, 0);

    // Link player2 to endBody
	revoluteJointDef2.bodyA = body_player2;
	revoluteJointDef2.bodyB = beginBody;
	world->CreateJoint(&revoluteJointDef2);
}

void Rope::draw(sf::Color color, sf::RenderWindow* window) {
	
	for (auto body : elements) {
		Rope::shape->draw(body, color, window);
	}
	

}
