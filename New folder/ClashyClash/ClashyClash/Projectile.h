#pragma once
#include "raylib.h"
#include <iostream>
#include "raymath.h"

class Projectile
{
public:
	Projectile() = default;
	~Projectile();
	void Update(float dt);
	void Init(Vector2 position, float rotation);

	bool active = true;
	bool hitObj = false; //TODO: implement collision width objects

	Rectangle getCollisionRec() { return hitBox; }

	void Destroy();

private:

	float damage = 10;
	float speed = 900;
	float lifeTime = 0;
	float maxLifeTime = 7;
	float rotation{};
	float coolDown = 0;

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

