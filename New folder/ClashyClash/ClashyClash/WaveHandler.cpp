#include "WaveHandler.h"

WaveHandler::WaveHandler(const int enemyCount, const float timeToNextSpawn, std::vector<Enemy>* enemies, const Texture2D enemyTexture, Texture2D enemy_frozen)
{
	this->enemyCount = enemyCount;
	this->timeToNextSpawn = timeToNextSpawn;
	this->enemies = enemies;
	this->enemyTexture = enemyTexture;
	this->enemyFrozen = enemy_frozen;
}

void WaveHandler::Update(const float dt, Vector2 spawnPos)
{
	//Todo: keep track off spawned enemies and check if new enemy's need to be spawned

	waveTime += dt;

	if(waveTime > timeToNextSpawn)
	{
		for (int i = 0; i < enemyCount; ++i)
		{
			Enemy enemy{ spawnPos, enemyTexture, enemyFrozen};
			SpawnEnemy(enemy);
			waveTime = 0;
		}
	}
}

void WaveHandler::SpawnEnemy(const Enemy& enemy)
{
	enemies->push_back(enemy);
}