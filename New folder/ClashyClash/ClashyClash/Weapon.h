#pragma once
#include <raylib.h>
#include <raymath.h>

class Weapon
{
public:

	void initWeapon();
	void Fire(Vector2 spawnPosition);
	void UpdateProjectile();

private:

	Texture2D projectileTexture;
	Vector2 position;
	Vector2 velocity;

};
