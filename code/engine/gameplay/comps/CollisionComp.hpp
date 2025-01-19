#pragma once
#include <array>

#include "engine/gameplay/Component.hpp"

#include <ode/collision.h>
#include <set>
#include <engine/gameplay/Entity.hpp>

using CollidedEntities = std::set<Entity*>;

class CollisionComp : public Component
{
public:
    CollisionComp(class engine::gameplay::Entity* ownerP, float lx, float ly, float lz, int updateOrderP = 100);
    CollisionComp(class engine::gameplay::Entity* ownerP, int updateOrderP = 100);
	CollisionComp() = delete;
	virtual ~CollisionComp();
	CollisionComp(const CollisionComp&) = delete;
	CollisionComp& operator=(const CollisionComp&) = delete;

	CollidedEntities getCollidedEntities();
	void update(float dt) override;

	dGeomID _collisionGeomId;
};
