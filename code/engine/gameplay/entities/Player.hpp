#pragma once

#include <engine/gameplay/entities/Character.hpp>

class PlayerCtrlComp;
class CollisionComp;
class ShapeComp;

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Player : public Character
			{
				using Super = Character;

			public:
				Player(EntityContext &context);
				virtual ~Player();

				virtual void update();
					
				virtual void draw();

				PlayerCtrlComp* ctrlComp;
				CollisionComp* collisionComp;
				ShapeComp* shapeComp;
			};
		}
	}
}
