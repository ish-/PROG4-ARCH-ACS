#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics/Transform.hpp>

class Component;

namespace engine
{
	namespace gameplay
	{
		struct EntityContext;

		class Entity
		{
		public:
			static unsigned int id;

			Entity(EntityContext &context);
			virtual ~Entity();

			virtual void update();
			virtual void draw() = 0;

			std::string name = "_entity";
			void setName(std::string preferName);

			const sf::Vector2f &getPosition() const;
			void setPosition(const sf::Vector2f &newPosition);

			float getRotation() const;
			void setRotation(float newRotation);

			const sf::Transform &getTransform() const;

			//EntityContext& getContext() const;

		//protected:
			EntityContext & _context;

		//private:
			sf::Vector2f _position{};
			float _rotation{ 0.f };
			sf::Transform _transform;
			bool bIsMoved{ false };

			void updateTransform();

		// Component
		public:
			void updateComponents(float dt);
			void clearComponents();
			void addComponent(Component* component);
			void removeComponent(Component* component);

			std::vector<Component*> components;
		};
	}
}

using engine::gameplay::Entity;
