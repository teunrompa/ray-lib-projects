#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include <iostream>

#include "raymath.h"
#include "Enemy.h"

class Projectile
{
public:
	void Update(float dt);
	void Init(Vector2 position, float rotation, Texture2D texture);

	bool active = true;
	bool hitObj = false; //TODO: implement collision width objects

	Rectangle getCollisionRec() { return hitBox; }
	void setActive(const bool active) { this->active = active; }

	void checkCollisionWith(Enemy* enemy);

private:

	float speed{900};
	float lifeTime {0};
	float maxLifeTime{7};
	float rotation{};

	Vector2 position{};
	Vector2 velocity{1, 1};
	Vector2 direction{0, 1};

	Vector2 origin{};
	Rectangle source{};
	Rectangle destRec{};

	Rectangle hitBox{};

	Texture2D projectileTexture{};

	void Draw();
	void UpdatePosition(float dt);

};

#endif
