#pragma once

namespace engine
{
	namespace gameplay
	{
		class Entity;
	}
}

class Component
{
public:
	Component(engine::gameplay::Entity* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void update(float dt);
	//virtual void onUpdateWorldTransform() {}

//protected:
	engine::gameplay::Entity& owner;
	int updateOrder;		// Order of the component in the actor's updateComponent method
};

