#pragma once
#include "engine/gameplay/Component.hpp"
//#include <engine/gameplay/Entity.hpp>

class PlayerCtrlComp : public Component
{
	PlayerCtrlComp(class engine::gameplay::Entity* ownerP);
	PlayerCtrlComp() = delete;
	virtual ~PlayerCtrlComp();
	PlayerCtrlComp(const PlayerCtrlComp&) = delete;
	PlayerCtrlComp& operator=(const PlayerCtrlComp&) = delete;
		
	void update(float dt) override;
};
