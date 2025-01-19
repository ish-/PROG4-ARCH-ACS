#include "CollisionComp.hpp"

#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/EntityContext.hpp>

#include "engine/LOG.hpp"
#include "engine/config.hpp"

CollisionComp::CollisionComp(Entity* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP) {}

CollisionComp::CollisionComp(Entity* ownerP, float lx, float ly, float lz, int updateOrderP)
	: Component(ownerP, updateOrderP) {

    _collisionGeomId = dCreateBox(owner._context.physicsManager.getSpaceId(), lx, ly, lz);
    dGeomSetData(_collisionGeomId, this);
}

CollisionComp::~CollisionComp() {
	LOG("~CollisionComp");
	dGeomDestroy(_collisionGeomId);
}

std::set<Entity*> CollisionComp::getCollidedEntities()
{
	
	auto collisions = owner._context.physicsManager.getCollisionsWith(_collisionGeomId);
	std::set<Entity*> entities;
	for (auto& geomId : collisions)
	{
		Entity* entity = reinterpret_cast<Entity*>(dGeomGetData(geomId));
		if (entity)
			entities.insert(entity);
	}
	return entities;
}

void CollisionComp::update(float dt)
{
	dt;
	if (owner.bIsMoved)
	{
		dGeomSetPosition(_collisionGeomId, owner._position.x, owner._position.y, 0);
	}
}
