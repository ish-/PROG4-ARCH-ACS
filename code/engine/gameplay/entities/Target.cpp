#include "Target.hpp"

#include <engine/gameplay/EntityContext.hpp>

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
				collisionComp = new CollisionComp(this, engine::config::CELL_SIZE * 0.9f, engine::config::CELL_SIZE * 0.9f, 1.f);
				shapeComp = new ShapeComp(this);
				shapeComp->load("target");
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
