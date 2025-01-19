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

std::set<CollisionComp*> CollisionComp::getCollidedComps()
{

	auto collisions = owner._context.physicsManager.getCollisionsWith(_collisionGeomId);
	std::set<CollisionComp*> comps;
	for (auto& geomId : collisions)
	{
		CollisionComp* entity = reinterpret_cast<CollisionComp*>(dGeomGetData(geomId));
		if (entity)
			comps.insert(entity);
	}
	return comps;
}

void CollisionComp::update(float dt)
{
	dt;
	if (owner.bIsMoved)
	{
		dGeomSetPosition(_collisionGeomId, owner._position.x, owner._position.y, 0);
	}
}
