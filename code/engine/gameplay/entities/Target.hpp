#pragma once

#include <memory>
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

				std::shared_ptr<CollisionComp> collisionComp;
				std::shared_ptr<ShapeComp> shapeComp;
			};
		}
	}
}
