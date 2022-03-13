#pragma once
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include <raylib.h>

class BaseCharacter
{
public:

	Vector2 position{0,0};
	Vector2 worldPosLastFrame{};

	Texture2D texture{};
	Texture2D textureIdle{};

	virtual void Update(float dt);
	void unsetMovement();
	void ResetAnimationData(const Texture2D* new_texture,  int maxFrames, const float updateTime);

	virtual Rectangle getCollisionRec();
	Vector2 getPos() { return position; }
	bool getAlive() { return isAlive; }
	void setAlive(const bool alive) { isAlive = alive; }

	int maxAnimationFrames{ 4 };

	float getRotation() { return rotation; }
protected:

	//Animation
	int currentAnimationFrame{ 0 };
	float scale{ 3 };
	float width{0};
	float height{0};
	float runningTime{0};
	float rotation{ 0 };
	float updateTime{0.3};
	float speed{500};

	Color color{ 255, 255, 255, 255 };
	Color damagedColor{ 230, 41, 55, 255 };

private:
	bool isAlive{ true };
};

#endif
