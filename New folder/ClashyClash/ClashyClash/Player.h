#pragma once
#include <raylib.h>
#include "raymath.h"


class Player
{
public:

	Vector2 position{ 0, 0 };
	Vector2 moveVel{0, 0}; // the direction where the player is going
	Vector2 mousePos = GetMousePosition();

	void Init();
	void UpdatePlayer(); //updates all the players code

	//Check if the player has reached the edge of the map
	bool isPlayerInMap = true;
	Texture2D playerTexture;


private:

	float dt{0};

	void Draw();
	void Update(); //updates the player logic

	void LookAtMouse();
	void MovePlayer();

	float scale {3};
	float rotation{0};
	float speed{500};
};

