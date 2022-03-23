#include "Player.h"

Player::Player(Camera* camera, Input* input, XMFLOAT3 position)
{
	this->input = input;
	this->camera = camera;
	
	float dotSpacing = 0.3f;
	float dotDistance = 0.4f;

	frontDots.push_back({-dotSpacing, 0,  dotDistance });
	frontDots.push_back({ 0, 0,  dotDistance });
	frontDots.push_back({ dotSpacing, 0,  dotDistance });
							    
	rightDots.push_back({ dotDistance, 0,  dotSpacing });
	rightDots.push_back({ dotDistance, 0,  0 });
	rightDots.push_back({ dotDistance, 0, -dotSpacing });

	leftDots.push_back({-dotDistance, 0,  dotSpacing });
	leftDots.push_back({-dotDistance, 0,  0.0f });
	leftDots.push_back({-dotDistance, 0, -dotSpacing });
							   
	backDots.push_back({-dotSpacing, 0, -dotDistance });
	backDots.push_back({ 0.0f, 0, -dotDistance });
	backDots.push_back({ dotSpacing, 0, -dotDistance });

	Position = position;
	FloorHeight = 0;
	
	viewBobbingTimer = 0;
	fallSpeed = 0;
	walkSpeed = 4;
	runSpeed = 6;
	currentSpeed = walkSpeed;
}

void Player::SetHitBoxes(vector<HitBox*> hitBoxes)
{
	this->hitBoxes = hitBoxes;
}

void Player::Update(float deltaTime)
{
	// Movement Speed
	float speedAcc = 10;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000) currentSpeed = currentSpeed < runSpeed ? currentSpeed += deltaTime * speedAcc : runSpeed;
	else currentSpeed = currentSpeed > walkSpeed ? currentSpeed -= deltaTime * speedAcc : walkSpeed;
	
	// Movement Vector
	XMFLOAT3 forward = camera->Forward;
	forward.y = 0;
	forward = Normalize(forward);

	XMFLOAT3 right = camera->Right;
	right.y = 0;
	right = Normalize(right);

	XMFLOAT3 moveVector = Add(Mult(forward, input->VAxis), Mult(right, input->HAxis));
	if (Length(moveVector) > 1) moveVector = Normalize(moveVector);

	float frequency = Length(moveVector) * currentSpeed * 1.75f;
	float amplitude = Length(moveVector) * 0.05f;

	// Hitbox Detection
	for (HitBox* hitBox : hitBoxes) 
	{
		for (int i = 0; i < frontDots.size(); i++) if (hitBox->PointIsInBox(Add(Position, frontDots[i]))) if (moveVector.z > 0) moveVector.z = 0;
		for (int i = 0; i < rightDots.size(); i++) if (hitBox->PointIsInBox(Add(Position, rightDots[i]))) if (moveVector.x > 0) moveVector.x = 0;
		for (int i = 0; i < leftDots.size(); i++) if (hitBox->PointIsInBox(Add(Position, leftDots[i]))) if (moveVector.x < 0) moveVector.x = 0;
		for (int i = 0; i < backDots.size(); i++) if (hitBox->PointIsInBox(Add(Position, backDots[i]))) if (moveVector.z < 0) moveVector.z = 0;
	}

	// Movement
	Position = Add(Position, Mult(moveVector, currentSpeed * deltaTime));
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && Position.y <= FloorHeight) fallSpeed = -6;
	
	// Gravity
	Position.y -= fallSpeed * deltaTime;

	if (Position.y <= FloorHeight) 
	{
		fallSpeed = 0;
		Position.y = FloorHeight;
	}
	else fallSpeed += deltaTime * 15.0f;

	// View Bobbing 
	if (Position.y > FloorHeight) 
	{
		amplitude -= (Position.y - FloorHeight) * amplitude * 1.5f;
		if (amplitude < 0) amplitude = 0;
	}

	viewBobbingTimer += deltaTime * frequency;
	if (viewBobbingTimer > XM_PI * 2) viewBobbingTimer = 0;

	// Camera 
	XMFLOAT3 camPos = Add(Position, { 0, 1.5f, 0 });
	camPos = Add(camPos, Mult(right, sin(viewBobbingTimer) * amplitude));
	camPos = Add(camPos, Mult({0, 1, 0}, 0.5f * amplitude * cos(viewBobbingTimer * 2) + amplitude * 0.5f));

	camera->Position = camPos;
}