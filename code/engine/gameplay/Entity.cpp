#include "Entity.hpp"
#include "Component.hpp"

namespace engine
{
	namespace gameplay
	{
		Entity::Entity(EntityContext &context)
			: _context{ context }
		{
		}

		void Entity::update()
		{
			updateComponents(0.0f);
		}

		const sf::Vector2f &Entity::getPosition() const
		{
			return _position;
		}

		void Entity::setPosition(const sf::Vector2f &newPosition)
		{
			_position = newPosition;
			updateTransform();
		}

		float Entity::getRotation() const
		{
			return _rotation;
		}

		void Entity::setRotation(float newRotation)
		{
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
