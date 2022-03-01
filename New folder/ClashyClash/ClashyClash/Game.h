#pragma once
#include "Player.h"
#include "raylib.h"
#include <iostream>
#include <vector>

#include "Prop.h"


#define LOG(x) std::cout << (x) << std::endl;

class Game
{
public:

	Vector2 screenSize{ 1000, 800 };
	Vector2 worldSize;

	void InitGame();
	void UpdateGame();
	void GameShouldStop();

	//Public objects
	Vector2 cameraOffset{ screenSize.x / 2, screenSize.y / 2 };

	Camera2D camera{ cameraOffset, player.position , 0, 1 };

	Player player;
	Prop rock;
	Prop props[2];

	Rectangle worldBounds;

private:

	//Game rendering methods
	void DrawGame();
	void ClearGameScreen();
	void EndDrawingGame();
	void DrawMap();
	void CheckIfPlayerIsInWorld();


	//Game values
	Texture2D map;
	float mapScale = 4;
	float cameraTargetOffset;

};

