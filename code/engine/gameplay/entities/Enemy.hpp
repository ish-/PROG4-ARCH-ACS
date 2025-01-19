#pragma once

#include <string>
#include <memory>
#include <engine/gameplay/entities/Character.hpp>

class ShapeComp;

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Enemy : public Character
			{
			public:
				Enemy(EntityContext &context, const std::string &archetypeName);

				virtual void update() override;
				virtual void draw();

				std::shared_ptr<ShapeComp> shapeComp;

			private:
				float _visionRadius{ 0 };
				int _shootDelay{ 0 };
				int _shootDelayCounter{ 0 };

				void loadArchetype(const std::string &archetypeName);
			};
		}
	}
}
