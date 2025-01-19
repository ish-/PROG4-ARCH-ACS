#include "Character.hpp"

#include <engine/gameplay/EntityContext.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include "engine/LOG.hpp"

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Character::Character(EntityContext &context)
				: Entity{ context }
			{
			}

			Character::~Character()
			{
				LOG("~Character()");
			}

			void Character::draw()
			{
				
			}
		}
	}
}
