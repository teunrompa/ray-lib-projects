#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D texture_idle, Texture2D texture_frozen)
{
	maxAnimationFrames = 4;

	texture = texture_idle;
	this->enemyFrozen = texture_frozen;

	this->position = pos;
	this->textureIdle = texture_idle;
	this->width = texture_idle.width / maxAnimationFrames;
	this->height = texture_idle.height;
	speed = 300;
}

void Enemy::Update(const float dt, Color color)
{
	if(!getAlive()) return;

	if(!frozen)
	{
		texture = textureIdle;
		//Update enemies target and velocity
		velocity = Vector2Subtract(target->getPos(), position);
		//normalize returns NaN when velocity = 0 
		if (Vector2Length(velocity) > 0)
			velocity = Vector2Normalize(velocity);

		velocity = Vector2Scale(velocity, speed * dt);
		position = Vector2Add(position, velocity);

		isAnimationReset = false;
	}else
	{
		Freeze();
	}
	BaseCharacter::Update(dt, WHITE);
}

void Enemy::setTarget(Character* target)
{
	this->target = target;
}

void Enemy::setFrozen(const bool frozen)
{
	this->frozen = frozen;
}


void Enemy::Freeze()
{
	//reset all animation data
	if(!isAnimationReset)
	{
		isAnimationReset = true;
		ResetAnimationData(&enemyFrozen, 5, 1);
	}
	if (maxAnimationFrames <= currentAnimationFrame)
	{
		frozen = false;
	}
}

Rectangle Enemy::getCollisionRec()
{
	float modifier = 0.7f;
	return Rectangle{
		position.x - width * scale / 2 * modifier,
		position.y - height * scale / 2 ,
		width * scale * modifier ,
		height * scale
	};
}


