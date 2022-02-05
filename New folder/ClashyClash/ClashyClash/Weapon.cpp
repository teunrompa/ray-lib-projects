#include "Weapon.h"

void Weapon::initWeapon()
{
	projectileTexture = LoadTexture("snow_ball");
}

void Weapon::Fire(Vector2 spawnPosition)
{
	DrawTextureEx(projectileTexture, spawnPosition, 0, 20, WHITE);
}

/*
 * Updates the projectile's velocity
 */
void Weapon::UpdateProjectile()
{
	position = Vector2Add(position, velocity);
}
