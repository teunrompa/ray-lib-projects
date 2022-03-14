#include "WaveHandler.h"

WaveHandler::WaveHandler(const int enemyCountToSpawn, const float timeToNextSpawn, std::vector<Enemy>* enemies, const Texture2D enemyTexture, const Texture2D enemy_frozen)
{
	this->enemyCountToSpawn = enemyCountToSpawn;
	this->timeToNextSpawn = timeToNextSpawn;
	this->enemies = enemies;
	this->enemyTexture = enemyTexture;
	this->enemyFrozen = enemy_frozen;
}

void WaveHandler::Update(const float dt, const Vector2 world_pos)
{
	waveTime += dt;

	if(enemies->empty())
	{
		for (int i = 0; i < enemyCountToSpawn; ++i)
		{
			Enemy enemy{ GenerateRandomPos(world_pos), enemyTexture, enemyFrozen };
			SpawnEnemy(enemy);
		}
		NextWave();
	}
}

void WaveHandler::SpawnEnemy(const Enemy& enemy)
{
	enemies->push_back(enemy);
	std::cout << "Enemy count: " << enemies->size() << "enemyPos:" << " x: " << enemy.position.x << " y: " << enemy.position.y << "\n";
}

void WaveHandler::NextWave()
{
	enemyCountToSpawn++;
	timeToNextSpawn++;
	waveTime = 0;
}

Vector2 WaveHandler::GenerateRandomPos(const Vector2 worldSize)
{
	int randomVal = GetRandomValue(0, 3);
	Vector2 spawnPosOutside;
	switch (randomVal)
	{
	case 0:
		//Spawn on random pos on the top of the world on the x axis
		spawnPosOutside = { static_cast<float>(GetRandomValue(0, worldSize.x)), 0 };
		break;
	case 1:
		//spawn on random pos on the left side of the world y axis
		spawnPosOutside = { 0, static_cast<float>(GetRandomValue(0, worldSize.y)) };
		break;
	case 2:
		//Spawn on random pos on the bottom of the world x axis
		spawnPosOutside = { static_cast<float>(GetRandomValue(0, worldSize.x)) , worldSize.y };
		break;
	case 3:
		//Spawn on random pos on the right side of the world on the y axis
		spawnPosOutside = { worldSize.x, static_cast<float>(GetRandomValue(0, worldSize.y)) };
		break;
	default:
		spawnPosOutside = { static_cast<float>(GetRandomValue(0, worldSize.x)), 0 };
	}
	return spawnPosOutside;
}
