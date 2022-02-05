#include "Game.h"

void Game::InitGame() 
{
	InitWindow( screenSize.x, screenSize.y, "Top down game");
	
	map = LoadTexture("nature_tileset/OpenWorldMap24x24.png"); //load the map texture
	worldSize = Vector2{static_cast<float>(map.width) * mapScale, static_cast<float>(map.height) * mapScale}; //make the world size based on the map texture

	//Init all the objects here...
	player.Init();
	player.position = Vector2{screenSize.x / 2, screenSize.y / 2};
	cameraTargetOffset = player.playerTexture.width;
}

void Game::DrawGame()
{
	BeginDrawing();
	BeginMode2D(camera);
}

void Game::ClearGameScreen()
{
	ClearBackground(WHITE);
}

void Game::EndDrawingGame()
{
	EndDrawing();
	EndMode2D();
}

void Game::DrawMap()
{
	Vector2 mapPos{ 0, 0 };
	DrawTextureEx(map, mapPos, 0, mapScale, WHITE);
}

void Game::CheckIfPlayerIsInWorld()
{
	if (player.position.x > worldSize.x)
	{
		camera.target = Vector2{ worldSize.x + cameraTargetOffset, player.position.y + cameraTargetOffset };
	}
	else if (player.position.x < 0)
	{
		camera.target = Vector2{ 0 + cameraTargetOffset , player.position.y + cameraTargetOffset };
	}
	else if (player.position.y < 0)
	{
		camera.target = Vector2{ player.position.x + cameraTargetOffset, 0 + cameraTargetOffset };
	}
	else if (player.position.y > worldSize.y)
	{
		camera.target = Vector2{ player.position.x + cameraTargetOffset, worldSize.y + cameraTargetOffset };
	}
	else
	{
		camera.target = Vector2{ player.position.x + cameraTargetOffset, player.position.y + cameraTargetOffset };
	}
}

//Write your Game Code here...
void Game::UpdateGame()
{
	DrawGame();

	ClearGameScreen();

	DrawMap();

	player.UpdatePlayer(camera);
	
	CheckIfPlayerIsInWorld();

	EndDrawingGame();
}

void Game::GameShouldStop()
{
	UnloadTexture(map);
	CloseWindow();
}
