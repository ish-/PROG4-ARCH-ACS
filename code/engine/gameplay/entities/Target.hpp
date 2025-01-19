#pragma once

#include <ode/collision.h>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/Entity.hpp>

class CollisionComp;

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

			private:
				graphics::ShapeList _shapeList;
				dGeomID _collisionGeomId;
			};
		}
	}
}
