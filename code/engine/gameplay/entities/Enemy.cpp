#include "Enemy.hpp"

#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/config.hpp>
#include <engine/gameplay/EntityContext.hpp>
// TODO: get rid of Gameplay
#include <engine/gameplay/EntityListener.hpp>
#include "engine/config.hpp"
#include <engine/gameplay/entities/Player.hpp>
#include <engine/gameplay/comps/ShapeComp.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Enemy::Enemy(EntityContext &context, const std::string &archetypeName)
				: Character{ context }
			{
				shapeComp = new ShapeComp(this);
				shapeComp->load("guard");

				loadArchetype(archetypeName);
			}

			void Enemy::update()
			{
				auto &player = _context.entityListener.getPlayer();
				if (player.bIsMoved)
				{
					auto &playerPosition = player.getPosition();
					auto &myPosition = getPosition();

					auto offset = myPosition - playerPosition;
					offset /= engine::config::CELL_SIZE;
					float distance2 = offset.x * offset.x + offset.y * offset.y;
					if (distance2 <= _visionRadius * _visionRadius)
					{
						if (_shootDelayCounter < _shootDelay)
						{
							++_shootDelayCounter;
						}
						else
						{
							_context.entityListener.gameOver();
						}
					}
					else
					{
						_shootDelayCounter = 0;
					}
				}
			}

			void Enemy::draw()
			{
				shapeComp->draw();
			}

			void Enemy::loadArchetype(const std::string &archetypeName)
			{
				std::stringstream filename;
				filename << "archetypes/" << archetypeName << ".xml";

				pugi::xml_document doc;
				pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

				if (result)
				{
					assert(!doc.empty());
					auto xmlArchetype = doc.first_child();

					std::string shapeListName = xmlArchetype.child_value("shapelist");
					assert(shapeComp->load(shapeListName));

					_visionRadius = std::stof(xmlArchetype.child_value("vision_radius"));
					assert(_visionRadius > 0.f);

					_shootDelay = std::stoi(xmlArchetype.child_value("shoot_delay"));
					assert(_shootDelay >= 0);
				}
				else
				{
					std::cerr << "Archetype [" << archetypeName << "] parsed with errors." << std::endl;
					std::cerr << "Error description: " << result.description() << std::endl;
					std::cerr << "Error offset: " << result.offset << std::endl;
				}
			}
		}
	}
}
