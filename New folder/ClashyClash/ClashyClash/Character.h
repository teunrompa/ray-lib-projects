#pragma once
#include <raylib.h>
#include "raymath.h"
#include <iostream>
#include <vector>

#include "BaseCharacter.h"
#include "Projectile.h"

class Character : public BaseCharacter
{
public:
	Vector2 moveVel{ 0, 0 }; // the direction where the player is going
	Vector2 mousePos = GetMousePosition();

	void Init(Camera2D& camera, Vector2 position);
	void Update(float deltaTime) override; //updates the player logic

	//Check if the player has reached the edge of the map
	bool isPlayerInMap = true;
	bool isColliding = false;

	void Move();
	void UndoMovement(); // reset the player to the last position he was at
	std::vector <Projectile> getProjectiles(){return projectiles;}
	Vector2 lastPos{};
private:

	std::vector<Projectile>	projectiles;

	void LookAtMouse(const Camera2D* camera);

	float dt{ 0 };

	//Fire logic
	void Fire();
	float coolDown{0};
	float fireRate{ 0.3f };

	Camera2D* gameCam;
};

