#include "Character.h"

void Character::Init(Camera2D &camera, Vector2 position)
{
	texture = LoadTexture("sprites/player_topdown_sheett.png");
	gameCam = &camera;
	this->position = position;

	width = texture.width / maxAnimationFrames;
	height = texture.height;

	speed = 500;
}


void Character::Update(const float deltaTime)
{
	BaseCharacter::Update(deltaTime);

	dt = deltaTime;

	Move();

	LookAtMouse(gameCam);

	Fire();

	mousePos = GetMousePosition();
}

void Character::LookAtMouse(const Camera2D* camera)
{
	rotation = Vector2Angle(position, GetScreenToWorld2D(mousePos, *camera));
}

void Character::Move()
{
	lastPos = position;

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

void Character::UndoMovement()
{
	position = lastPos;
}

void Character::Fire()
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



