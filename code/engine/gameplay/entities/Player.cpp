#include "engine/gameplay/entities/Player.hpp"

#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/EntityListener.hpp>
#include <engine/gameplay/entities/Target.hpp>

#include <engine/gameplay/comps/PlayerCtrlComp.h>
#include <engine/gameplay/comps/CollisionComp.hpp>
#include <engine/gameplay/comps/ShapeComp.hpp>

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

				shapeComp = new ShapeComp(this);
				shapeComp->load("player");
			}

			void Player::update()
			{
				Super::update();

				CollidedComps comps = collisionComp->getCollidedComps();
				for (auto comp : comps)
				{
					if (comp == nullptr)
						continue;

					Entity* owner = &(comp->owner);
					if (!owner)
						continue;

					if (auto targetEntity = dynamic_cast<entities::Target*>(owner)) {
						if (!targetEntity)
							continue;

						LOG("Collision with Target");
						_context.entityListener.loadNextMap();
					}
				}
			}

			void Player::draw()
			{
				shapeComp->draw();
			}

			Player::~Player()
			{
				LOG("~Player()");
			}
		}
	}
}
