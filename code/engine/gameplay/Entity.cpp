#include "Entity.hpp"
#include "Component.hpp"

#include "engine/LOG.hpp"

namespace engine
{
	namespace gameplay
	{
		unsigned int Entity::id = 0;

		Entity::Entity(EntityContext &context)
			: _context{ context }
		{

		}

		Entity::~Entity()
		{
			LOG("~Entity()", name);
			clearComponents();
		}

		void Entity::update()
		{
			updateComponents(0.0f);
		}

		void Entity::setName(std::string preferName)
		{
			name = preferName + "-" + std::to_string(Entity::id++);
		}

		const sf::Vector2f &Entity::getPosition() const
		{
			return _position;
		}

		void Entity::setPosition(const sf::Vector2f &newPosition)
		{
			_position = newPosition;
			updateTransform();
			bIsMoved = true;
		}

		float Entity::getRotation() const
		{
			return _rotation;
		}

		void Entity::setRotation(float newRotation)
		{
			bIsMoved = true;
			_rotation = newRotation;
			updateTransform();
		}

		const sf::Transform &Entity::getTransform() const
		{
			return _transform;
		}

		/*EntityContext& Entity::getContext() const
		{
			return _context;
		}*/

		void Entity::updateTransform()
		{
			_transform = sf::Transform::Identity;
			_transform.translate(_position);
			_transform.rotate(_rotation);
		}

		// Component


		void Entity::updateComponents(float dt)
		{
			for (auto component : components)
			{
				component->update(dt);
			}
		}

		void Entity::clearComponents() {
			/*for (auto component : components)
				delete component;*/
			components.clear();
		}

		void Entity::addComponent(Component* component)
		{
			// Find the insertion point in the sorted vector
			// (The first element with a order higher than me)
			int myOrder = component->getUpdateOrder();
			auto iter = begin(components);
			for (; iter != end(components); ++iter)
			{
				if (myOrder < (*iter)->getUpdateOrder())
				{
					break;
				}
			}

			// Inserts element before position of iterator
			//components.insert(iter, std::shared_ptr<Component>(component));
			components.insert(iter, component);
		}

		void Entity::removeComponent(Component* component)
		{
			auto iter = std::find(begin(components), end(components), component);
			if (iter != end(components))
			{
				components.erase(iter);
			}
		}

	}
}
