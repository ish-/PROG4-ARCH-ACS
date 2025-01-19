#include "Target.hpp"

#include <engine/gameplay/EntityContext.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

#include <engine/gameplay/comps/CollisionComp.hpp>

#include "engine/config.hpp"
#include "engine/LOG.hpp"

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Target::Target(EntityContext &context)
				: Entity{ context }
			{
				_shapeList.load("target");

				collisionComp = new CollisionComp(this, engine::config::CELL_SIZE * 0.9f, engine::config::CELL_SIZE * 0.9f, 1.f);

				/*_collisionGeomId = dCreateBox(context.physicsManager.getSpaceId(), engine::config::CELL_SIZE * 0.9f, engine::config::CELL_SIZE * 0.9f, 1.f);
				dGeomSetData(_collisionGeomId, this);*/
			}

			Target::~Target()
			{
				LOG("~Target()");
			}

			void Target::draw()
			{
				_context.graphicsManager.draw(_shapeList, getTransform());
			}
		}
	}
}
