#include "raylib.h"


int main(int argc, char* argv[])
{

	constexpr int width = 800;
	constexpr int height = 350;


	//axes coordinates
	Vector2 axe_pos = { static_cast<float>(GetRandomValue(0, width)), 0.f };
	float direction_axe = 3;
	constexpr int axe_size = 50;

	//axes coordinates
	int l_axe_x{ static_cast<int>(axe_pos.x) };
	int r_axe_x{ static_cast<int>(axe_pos.x) + axe_size };
	int u_axe_y{ static_cast<int>(axe_pos.y) };
	int b_axe_y{ static_cast<int>(axe_pos.y) + axe_size };


	//circle coordinates
	Vector2 circle_pos = { static_cast<float>(width) / 2, static_cast<float>(height) / 2 };
	constexpr int speed = 5;
	constexpr int circle_radius = 25;
	
	//circle edges
	float l_circle_x { circle_pos.x - circle_radius };
	float r_circle_x{ circle_pos.x + circle_radius };
	float u_circle_y { circle_pos.y - circle_radius };
	float b_circle_y { circle_pos.y + circle_radius };

	bool collision_width_axe = 
		(b_axe_y < u_circle_y) &&
		(u_axe_y <= b_circle_y) &&
		(r_axe_x <= r_circle_x) &&
		(l_axe_x >= l_circle_x);
		

	InitWindow(width, height, "Test");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		ClearBackground(WHITE);
		BeginDrawing();

		l_circle_x = circle_pos.x - circle_radius;
		r_circle_x = circle_pos.x + circle_radius;
		u_circle_y = circle_pos.y - circle_radius;
		b_circle_y = circle_pos.y + circle_radius;
		l_axe_x = axe_pos.x;
		r_axe_x = axe_pos.x + axe_size;
		u_axe_y = axe_pos.y;
		b_axe_y = axe_pos.y + axe_size;


	
		collision_width_axe = 
			(b_axe_y < u_circle_y) &&
			(u_axe_y <= b_circle_y) &&
			(r_axe_x <= r_circle_x) &&
			(l_axe_x >= l_circle_x);

		

		if( collision_width_axe)
		{
			DrawText("Game Over!", width / 2, height / 2, 20, RED);
		}else
		{
			DrawRectangle(static_cast<int>(axe_pos.x), static_cast<int>(axe_pos.y), axe_size, axe_size, BLUE);

			DrawCircle(static_cast<int>(circle_pos.x), static_cast<int>(circle_pos.y), circle_radius, RED);

			axe_pos.y += direction_axe;
			if (axe_pos.y > height || axe_pos.y < 0)
			{
				direction_axe = -direction_axe;
			}


			if (IsKeyDown(KEY_D) && circle_pos.x < width)
			{
				circle_pos.x += speed;
			}
			if (IsKeyDown(KEY_A) && circle_pos.x > 0)
			{
				circle_pos.x -= speed;
			}
			if (IsKeyDown(KEY_W) && circle_pos.y > 0)
			{
				circle_pos.y -= speed;
			}
			if (IsKeyDown(KEY_S) && circle_pos.y < height)
			{
				circle_pos.y += speed;
			}
		}

		EndDrawing();

	}
}
