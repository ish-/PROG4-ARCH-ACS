#pragma once
#include <string>
#include <SFML/Graphics/Shape.hpp>

#include "engine/gameplay/Component.hpp"
#include "engine/gameplay/Entity.hpp"

//class Shapes;
using Shapes = std::vector<sf::Shape*>;

class ShapeComp : public Component
{
public:
    ShapeComp(class engine::gameplay::Entity* ownerP, int updateOrderP = 100);
	ShapeComp() = delete;
	virtual ~ShapeComp();
	ShapeComp(const ShapeComp&) = delete;
	ShapeComp& operator=(const ShapeComp&) = delete;

    bool load(const std::string &name);

    Shapes& getShapes();

    void draw ();

private:
    Shapes _shapes;
};
