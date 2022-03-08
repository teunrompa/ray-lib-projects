#include "Game.h"

#include <functional>

void Game::InitGame() 
{
	InitWindow(screenSize.x, screenSize.y, "Top down game");

	map = LoadTexture("nature_tileset/OpenWorldMap24x24.png"); //load the map texture
	worldSize = Vector2{static_cast<float>(map.width) * mapScale, static_cast<float>(map.height) * mapScale}; //make the world size based on the map texture
	worldBounds = {0,0, worldSize.x, worldSize.y};

	//Init all the objects here...
	player.Init(camera, Vector2{ screenSize.x / 2, screenSize.y / 2 });
	cameraTargetOffset = player.texture.width / player.maxAnimationFrames;

	//Game props
	props.emplace_back(Vector2{200, 200}, LoadTexture("nature_tileset/Rock.png"));
	props.emplace_back(Vector2{200, 500}, LoadTexture("nature_tileset/Bush.png"));

	//Enemies just for testing
	enemies.emplace_back(Vector2{ 300, 400 }, LoadTexture("sprites/flame_character_sheet.png"), LoadTexture("sprites/flame_character_sheet.png"));

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
	DrawTextureEx(map, Vector2{ 0, 0 }, 0, mapScale, WHITE);
}

void Game::KeepCameraInWorld()
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

	gameTime += GetFrameTime();

	player.Update(GetFrameTime());

	//check if the player is within the map
	if( player.position.x < 0 ||
		player.position.y < 0 || 
		player.position.x + screenSize.x > worldSize.x ||
		player.position.y + screenSize.y > worldSize.y)
	{
		player.UndoMovement();
	}


	//Loop trough props
	for (auto prop : props)
	{
		prop.Render();
		//Is player colliding width props?
		if (CheckCollisionRecs(prop.getCollisionRec(), player.getCollisionRec()))
		{
			player.UndoMovement();
		}

		DrawRectangleRec(prop.getCollisionRec(), YELLOW);
	}

	for (auto& enemy : enemies)
	{
		enemy.setTarget(&player);
		enemy.Update(GetFrameTime());
	}

	coolDown += GetFrameTime();

	//add a projectile to the projectiles vector
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && fireRate < coolDown)
	{
		Projectile projectile;

		projectile.Init(player.position, player.getRotation());

		projectiles.push_back(projectile);

		coolDown = 0;
	}

	//Loop trough the projectiles and update them

	if (!projectiles.empty())
	{
		for (int i = projectiles.size() - 1; i >= 0; i--)
		{
			//Update the active projectile
			if (projectiles[i].active)
				projectiles[i].Update(GetFrameTime());

			//Check for collision width enemy
			if (!enemies.empty() && !projectiles.empty())
			{
				for (auto& enemy : enemies)
				{
					projectiles[i].checkCollisionWith(&enemy);
					
				}
			}
			//Remove the projectile if not active
			if (!projectiles[i].active)
			{
				projectiles.erase(projectiles.begin() + i);
			}
		}
	}


	KeepCameraInWorld();

	EndDrawingGame();
}

void Game::GameShouldStop()
{
	UnloadTexture(map);
	CloseWindow();
}
