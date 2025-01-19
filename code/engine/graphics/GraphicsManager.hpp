#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>

using Shapes = std::vector<sf::Shape*>;

namespace engine
{
	class EventListener;

	namespace graphics
	{
		
		class ViewProvider;

		class Manager
		{
		public:
			Manager(EventListener &eventListener, ViewProvider &viewProvider);

			bool setUp();
			void tearDown();

			void update();

			void clear();
			void draw(const Shapes& shapes, const sf::Transform& transform);
			void display();

		private:
			EventListener & _eventListener;
			ViewProvider & _viewProvider;

			sf::RenderWindow _window;

			static const sf::Int16 WINDOW_WIDTH = 800;
			static const sf::Int16 WINDOW_HEIGHT = 600;
		};
	}
}
