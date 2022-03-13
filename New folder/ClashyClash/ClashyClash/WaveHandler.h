#pragma once
#include "raylib.h"
#include "Enemy.h"
#include "vector"

class WaveHandler
{
public:
	WaveHandler(int enemyCount, float timeToNextSpawn, std::vector<Enemy>* enemies);

	void Update(float dt , Vector2 spawnPos);
	void SpawnEnemy(const Enemy& enemy);
	
private:
	int enemyCount;
	float timeToNextSpawn;
	float waveTime{0};
	std::vector<Enemy>* enemies;
};

