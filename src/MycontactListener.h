#pragma once
#include <box2d/box2d.h>
#include"Global.h"

extern int numFootContact;

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
private:

};

inline MyContactListener::MyContactListener()
{
}

inline MyContactListener::~MyContactListener()
{
}
