#include "Projectile.h"

void Projectile::Init(Vector2 position, float rotation)
{
	projectileTexture = LoadTexture("sprites/snow_ball.png");

	this->position = position;
	this->rotation = rotation;
	this->rotation -= 90;

	direction = Vector2Rotate(direction, this->rotation);
	hitBox.width = projectileTexture.width;
	hitBox.height = projectileTexture.height;

	source = {0,0, static_cast<float>(projectileTexture.width), static_cast<float>(projectileTexture.height)};
	destRec = {this->position.x, this->position.y, static_cast<float>(projectileTexture.width), static_cast<float>(projectileTexture.height)};
	origin = {static_cast<float>(projectileTexture.height) / 2,static_cast<float>(projectileTexture.height) / 2};
}

void Projectile::UpdatePosition(float dt)
{
	velocity  = Vector2Add(velocity, direction);
	velocity = Vector2Normalize(velocity);

	velocity.x *= speed * dt;
	velocity.y *= speed * dt;

	position = Vector2Add(position, velocity);
	hitBox.x = position.x;
	hitBox.y = position.y;

	destRec.x = position.x;
	destRec.y = position.y;
}

void Projectile::Destroy()
{
	UnloadTexture(projectileTexture);
}

void Projectile::Update(float dt)
{
	if (lifeTime >= maxLifeTime) {
		active = false;
	}

	lifeTime += dt;

	if(active)
	{
		Draw();
		UpdatePosition(dt);
	}else
	{
		Destroy();
	}
}


void Projectile::Draw()
{
	DrawTexturePro(projectileTexture, source, destRec, origin, rotation, RAYWHITE);
	DrawRectangleRec(hitBox, RED);
}
