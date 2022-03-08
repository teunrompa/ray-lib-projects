#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
= default;

void BaseCharacter::Update(float dt)
{
	worldPosLastFrame = position;

	//Updates the animation
	runningTime += dt;
	if (runningTime >= updateTime)
	{
		currentAnimationFrame++;
		runningTime = 0.f;
		if (currentAnimationFrame > maxAnimationFrames)
			currentAnimationFrame = 0;
	}

	Rectangle source{ currentAnimationFrame * width, 0.f, width, height };
	Rectangle dest{ position.x, position.y, scale * width, scale * height };
	Vector2 origin{ width  / 2 * scale,  height / 2 * scale};
	DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}

void BaseCharacter::unsetMovement()
{
	position = worldPosLastFrame;
}

void BaseCharacter::ResetAnimationData(const Texture2D* new_texture, const int maxFrames, const float updateTime)
{
	currentAnimationFrame = 0;
	maxAnimationFrames = maxFrames;
	this->updateTime = updateTime;
	runningTime = 0;
	this->width = new_texture->width / maxAnimationFrames;
	texture = *new_texture;
}

Rectangle BaseCharacter::getCollisionRec()
{
	return Rectangle{
		position.x - width * scale / 2,
		position.y  - height * scale / 2,
		width  * scale ,
		height * scale
	};
}
