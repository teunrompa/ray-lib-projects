#include "Attack.h"

void Attack::Init(Vector2 position, float cooldown, float radius, Texture2D texture)
{
	this->position = position;
	this->cooldown = cooldown;
	this->duration = duration;
	this->radius = radius;
	this->texture = texture;
	width = texture.width / maxAnimationFrames;
	height = texture.height;
}

void Attack::Update(Vector2 attackPos, const float dt, const float rotation)
{
	this->position = attackPos;

	lookingDir = Vector2Rotate(lookingDir, rotation - 90);
	lookingDir = Vector2Scale(lookingDir, offset);
	position = Vector2Add(position, lookingDir);
	cooldownTime += dt;

	//Check if the cooldown has been reached or if the player is already attacking
	if(cooldownTime > cooldown)
	{
		if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) || attacking)
		{
			DoAttack(position, rotation);
			lifeTime += dt;
		}
	}

	lookingDir = { 0, 1 };
}

/*
 * Draws the attack and checks for collisions
 */
void Attack::DoAttack(Vector2 pos, const float rotation)
{
	Rectangle source = {currentAnimationFrame * width, 0, width, height };
	Rectangle dest = { pos.x , pos.y , width * scale, height * scale};
	Vector2 origin = {width - 10, height };

	DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

	attacking = true;

	runningTime += GetFrameTime();

	if (runningTime >= updateTime)
	{
		currentAnimationFrame++;
		runningTime = 0.f;
		if (currentAnimationFrame >= maxAnimationFrames)
		{
			//Attack has finished reset the values
			attacking = false;
			currentAnimationFrame = 0;
			cooldownTime = 0;
		}
	}
}
