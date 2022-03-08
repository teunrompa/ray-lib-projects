#pragma once
#include "Character.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include "Prop.h"
#include "Enemy.h"
#include "Projectile.h"

class Game
{
public:

	Vector2 screenSize{ 1000, 800 };
	Vector2 worldSize{}; //This accounts for scale

	void InitGame();
	void UpdateGame();
	void GameShouldStop();

	//Public objects
	Vector2 cameraOffset{ screenSize.x / 2, screenSize.y / 2 };

	Camera2D camera{ cameraOffset, player.position , 0, 1 };

	Character player{};

	Rectangle worldBounds{};

	float gameTime = GetFrameTime();

private:

	//Game rendering methods
	void DrawGame();
	void ClearGameScreen();
	void EndDrawingGame();
	void DrawMap();
	void KeepCameraInWorld();

	//Game values
	Texture2D map{};
	float mapScale = 4;
	float cameraTargetOffset{};

	//Objects
	std::vector<Prop> props;
	std::vector<Enemy> enemies;
	std::vector<Projectile>	projectiles;


	//Fire logic
	float coolDown{ 0 };
	float fireRate{ 0.3f };
};

