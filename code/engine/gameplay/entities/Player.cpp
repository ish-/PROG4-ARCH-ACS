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
#include "engine/LOG.hpp"
#include "engine/config.hpp"

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Player::Player(EntityContext &context)
				: Character{ context }
			{
				ctrlComp = new PlayerCtrlComp(this);
				_shapeList.load("player");

				_collisionGeomId = dCreateBox(context.physicsManager.getSpaceId(), engine::config::CELL_SIZE * 0.9f, engine::config::CELL_SIZE * 0.9f, 1.f);
				dGeomSetData(_collisionGeomId, this);
			}

			void Player::update()
			{
				Super::update();

				if (ctrlComp->justMoved)
				{
					dGeomSetPosition(_collisionGeomId, _position.x, _position.y, 0);
				}

				auto collisions = _context.physicsManager.getCollisionsWith(_collisionGeomId);
				for (auto &geomId : collisions)
				{
					auto entity = reinterpret_cast<Entity *>(dGeomGetData(geomId));
					auto targetEntity = dynamic_cast<entities::Target *>(entity);
					if (targetEntity)
					{
						_context.entityListener.loadNextMap();
					}
				}
			}

			Player::~Player()
			{
				LOG("~Player()");
			}

			bool Player::hasJustMoved() const
			{
				return ctrlComp->justMoved;
			}
		}
	}
}
