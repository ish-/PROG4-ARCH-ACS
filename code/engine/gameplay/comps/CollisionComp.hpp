#pragma once
#include <array>

#include "engine/gameplay/Component.hpp"

#include <ode/collision.h>
#include <set>
#include <engine/gameplay/Entity.hpp>

class CollisionComp;

using CollidedComps = std::set<CollisionComp*>;

class CollisionComp : public Component
{
public:
    CollisionComp(class engine::gameplay::Entity* ownerP, float lx, float ly, float lz, int updateOrderP = 100);
	CollisionComp() = delete;
	virtual ~CollisionComp();
	CollisionComp(const CollisionComp&) = delete;
	CollisionComp& operator=(const CollisionComp&) = delete;

	CollidedComps getCollidedComps();
	void update(float dt) override;

	dGeomID _collisionGeomId;
};
