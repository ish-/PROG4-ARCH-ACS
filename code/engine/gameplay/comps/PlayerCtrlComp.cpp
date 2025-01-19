#include <engine/gameplay/comps/PlayerCtrlComp.h>

#include <engine/gameplay/Entity.hpp>

#include <engine/gameplay/EntityContext.hpp>
#include <engine/input/InputManager.hpp>

#include "engine/LOG.hpp"
#include "engine/config.hpp"

PlayerCtrlComp::PlayerCtrlComp(Entity* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP) {

}

PlayerCtrlComp::~PlayerCtrlComp() {
	LOG("~PlayerCtrlComp");
}

void PlayerCtrlComp::update(float dt)
{
	dt;
	justMoved = false;
	auto position = owner.getPosition();
	float rotation = owner.getRotation();

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Left))
	{
		justMoved = true;
		position.x -= engine::config::CELL_SIZE;
		rotation = 180.f;
	}

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Right))
	{
		justMoved = true;
		position.x += engine::config::CELL_SIZE;
		rotation = 0.f;
	}

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Up))
	{
		justMoved = true;
		position.y -= engine::config::CELL_SIZE;
		rotation = -90.f;
	}

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Down))
	{
		justMoved = true;
		position.y += engine::config::CELL_SIZE;
		rotation = 90.f;
	}

	if (justMoved) {
		owner.setPosition(position);
		owner.setRotation(rotation);
	}
}
