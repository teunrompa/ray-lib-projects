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

//Write your Game Code here...
void Game::UpdateGame()
{
	DrawGame();

	ClearGameScreen();

	DrawMap();

	player.UpdatePlayer();

	//check if the player is at the edge of the screen
	if (camera.target.x <= worldSize.x)
	{
		camera.target = Vector2{ player.position.x + cameraTargetOffset, player.position.y + cameraTargetOffset};
	}


	EndDrawingGame();
}

void Game::GameShouldStop()
{
	UnloadTexture(map);
	CloseWindow();
}
