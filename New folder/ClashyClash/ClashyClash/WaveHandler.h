#pragma once
#include "raylib.h"
#include "Enemy.h"
#include "vector"

class WaveHandler
{
public:
	WaveHandler(int enemyCountToSpawn, float timeToNextSpawn, std::vector<Enemy>* enemies, Texture2D enemyTexture, Texture2D enemy_frozen);

	void Update(float dt , Vector2 world_pos);
	void SpawnEnemy(const Enemy& enemy);
	void NextWave();
	Vector2 GenerateRandomPos(Vector2 worldSize);
	
private:
	int enemyCountToSpawn{};
	float timeToNextSpawn{};
	float waveTime{0};

	std::vector<Enemy>* enemies;
	Texture2D enemyTexture{};
	Texture2D enemyFrozen{};
};

