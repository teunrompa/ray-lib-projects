#include "Player.h"


void Player::Init()
{
	playerTexture = LoadTexture("sprites/player.png");

	playerDest = { position.x, position.y, static_cast<float>(playerTexture.width) * scale, static_cast<float>(playerTexture.height) * scale };
	sourceRec = {0,0, static_cast<float>(playerTexture.width), static_cast<float>(playerTexture.height)};
	origin = {playerDest.height  / 2 , playerDest.width  /2};
}

void Player::Draw() 
{
	DrawTexturePro(playerTexture, sourceRec, playerDest, origin, rotation, WHITE);
}

void Player::Update(Camera2D camera)
{
	dt = GetFrameTime();
	MovePlayer();
	LookAtMouse(camera);


	mousePos = GetMousePosition();
	playerDest.x = position.x;
	playerDest.y = position.y;
}

void Player::LookAtMouse(Camera2D camera)
{
	
	rotation = Vector2Angle(position, GetScreenToWorld2D(mousePos, camera));
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
		//std::cout << position.x << "" << position.y << std::endl;
	}

	moveVel.x = 0;
	moveVel.y = 0;
}

void Player::UpdatePlayer(Camera2D camera) 
{
	Draw();
	Update(camera);
}


