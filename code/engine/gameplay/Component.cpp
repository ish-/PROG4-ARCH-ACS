#include "Component.hpp"
#include "Entity.hpp"
#include <engine/LOG.hpp>

Component::Component()
{
	//owner.addComponent(this);
}

Component::~Component()
{
	//getOwner()->removeComponent(this);
	//LOG("~Component()");
}

void Component::update(float dt)
{
	dt;
}


