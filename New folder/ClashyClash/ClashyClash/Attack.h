#pragma once
#include "raylib.h"
#include "raymath.h"

class Attack
{
public:
	void Init(Vector2 position, float cooldown, float radius, Texture2D texture);
	void Update(Vector2 attackPos, float dt, float rotation);

	Vector2 getPos() { return position; }
	float getRadius() { return radius; }
	bool getIsAttacking() { return attacking; }
private:

	void DoAttack(Vector2 pos, float rotation);

	float duration{};
	float cooldown{};
	float radius{};
	float lifeTime{ 0 };
	float cooldownTime{ 0 };
	bool attacking{ false };

	float offset{ 25 };

	//Animation
	float currentAnimationFrame{ 0 };
	float updateTime{ 0.03f };
	float maxAnimationFrames{ 9 };
	float width{};
	float height{0};
	float scale{2};
	float runningTime{0};

	Texture2D texture{};
	Vector2 position{};
	Vector2 lookingDir{0,1};
};

