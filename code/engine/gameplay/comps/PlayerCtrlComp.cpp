#include "PlayerCtrlComp.h"
#include <engine/gameplay/Entity.hpp>

PlayerCtrlComp::PlayerCtrlComp(Entity* ownerP)
	: Component(ownerP) {

}

PlayerCtrlComp::~PlayerCtrlComp() {

}


void PlayerCtrlComp::update(float dt)
{
	dt;
	//_justMoved = false;
	auto position = owner.getPosition();
	//float rotation = getRotation();
}
