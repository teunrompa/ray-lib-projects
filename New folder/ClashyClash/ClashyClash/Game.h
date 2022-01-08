#pragma once
#include "Player.h"
#include "raylib.h"

class Game
{
public:

	Vector2 screenSize{ 600, 600 };
	Vector2 worldSize;

	void InitGame();
	void UpdateGame();
	void GameShouldStop();

	//Public objects
	Player player;
	Vector2 cameraOffset{screenSize.x / 2, screenSize.y / 2};
	Camera2D camera{cameraOffset, player.position , 0, 1};


private:

	//Game rendering methods
	void DrawGame();
	void ClearGameScreen();
	void EndDrawingGame();
	void DrawMap();

	//Game values
	Texture2D map;
	float mapScale = 4;
	float cameraTargetOffset;

};

