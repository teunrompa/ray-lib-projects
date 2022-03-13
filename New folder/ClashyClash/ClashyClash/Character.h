#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <raylib.h>
#include "raymath.h"
#include <iostream>
#include <vector>

#include "BaseCharacter.h"
#include "Attack.h"

class Character : public BaseCharacter
{
public:
	Vector2 moveVel{ 0, 0 }; // the direction where the player is going
	Vector2 mousePos = GetMousePosition();

	void Init(Camera2D& camera, Vector2 position);
	void Update(float deltaTime) override; //updates the player logic

	//Check if the player has reached the edge of the map
	bool isPlayerInMap = true;
	bool isColliding = false;

	void Move();
	void UndoMovement(); // reset the player to the last position he was at

	Vector2 lastPos{};
	Rectangle getCollisionRec() override;

private:


	void LookAtMouse(const Camera2D* camera);

	float dt{ 0 };

	Camera2D* gameCam;
};

#endif

