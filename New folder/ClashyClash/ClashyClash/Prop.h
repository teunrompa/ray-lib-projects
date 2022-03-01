#pragma once
#include <raylib.h>

class Prop
{
public:

	void Render();
	void Init(Vector2 pos, Texture2D texture);

private:
	Texture2D texture{};
	Vector2 worldPos{};
	float scale{ 4.f };
};

