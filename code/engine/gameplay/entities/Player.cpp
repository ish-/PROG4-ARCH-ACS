#include "engine/gameplay/entities/Player.hpp"

#include <ode/collision.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/entities/Target.hpp>
#include <engine/Engine.hpp>

#include <engine/gameplay/comps/PlayerCtrlComp.h>
#include <engine/gameplay/comps/CollisionComp.hpp>
#include "engine/LOG.hpp"
#include "engine/config.hpp"

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Player::Player(EntityContext& context)
				: Character{ context }
			{
				ctrlComp = new PlayerCtrlComp(this);
				collisionComp = new CollisionComp(this,
					engine::config::CELL_SIZE * 0.9f, engine::config::CELL_SIZE * 0.9f, 1.f);

				_shapeList.load("player");
			}

			void Player::update()
			{
				Super::update();

				CollidedEntities entities = collisionComp->getCollidedEntities();
				for (auto entity : entities)
				{
					if (auto targetEntity
							= dynamic_cast<entities::Target*>(entity))
						_context.entityListener.loadNextMap();
				}
			}

			Player::~Player()
			{
				LOG("~Player()");
			}
		}
	}
}
