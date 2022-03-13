#pragma once
#include "Character.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include "Prop.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Attack.h"
#include "WaveHandler.h"
#include "TextureManager.h"
#include <string>

class Game
{
public:
	Vector2 screenSize{ 1000, 800 };
	Vector2 worldSize{}; //This accounts for scale

	void InitGame();
	void UpdateGame();
	void GameShouldStop();
	void ShowMessage(std::string msg, Vector2 pos, float font_size, Color text_color);
	void EndDrawingGame();

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
	void DrawMap();
	void KeepCameraInWorld();
	void ResetGame();

	bool gameHasStarted{ false };

	//Game values
	Texture2D map{};
	float mapScale = 6;
	float cameraTargetOffset{};

	//Objects
	std::vector<Prop> props;
	std::vector<Enemy> enemies;
	std::vector<Projectile>	projectiles;

	Attack attack{};
	TextureManager textureManager;
	WaveHandler waveHandler{1,2, &enemies, textureManager.getTextureEnemy(), textureManager.getEnemyFrozen()};

	//Fire logic
	float coolDown{ 0 };
	float fireRate{ 0.3f };

	float score{ 0 };
};

