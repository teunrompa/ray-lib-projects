#include "Game.h"

void Game::InitGame() 
{
	InitWindow(screenSize.x, screenSize.y, "Top down game");

	InitAudioDevice();

	enemy_die		= LoadSound("audio/hit_sound.wav");
	player_hit		= LoadSound("audio/player_hit.wav");
	projectile_fire = LoadSound("audio/projectile_fire.wav");
	enemy_freeze	= LoadSound("audio/enemy_freeze.wav");

	SetSoundVolume(enemy_die, 0.2f);
	SetSoundVolume(player_hit, 0.2f);
	SetSoundVolume(projectile_fire, 0.2f);
	SetSoundVolume(enemy_freeze, 0.2f);

	textureManager.init();
	
	map = textureManager.getMap(); //load the map texture
	worldSize = Vector2{static_cast<float>(map.width) * mapScale, static_cast<float>(map.height) * mapScale}; //make the world size based on the map texture
	worldBounds = {0,0, worldSize.x, worldSize.y};

	//Init all the objects here...
	player.Init(camera, Vector2{ worldSize.x / 2, worldSize.y / 2 }, textureManager.getPlayer());
	cameraTargetOffset = player.texture.width / player.maxAnimationFrames;

	attack.Init(player.getPos(), 0.5f, 45, LoadTexture("sprites/swing_animation.png"));

	//Wave handler made a copy because it wants to be initialized
	WaveHandler wave_handler{3, 5, &enemies, textureManager.getTextureEnemy(), textureManager.getEnemyFrozen()};
	waveHandler = wave_handler;
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

void Game::ResetGame()
{
	player.ResetValues(Vector2{ worldSize.x / 2, worldSize.y / 2 });

	//Reset the enemy count
	std::vector<Enemy> emptyEnemies;
	enemies = emptyEnemies;
	score = 0;
	highScoreSaved = false;
}

void Game::SaveHighScore()
{
	std::ifstream file;
	file.open("high_scores.txt");
	file >> highScore;
	file.close();

	//if score is greater than high score write score to file
	if(highScore < score)
	{
		std::ofstream file;
		file.open("high_scores.txt");
		file << score;
	}
}

float Game::getHighScore()
{
	std::ifstream file;
	file.open("high_scores.txt");
	file >> highScore;
	file.close();
	return highScore;
}

//Write your Game Code here...
void Game::UpdateGame()
{
	DrawGame();

	ClearGameScreen();

	if (!gameHasStarted)
	{
		DrawText("Press space to start the game", camera.target.x - 300, camera.target.y, 40, BLACK);
		DrawText("Controls:\nW A S D = move,\nleft mouse = shoot,\nright mouse = melee", camera.target.x - 300, camera.target.y - 150, 15, GRAY);
		DrawText("Freeze enemies width your projectile,\nthen destoy them while they are frozen width your mellee attack", camera.target.x - 300, camera.target.y - 50, 15, GRAY);

		if (IsKeyPressed(KEY_SPACE))
		{
			gameHasStarted = true;
		}
		return;
	}

	DrawMap();

	//strings need to be defined here because the Text needs to be reset each time
	std::string healthString{ "Health: " };
	healthString.append(std::to_string(player.getCurrentHealth()), 0, 5);

	std::string scoreString{ "Score: " };
	scoreString.append(std::to_string(score), 0, 5);

	gameTime += GetFrameTime();

	player.Update(GetFrameTime());

	waveHandler.Update(GetFrameTime(), worldSize);

	//check if the player is within the map
	if (player.position.x < screenSize.x / 2 ||
		player.position.y < screenSize.y / 2 ||
		player.position.x + screenSize.x / 2 > worldSize.x - 50 ||
		player.position.y + screenSize.y / 2 > worldSize.y - 50)
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
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemies[i].setTarget(&player);
		enemies[i].Update(GetFrameTime());

		if (!enemies[i].getAlive())
		{
			enemies.erase(enemies.begin() + i);
		}
	}

	coolDown += GetFrameTime();

	//add a projectile to the projectiles vector
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && fireRate < coolDown && player.getAlive())
	{
		Projectile projectile;

		projectile.Init(player.getPos(), player.getRotation(), textureManager.getProjectile());

		projectiles.push_back(projectile);

		PlaySoundMulti(projectile_fire);

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
					if (CheckCollisionRecs(enemy.getCollisionRec(), projectiles[i].getCollisionRec()))
					{
						PlaySoundMulti(enemy_freeze);
					}

					projectiles[i].checkCollisionWith(&enemy); //TODO fix collision check	
				}
			}

			//Remove the projectile if not active
			if (!projectiles[i].active)
			{
				projectiles.erase(projectiles.begin() + i);
			}
		}
	}

	if (!enemies.empty())
	{
		for (auto& enemy : enemies)
		{
			//Enemy dies
			if (enemy.getFrozen() && attack.getIsAttacking() && CheckCollisionCircleRec(attack.getPos(), attack.getRadius(), enemy.getCollisionRec()))
			{
				enemy.setAlive(false);
				PlaySoundMulti(enemy_die);
				score += 10;
			}
			//Check collision between enemy and player
			if (!enemy.getFrozen() && CheckCollisionRecs(enemy.getCollisionRec(), player.getCollisionRec()))
			{
				//Check if the player is ready to take damage again
				if (player.getDamageCooldown() > player.getDamageCooldownMax() && player.getAlive())
				{
					player.TakeDamage(25);
					PlaySoundMulti(player_hit);
				}
			}
		}
	}

	if(player.getAlive())
	{
		attack.Update(player.getPos(), GetFrameTime(), player.getRotation());
		//Draw health and score
		Vector2 health_text_pos{ player.getPos().x - screenSize.x / 2 + 50, player.getPos().y - screenSize.y / 2 + 100 };
		ShowMessage(healthString, health_text_pos, 20, BLACK);

		Vector2 score_text_pos{ player.getPos().x + screenSize.x / 2 - 100, player.getPos().y - screenSize.y / 2 + 100 };
		ShowMessage(scoreString, score_text_pos, 20, BLACK);
	}

	

	if (!player.getAlive())
	{
		if(!highScoreSaved)
		{
			SaveHighScore();
			highScoreSaved = true;
		}

		std::string highScoreText{ "high score: " };
		highScoreText.append(std::to_string(getHighScore()), 0, 5);

		Vector2 high_score_text_pos{ player.getPos().x - 40, player.getPos().y + 200 };
		ShowMessage(highScoreText, high_score_text_pos, 20, BLACK);

		Vector2 score_text_pos_right{ player.getPos().x - 40, player.getPos().y + 100 };
		ShowMessage(scoreString, score_text_pos_right, 20, BLACK);

		Vector2 game_over_text_pos{ player.getPos().x - 350, player.getPos().y - 100 };
		ShowMessage("Game Over! Press space to restart or esc to quit", game_over_text_pos, 30, BLACK);

		if (IsKeyPressed(KEY_SPACE))
		{
			ResetGame();

		}
	}

	KeepCameraInWorld();
}

void Game::GameShouldStop()
{
	SaveHighScore();
	UnloadTexture(map);
	UnloadSound(player_hit);
	UnloadSound(projectile_fire);
	UnloadSound(enemy_die);
	UnloadSound(enemy_freeze);
	StopSoundMulti();
	CloseWindow();
}

void Game::ShowMessage(const std::string msg, const Vector2 pos, const float font_size, const Color text_color)
{
	DrawText(msg.c_str(), pos.x, pos.y, font_size, text_color);
}
