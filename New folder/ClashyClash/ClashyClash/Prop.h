#pragma once
#include <raylib.h>

class Prop
{
public:
	Prop(Vector2 pos, Texture2D texture);
	void Render();
	Rectangle getCollisionRec();

private:
	Texture2D texture{};
	Vector2 worldPos{};
	float scale{ 4.f };
};

