#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
	Enemy(Vector2 pos, Texture2D texture_idle);

	void Update(float dt) override;

	void setTarget(Character* target);
	void setFrozen(bool frozen);
	bool getFrozen() { return frozen; }
	Rectangle getCollisionRec() override;

private:
	bool frozen{false};
	bool isAnimationReset{false};
	void Freeze();


	Character* target{};
	Vector2 velocity{};
	Texture2D enemyFrozen{ LoadTexture("sprites/enemy_frozen_sheet.png")};
};

#endif
