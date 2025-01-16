#include "PlayerCtrlComp.h"
#include <engine/gameplay/Entity.hpp>

#include <engine/gameplay/EntityContext.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/gameplay/GameplayManager.hpp>

PlayerCtrlComp::PlayerCtrlComp(Entity* ownerP)
	: Component(ownerP) {

}

PlayerCtrlComp::~PlayerCtrlComp() {

}

void PlayerCtrlComp::update(float dt)
{
	dt;
	bool _justMoved = false;
	auto position = owner.getPosition();
	float rotation = owner.getRotation();

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Left))
	{
		_justMoved = true;
		position.x -= GameplayManager::CELL_SIZE;
		rotation = 180.f;
	}

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Right))
	{
		_justMoved = true;
		position.x += GameplayManager::CELL_SIZE;
		rotation = 0.f;
	}

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Up))
	{
		_justMoved = true;
		position.y -= GameplayManager::CELL_SIZE;
		rotation = -90.f;
	}

	if (owner._context.inputManager.isKeyJustPressed(sf::Keyboard::Down))
	{
		_justMoved = true;
		position.y += GameplayManager::CELL_SIZE;
		rotation = 90.f;
	}

	if (_justMoved)
	{
		owner.setPosition(position);
		owner.setRotation(rotation);

		owner.dGeomSetPosition(owner._collisionGeomId, position.x, position.y, 0);
	}
}
