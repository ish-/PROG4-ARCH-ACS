#pragma once

#include <memory>
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

				std::shared_ptr<PlayerCtrlComp> ctrlComp;
				std::shared_ptr<CollisionComp> collisionComp;
				std::shared_ptr<ShapeComp> shapeComp;
			};
		}
	}
}
