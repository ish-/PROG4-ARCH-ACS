#pragma once

#include <memory>

namespace engine
{
	namespace gameplay
	{
		class Entity;
	}
}

class Component
	: public std::enable_shared_from_this<Component>
{
public:
	Component();
	virtual ~Component();

	virtual void update(float dt);
	//virtual void onUpdateWorldTransform() {}
	int updateOrder;		// Order of the component in the actor's updateComponent method

// owner
protected:
	std::weak_ptr<engine::gameplay::Entity> _owner;

public:
	std::shared_ptr<engine::gameplay::Entity> getOwner() {
		return _owner.lock();
	}

	void setOwner(const std::shared_ptr<engine::gameplay::Entity>& actor) {
		_owner = actor;
	}
};

