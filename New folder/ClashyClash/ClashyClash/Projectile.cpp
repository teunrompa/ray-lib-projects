#include "Projectile.h"

void Projectile::Init(const Vector2 position, const float rotation, const Texture2D texture)
{
	projectileTexture = texture;

	this->position = position;
	this->rotation = rotation;
	this->rotation -= 90; //Correct angle

	//Rotate vector to match rotation
	direction = Vector2Rotate(direction, this->rotation);

	hitBox.width = projectileTexture.width;
	hitBox.height = projectileTexture.height;

	source = {0,0, static_cast<float>(projectileTexture.width), static_cast<float>(projectileTexture.height)};
	destRec = {this->position.x, this->position.y, static_cast<float>(projectileTexture.width), static_cast<float>(projectileTexture.height)};
	origin = {static_cast<float>(projectileTexture.height) / 2,static_cast<float>(projectileTexture.height) / 2};
}

void Projectile::checkCollisionWith(Enemy* enemy)
{
	if(CheckCollisionRecs(enemy->getCollisionRec(), getCollisionRec()))
	{
		active = false;
		enemy->setFrozen(true);
	}
}

void Projectile::UpdatePosition(float dt)
{
	velocity  = Vector2Add(velocity, direction);
	velocity = Vector2Normalize(velocity);

	velocity = Vector2Scale(velocity, speed * dt);

	position = Vector2Add(position, velocity);

	hitBox.x = position.x - projectileTexture.width / 2;
	hitBox.y = position.y - projectileTexture.height / 2;

	destRec.x = position.x;
	destRec.y = position.y;
}

void Projectile::Update(const float dt)
{
	if (lifeTime >= maxLifeTime) {
		active = false;
	}

	lifeTime += dt;

	if(active)
	{
		Draw();
		UpdatePosition(dt);
	}
}

void Projectile::Draw()
{
	DrawTexturePro(projectileTexture, source, destRec, origin, rotation, RAYWHITE);
}
