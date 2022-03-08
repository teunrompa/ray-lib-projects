#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D texture_idle, Texture2D texture_move)
{
	maxAnimationFrames = 4;

	texture = texture_idle;

	this->position = pos;
	this->textureIdle = texture_idle;
	this->textureMove = texture_move;
	this->width = texture_idle.width / maxAnimationFrames;
	this->height = texture_idle.height;
	speed = 300;
}

void Enemy::Update(const float dt)
{
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
	}else
	{
		Freeze();
	}
	BaseCharacter::Update(dt);
}

void Enemy::setTarget(Character* target)
{
	this->target = target;
}

void Enemy::Freeze()
{
	//reset all animation data
	if(!isAnimationReset)
	{
		isAnimationReset = true;
		resetAnimationFrames();
	}

	texture = enemyFrozen;
	maxAnimationFrames = 5;
	width = enemyFrozen.width / maxAnimationFrames;
	updateTime = 1;
	if (maxAnimationFrames == currentAnimationFrame)
	{
		frozen = false;
	}
}

