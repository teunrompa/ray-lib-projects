#include "Player.h"

#include <iostream>

void Player::Init()
{
	playerTexture = LoadTexture("sprites/player.png");
}

void Player::Draw() 
{
	DrawTextureEx(playerTexture, position, rotation, scale, WHITE);
}

void Player::Update()
{
	dt = GetFrameTime();
	MovePlayer();
}

void Player::LookAtMouse()
{
	
}

void Player::MovePlayer()
{
	if (IsKeyDown(KEY_W)) moveVel.y -= 1;
	if (IsKeyDown(KEY_S)) moveVel.y += 1;
	if (IsKeyDown(KEY_A)) moveVel.x -= 1;
	if (IsKeyDown(KEY_D)) moveVel.x += 1;

	if(Vector2Length(moveVel) != 0.0f)
	{
		moveVel = Vector2Normalize(moveVel);
		moveVel.x *= speed * dt;
		moveVel.y *= speed * dt;
		position = Vector2Add(position, moveVel);
		std::cout << position.x << "" << position.y << std::endl;
	}

	moveVel.x = 0;
	moveVel.y = 0;
}

void Player::UpdatePlayer() 
{
	Draw();
	Update();
}


