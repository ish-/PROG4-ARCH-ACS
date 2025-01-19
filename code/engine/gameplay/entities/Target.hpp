#pragma once

#include <ode/collision.h>
#include <engine/gameplay/Entity.hpp>

class CollisionComp;
class ShapeComp;

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Target : public Entity
			{
			public:
				Target(EntityContext &context);
				~Target();

				//virtual void update() override;

				virtual void draw() override;

				CollisionComp* collisionComp;
				ShapeComp* shapeComp;
			};
		}
	}
}
