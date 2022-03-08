#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D texture)
{
	this->worldPos = pos;
	this->texture = texture;
}

void Prop::Render()
{
	DrawTextureEx(texture, worldPos, 0, scale, RAYWHITE);
}

Rectangle Prop::getCollisionRec()
{
	return Rectangle{
		worldPos.x,
		worldPos.y,
		texture.width  * scale,
		texture.height * scale
	};
}

