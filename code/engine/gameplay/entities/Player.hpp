#pragma once

#include <engine/gameplay/entities/Character.hpp>

class PlayerCtrlComp;
class CollisionComp;

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

				virtual void update();

				virtual ~Player();

				bool hasJustMoved() const;

				PlayerCtrlComp* ctrlComp;
				CollisionComp* collisionComp;
			};
		}
	}
}
