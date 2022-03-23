#include "Skybox.h"

void Skybox::Update(float deltaTime)
{
	Position = camera->Position;
	Rotation.y = dirLight->LightData.Rotation;

	UpdateMatrix();
}