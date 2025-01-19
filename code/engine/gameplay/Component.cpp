#include "Component.hpp"
#include "Entity.hpp"
#include <engine/LOG.hpp>

Component::Component(engine::gameplay::Entity* ownerP, int updateOrderP) :
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
	LOG("~Component()");
}

void Component::update(float dt)
{
	dt;
}


