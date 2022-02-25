#pragma once
#include <raylib.h>
#include "raymath.h"
#include <iostream>
#include <vector>
#include "Projectile.h"

class Player
{
public:
	std::vector<Projectile>	projectiles;

	Vector2 position{ 0, 0 };
	Vector2 moveVel{0, 0}; // the direction where the player is going
	Vector2 mousePos = GetMousePosition();

	void Init();
	void UpdatePlayer(Camera2D camera); //updates all the players code

	//Check if the player has reached the edge of the map
	bool isPlayerInMap = true;
	Texture2D playerTexture;

private:
	Rectangle sourceRec;
	Rectangle playerDest;
	Vector2 origin;

	void Draw();
	void Update(Camera2D camera); //updates the player logic
	void LookAtMouse(Camera2D camera);
	void MovePlayer();

	float dt{ 0 };

	//Player info
	float scale {3};
	float rotation{90};
	float speed{500};

	//Fire logic
	void Fire(float fireRate);
	float coolDown = 0;
};

