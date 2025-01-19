#include "engine/gameplay/GameplayManager.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <pugixml/pugixml.hpp>
#include <engine/Engine.hpp>
#include <engine/gameplay/entities/Enemy.hpp>
//#include <engine/gameplay/entities/Player.hpp>
//#include <engine/gameplay/entities/Target.hpp>
#include <engine/LOG.hpp>

namespace engine
{
	namespace gameplay
	{
		const float Manager::CELL_SIZE = 50.f;

		Manager::Manager(graphics::Manager &graphicsManager, input::Manager &inputManager, physics::Manager &physicsManager)
			: _context{ graphicsManager, inputManager, physicsManager, *this }
		{
		}

		bool Manager::update()
		{
			for (auto entity : _entities)
			{
				entity->update();
			}

			_preventMapCompletion = false;
			if (_nextMapRequested)
			{
				if (_nextMapName.empty())
					return stop("Win!");

				_nextMapRequested = false;
				loadMap(_nextMapName);
			}

			if (_context.inputManager.isKeyJustPressed(sf::Keyboard::Escape))
				return stop("Escape pressed..");

			if (bGameover)
				return stop("Gameover!");
		
			return false;
		}

		void Manager::draw()
		{
			for (auto entity : _entities)
			{
				entity->draw();
			}
		}

		bool Manager::stop(char* msg = "Untitled stop...")
		{
			std::cout << msg << std::endl;
			clearMapEntities();
			return true;
		}

		void Manager::clearMapEntities() {
			LOG("Manager::clearMapEntities()");
			for (auto entity : _entities)
			{
				delete entity;
			}
			_entities.clear();
		}

		void Manager::loadMap(const std::string& mapName)
		{
			LOG("Manager::loadMap()");
			bGameover = false;

			clearMapEntities();

			std::stringstream filename;
			filename << "maps/" << mapName << ".xml";

			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

			if (result)
			{
				assert(!doc.empty());
				auto xmlMap = doc.first_child();

				_rows = std::stoi(xmlMap.child_value("rows"));
				assert(_rows >= 0);

				_columns = std::stoi(xmlMap.child_value("columns"));
				assert(_columns >= 0);

				for (auto &xmlElement : xmlMap.child("elements").children())
				{
					if (!std::strcmp(xmlElement.name(), "enemy"))
					{
						int row = std::stoi(xmlElement.child_value("row"));
						assert(row >= 0 && row < _rows);

						int column = std::stoi(xmlElement.child_value("column"));
						assert(column >= 0 && column < _columns);

						std::string archetypeName = xmlElement.child_value("archetype");

						auto entity = new entities::Enemy{ _context, archetypeName };
						entity->setName("Enemy");
						entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

						_entities.insert(entity);
					}

					if (!std::strcmp(xmlElement.name(), "player"))
					{
						/*int row = std::stoi(xmlElement.child_value("row"));
						assert(row >= 0 && row < _rows);

						int column = std::stoi(xmlElement.child_value("column"));
						assert(column >= 0 && column < _columns);

						auto player = new entities::Player{ _context };
						player->setName("Player");
						player->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

						_entities.insert(player);
						_playerEntity = player;*/
					}

					if (!std::strcmp(xmlElement.name(), "target"))
					{
						/*int row = std::stoi(xmlElement.child_value("row"));
						assert(row >= 0 && row < _rows);

						int column = std::stoi(xmlElement.child_value("column"));
						assert(column >= 0 && column < _columns);

						auto entity = new entities::Target{ _context };
						entity->setName("Target");
						entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

						_entities.insert(entity);*/
					}
				}

				_currentMapName = mapName;
				_nextMapName = xmlMap.child_value("next_map");

				// JIRA-1337: Map is skipped.
				// This prevents the map to be completed during the first frame. I don't know why this happens.
				_preventMapCompletion = true;
			}
			else
			{
				std::cerr << "Map [" << mapName << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
			}
		}

		void Manager::gameOver()
		{
			bGameover = true;
			/*loadMap(_currentMapName);*/
		}

		void Manager::loadNextMap()
		{
			LOG("Manager::loadNextMap()");
			if (!_preventMapCompletion)
			{
				_nextMapRequested = true;
			}
		}

		const entities::Player &Manager::getPlayer() const
		{
			assert(_playerEntity);
			return *_playerEntity;
		}

		sf::Vector2f Manager::getViewCenter() const
		{
			return sf::Vector2f{ _columns * (CELL_SIZE / 2.f), _rows * (CELL_SIZE / 2.f) };
		}
	}
}
