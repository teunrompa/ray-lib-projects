#include "Character.h"

void Character::Init(Camera2D& camera, Vector2 position)
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
	if (!getAlive()) return;

	BaseCharacter::Update(deltaTime);

	dt = deltaTime;

	Move();

	LookAtMouse(gameCam);

	mousePos = GetMousePosition();
}

Rectangle Character::getCollisionRec()
{
	float modifier = 0.5f;
	return Rectangle{
		position.x - width * scale / 2 * modifier,
		position.y - height * scale / 2 * modifier,
		width* scale * modifier,
		height* scale * modifier
	};
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





