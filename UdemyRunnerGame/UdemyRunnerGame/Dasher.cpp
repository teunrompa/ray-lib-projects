#include <iostream>
#include "raylib.h"

struct AnimData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};


int main(int argc, char* argv[])
{

	int window_width{ 800 };
	int window_height{ 500 };

	InitWindow(window_width, window_height, "game");

	constexpr float gravity{ 70 };

	//nebula variables
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	Rectangle nebulaRec{0,0, nebula.width / 8, nebula.height / 8};
	Vector2 nebulaPos{ window_width  , window_height - nebulaRec.height};
	Vector2 nebulaVel{ -300, 0 };
	//animation
	int nebFrame{0};
	float nebRuningTime{ 0 };
	const float nebUpdateTime{ 1 / 12 };

	//player variables
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	
	AnimData scarfyData{ {scarfy.width / 6, scarfy.height, 0 , 0}, {window_width / 2 - scarfyData.rec.width / 2,window_height - scarfyData.rec.height } };
	scarfyData.frame = 0;
	scarfyData.updateTime = 1.0 / 12.0;
	scarfyData.runningTime = 0.0;


	
	Rectangle scarfyRec{0, 0, scarfy.width / 6, scarfy.height}; //divide width by 6 because there are 6 images on our spriteSheet
	Vector2 scarfyPos{ window_width / 2, window_height - scarfyRec.height };
	Vector2 velocity{ 0, 0 };
	float jump_velocity{ -1600 };
	bool is_airborne{ false };

	//animation
	int frame{};
	constexpr float updateTime{ 1.0f / 12.0f};
	float runningTime{};

	float gameFrameRate{ 60 };
	SetTargetFPS(gameFrameRate);

	while (!WindowShouldClose())
	{
		//get the delta time
		float dt{ GetFrameTime() };

		if (scarfyPos.y >= window_height - scarfyRec.height)
		{
			velocity.y = 0;
			is_airborne = false;
		}
		else
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

		nebulaPos.x += nebulaVel.x * dt;



		//freeze animation frame when in air
		if (!is_airborne) {
			//update running time
			runningTime += dt;

			if (runningTime >= updateTime)
			{
				runningTime = 0;

				//updates the animation frame
				scarfyRec.x = frame * scarfyRec.width;

				//increment the frame
				frame++;

				//reset the frame 
				if (frame > 5)
				{
					frame = 0;
				}
			}
		}


		nebRuningTime += dt;

		if (nebRuningTime >= nebUpdateTime) {
			nebulaRec.x = nebFrame * nebulaRec.width;

			nebFrame++;

			if (nebFrame > 7) {
				nebFrame = 0;
			}
		}

		DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
		DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
		EndDrawing();
	}
	UnloadTexture(nebula);
	UnloadTexture(scarfy);
	CloseWindow();


}
