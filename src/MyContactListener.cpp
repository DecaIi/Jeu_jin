#include "MyContactListener.h"
#include <iostream>

//gestion des champs de vue 
void binginviewdetextion(b2Fixture * A, b2Fixture* B) {
	FixtureData* fixtureDataA = static_cast<FixtureData*> (A->GetUserData());
	FixtureData* fixtureDataB = static_cast<FixtureData*> (B->GetUserData());
	if (  fixtureDataA->getDataType() == viewField ){
		
		b2RayCastInput input;
		input.p1 = A->GetBody()->GetPosition();
		input.p2 = B->GetBody()->GetPosition();
		input.maxFraction = 1;
		std::unique_ptr< b2RayCastOutput> output= std::make_unique<b2RayCastOutput>();
		if (!A->RayCast(output.get(), input, 1)) {
			((ViewFieldData*)fixtureDataA)->increaIncreaceEntitidetected();
		}
	}
	if (fixtureDataB->getDataType() == viewField) {

		b2RayCastInput input;
		input.p1 = B->GetBody()->GetPosition();
		input.p2 = A->GetBody()->GetPosition();
		input.maxFraction = 1;
		std::unique_ptr< b2RayCastOutput> output = std::make_unique<b2RayCastOutput>();
		if (! B->RayCast(output.get(), input, 1)) {
			((ViewFieldData*)fixtureDataB)->increaIncreaceEntitidetected();
		}
	}
}
void endviewdetextion(b2Fixture* A, b2Fixture* B) {
	FixtureData* fixtureDataA = static_cast<FixtureData*> (A->GetUserData());
	FixtureData* fixtureDataB = static_cast<FixtureData*> (B->GetUserData());
	if (fixtureDataA->getDataType() == viewField) {
		b2RayCastInput input;
		input.p1 = A->GetBody()->GetPosition();
		input.p2 = B->GetBody()->GetPosition();
		input.maxFraction = 1;
		std::unique_ptr< b2RayCastOutput> output = std::make_unique<b2RayCastOutput>();
		if (! A->RayCast(output.get(), input, 1)) {
			((ViewFieldData*)fixtureDataA)->DecreaseEntityDetected();
		}

	}
	if (fixtureDataB->getDataType() == viewField) {
		b2RayCastInput input;
		input.p1 = B->GetBody()->GetPosition();
		input.p2 = A->GetBody()->GetPosition();
		input.maxFraction = 1;
		std::unique_ptr<b2RayCastOutput> output = std::make_unique<b2RayCastOutput>();
		if (! B->RayCast(output.get(), input, 1)) {
			((ViewFieldData*)fixtureDataB)->DecreaseEntityDetected();
		}
	}
}

void end_contact_action(FixtureData* fixtureData) {
	switch (fixtureData->getDataType())
	{
	case foot:
		((FootData*)fixtureData)->DecreaceNumFootContact(); 
		break;
	case MonsterLfoot:
		((FootData*)fixtureData)->DecreaceNumFootContact();
		break;
	case MonsterRfoot:
		((FootData*)fixtureData)->DecreaceNumFootContact();
		break;
	case hand:
		((HandData*)fixtureData)->DecreaceNumhandContact();
		break;
	default:
		break;
	}
}

void BeginContact_action(FixtureData* fixtureData) {
	switch (fixtureData->getDataType())
	{
	case foot:
		((FootData*)fixtureData)->IncreaceNumFootContact();
		break;
	case MonsterLfoot:
		((FootData*)fixtureData)->IncreaceNumFootContact();
		break;
	case MonsterRfoot:
		((FootData*)fixtureData)->IncreaceNumFootContact();
		break;
	case hand:
		((HandData*)fixtureData)->IncreaceNumhandContact();
		break;
	default:
		break;
	}
}

void MyContactListener::BeginContact(b2Contact* contact) {
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();

    FixtureData* fixtureData = static_cast<FixtureData*>( fixtureUserData );
    if (fixtureData != NULL) {
		BeginContact_action(fixtureData);
    }

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    fixtureData = static_cast<FixtureData*>( fixtureUserData );
    if (fixtureData != NULL) {
		BeginContact_action(fixtureData);
    }
	
	if (contact->GetFixtureA() != NULL && contact->GetFixtureB() != NULL) {
		binginviewdetextion(contact->GetFixtureA(), contact->GetFixtureB());
	}

}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	FixtureData* fixtureData = static_cast<FixtureData*>(fixtureUserData);
    if (fixtureData != NULL) {
        end_contact_action(fixtureData);
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
	fixtureData = static_cast<FixtureData*>(fixtureUserData);
    if (fixtureData != NULL) {
        end_contact_action(fixtureData);
    }
	if (contact->GetFixtureA() != NULL && contact->GetFixtureB() != NULL) {
		endviewdetextion(contact->GetFixtureA(), contact->GetFixtureB());
	}
}

MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
}
