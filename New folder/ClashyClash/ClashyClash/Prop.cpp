#include "Prop.h"



void Prop::Init(Vector2 pos, Texture2D texture)
{
	this->worldPos = pos;
	this->texture = texture;
}

void Prop::Render()
{
	DrawTextureEx(texture, worldPos, 0, scale, RAYWHITE);
}

