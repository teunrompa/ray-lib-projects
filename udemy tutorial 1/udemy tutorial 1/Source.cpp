#include <cstdio>
#include "raylib.h"


int main(int argc, char* argv[])
{

	constexpr int width = 350;
	constexpr int height = width * 2;

	Vector2 player_pos = { static_cast<float>(width) / 2, static_cast<float>(height) / 2 };
	Vector2 axe_pos = { static_cast<float>(GetRandomValue(0, width)), 0.f };

	InitWindow(width, height, "Test");

	SetTargetFPS(60);
	constexpr float speed = 5;
	while (!WindowShouldClose())
	{

		ClearBackground(WHITE);

		BeginDrawing();

		DrawRectangle(static_cast<int>(axe_pos.x), static_cast<int>(axe_pos.y), 50, 50, BLUE);

		DrawCircle(static_cast<int>(player_pos.x), static_cast<int>(player_pos.y), 25, RED);

		axe_pos.y += 1;

		if (IsKeyDown(KEY_D) && player_pos.x < width)
		{
			player_pos.x += speed;
		}
		if (IsKeyDown(KEY_A) && player_pos.x > 0)
		{
			player_pos.x -= speed;
		}
		if (IsKeyDown(KEY_W) && player_pos.y > 0)
		{
			player_pos.y -= speed;
		}
		if (IsKeyDown(KEY_S) && player_pos.y < height)
		{
			player_pos.y += speed;
		}
		EndDrawing();
	}
}
