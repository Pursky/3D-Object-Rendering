#include "HeightBox.h"

HeightBox::HeightBox(Player* player, XMFLOAT4 dimensions, float height, float rimSize, float rimHeight)
{
	this->player = player;
	this->dimensions = dimensions;
	this->height = height;
	this->rimSize = rimSize;
	this->rimHeight = rimHeight;
}

void HeightBox::Update(float deltaTime)
{
	float x = player->Position.x;
	float z = player->Position.z;

	if (x > dimensions.x && x < dimensions.y && z > dimensions.z && z < dimensions.w) player->FloorHeight = height;
	else 
	{
		if (rimSize == 0) return;
		if (x < dimensions.x - rimSize || x > dimensions.y + rimSize || z < dimensions.z - rimSize || z > dimensions.w + rimSize) return;

		// Interpolation of player height within the rim.
		XMFLOAT3 clamped = {Clamp(x, dimensions.x, dimensions.y), 0,  Clamp(z, dimensions.z, dimensions.w) };
		float distance = Length(Sub(clamped, {x, 0, z}));

		distance *= 1.0f / rimSize;
		if (distance > 1) distance = 1;

		player->FloorHeight = Lerp(height, rimHeight, distance);
	}
}