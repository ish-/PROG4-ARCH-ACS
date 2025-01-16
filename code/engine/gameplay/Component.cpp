#include "Component.hpp"
#include "Entity.hpp"

Component::Component(engine::gameplay::Entity* ownerP, int updateOrderP) :
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	//owner.addComponent(this);
}

Component::~Component()
{
	//owner.removeComponent(this);
}

//void Component::update(float dt)
//{
//}


