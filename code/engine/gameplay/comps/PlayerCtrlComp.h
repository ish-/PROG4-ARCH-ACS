#pragma once
#include "engine/gameplay/Component.hpp"

class PlayerCtrlComp : public Component
{
public:
	PlayerCtrlComp(class engine::gameplay::Entity* ownerP, int updateOrderP = 100);
	PlayerCtrlComp() = delete;
	virtual ~PlayerCtrlComp();
	PlayerCtrlComp(const PlayerCtrlComp&) = delete;
	PlayerCtrlComp& operator=(const PlayerCtrlComp&) = delete;

	void update(float dt) override;

	bool justMoved = false;
};
