#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <raylib.h>
#include "raymath.h"
#include <iostream>
#include <vector>

#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
	Vector2 moveVel{ 0, 0 }; // the direction where the player is going
	Vector2 mousePos = GetMousePosition();

	void Init(Camera2D& camera, Vector2 position, Texture2D texture);
	void Update(float deltaTime) override; //updates the player logic

	//Check if the player has reached the edge of the map
	bool isPlayerInMap = true;
	bool isColliding = false;

	void Move();
	void UndoMovement(); // reset the player to the last position he was at
	void TakeDamage(const float damage);

	float getDamageCooldown() { return damageCooldownCount; }
	float getDamageCooldownMax() { return damageCooldownMax; }
	float getCurrentHealth() { return currentHealth; }

	Vector2 lastPos{};
	Rectangle getCollisionRec() override;
private:

	float healthMax{ 100 };
	float currentHealth{ healthMax };
	float damageCooldownMax{1.5f};
	float damageCooldownCount{ 0 };

	void LookAtMouse(const Camera2D* camera);

	float dt{ 0 };

	Camera2D* gameCam;

	
};

#endif

