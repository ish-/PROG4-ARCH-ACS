#include "engine/Engine.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>
#include "engine/LOG.hpp"

namespace engine
{
	Engine::Engine()
		: _gameplayManager{ _graphicsManager, _inputManager, _physicsManager }
		, _graphicsManager{ *this, _gameplayManager }
	{
	}

	bool Engine::loadConfiguration()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file("configuration.xml");

		if (result)
		{
			assert(!doc.empty());
			auto configuration = doc.first_child();
			_startMap = configuration.child_value("start_map");

			return true;
		}
		else
		{
			std::cerr << "Configuration parsed with errors." << std::endl;
			std::cerr << "Error description: " << result.description() << std::endl;
			std::cerr << "Error offset: " << result.offset << std::endl;

			return false;
		}
	}

	bool Engine::setUp()
	{
		if (!_graphicsManager.setUp())
		{
			return false;
		}

		if (!_physicsManager.setUp())
		{
			return false;
		}

		return true;
	}

	void Engine::tearDown()
	{
		LOG("Engine::tearDown()");
		_physicsManager.tearDown();
		_graphicsManager.tearDown();
	}

	void Engine::run()
	{
		_running = true;

		_gameplayManager.loadMap(_startMap);

		sf::Clock clock;
		while (_running)
		{
			_deltaTime = clock.restart().asSeconds();

			_inputManager.clear();

			_physicsManager.update();
			_graphicsManager.update();
			bool bExit = _gameplayManager.update();

			_graphicsManager.clear();

			_gameplayManager.draw();

			_graphicsManager.display();

			if (bExit)
				break;
		}
	}

	float Engine::getDeltaTime() const
	{
		return _deltaTime;
	}

	void Engine::onEvent(const sf::Event &event)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_running = false;
			break;

		case sf::Event::LostFocus:
			_inputManager.setActive(false);
			break;

		case sf::Event::GainedFocus:
			_inputManager.setActive(true);
			break;

		case sf::Event::KeyPressed:
			_inputManager.onKeyPressed(event.key);
			break;

		case sf::Event::KeyReleased:
			_inputManager.onKeyReleased(event.key);
			break;

		default:
			break;
		}
	}
}
