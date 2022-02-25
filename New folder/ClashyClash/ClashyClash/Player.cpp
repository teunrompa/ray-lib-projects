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

	Fire(0.2f);

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
	}

	moveVel.x = 0;
	moveVel.y = 0;
}

void Player::Fire(float fireRate)
{
	coolDown += dt;
	
	//add a projectile to the projectiles vector
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && fireRate < coolDown)
	{
		Projectile projectile;

		projectile.Init(position, rotation);

		projectiles.push_back(projectile);

		coolDown = 0;
	}

	//loop trough the projectiles and update them
	for (int i = projectiles.size() - 1; i >= 0; i--)
	{
		projectiles[i].Update(dt);

		if(!projectiles[i].active)
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}
}

void Player::UpdatePlayer(Camera2D camera) 
{
	Draw();
	Update(camera);
}


