#include <iostream>
#include "raylib.h"



int main(int argc, char* argv[])
{

	int window_width{ 800 };
	int window_height{ 500 };

	InitWindow(window_width, window_height, "game");


	//rectangle dimensions
	Vector2 velocity{ 0, 0 };

	constexpr float gravity{ 100 };
	float jump_velocity{ -1600 };

	bool is_airborne {false};

	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	Rectangle scarfyRec{0, 0, scarfy.width / 6, scarfy.height}; //divide width by 6 because there are 6 images on our spriteSheet
	Vector2 scarfyPos{ window_width / 2, window_height - scarfy.height };

	//animation
	int frame{ 0 };
	float updateTime{ 1/ 12};


	float gameFrameRate{ 60 };
	SetTargetFPS(gameFrameRate);

	while (!WindowShouldClose())
	{
		//get the delta time
		float dt{ GetFrameTime() };

		if(scarfyPos.y >= window_height - scarfyRec.height)
		{
			velocity.y = 0;
			is_airborne = false;
		}else
		{
			is_airborne = true;
			velocity.y += gravity;
		}


		if (IsKeyPressed(KEY_SPACE) && !is_airborne)
		{
			velocity.y += jump_velocity;
		}

		BeginDrawing();
		ClearBackground(WHITE);


		//apply velocity
		scarfyPos.y += velocity.y * dt;
		scarfyPos.x += velocity.x * dt;

		//animation
		scarfyRec.x = frame * scarfyRec.width;

		if(12 > animationFrameRate)
		{
			
		}

		frame++;

		if(frame > 5)
		{
			frame = 0;
		}


		DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
		EndDrawing();
	}

	UnloadTexture(scarfy);
	CloseWindow();


}
