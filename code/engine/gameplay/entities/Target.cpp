#include "Target.hpp"

#include <engine/gameplay/EntityContext.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

#include <engine/gameplay/comps/CollisionComp.hpp>
#include <engine/gameplay/comps/ShapeComp.hpp>

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
				collisionComp = addComponent<CollisionComp>(engine::config::CELL_SIZE * 0.9f, engine::config::CELL_SIZE * 0.9f, 1.f);
				shapeComp = addComponent<ShapeComp>("target");
			}

			Target::~Target()
			{
				LOG("~Target()");
			}

			void Target::draw()
			{
				shapeComp->draw();
			}
		}
	}
}
