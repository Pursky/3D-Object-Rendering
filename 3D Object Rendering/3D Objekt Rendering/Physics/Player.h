#pragma once
#include "../Camera.h"
#include <vector>
#include "HitBox.h"

/// <summary>
/// A player object, that interacts with it's enviroment.
/// </summary>
class Player
{
	public:
		/// <summary>
		/// The constructor of the player.
		/// </summary>
		/// <param name="camera">The camera object of the application.</param>
		/// <param name="input">The input object of the application.</param>
		/// <param name="position">The start position of the player.</param>
		Player(Camera* camera, Input* input,  XMFLOAT3 position);

		/// <summary>
		/// Assigns the hitboxes of the application to the player.
		/// </summary>
		/// <param name="hitBoxes">The hitboxes of the application.</param>
		void SetHitBoxes(vector<HitBox*> hitBoxes);

		/// <summary>
		/// Updates and moves the player every frame.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		void Update(float deltaTime);

		/// <summary>The current position of the player.</summary>
		XMFLOAT3 Position;
		/// <summary>The current height of the ground.</summary>
		float FloorHeight;

	private:
		/// <summary>The input object of the application</summary>
		Input* input;
		/// <summary>The camera object of the application</summary>
		Camera* camera;
		/// <summary>The hitboxes of the application</summary>
		vector<HitBox*> hitBoxes;

		/// <summary>The dots that define the players collision in z+ direction.</summary>
		vector<XMFLOAT3> frontDots;
		/// <summary>The dots that define the players collision in x+ direction.</summary>
		vector<XMFLOAT3> rightDots;
		/// <summary>The dots that define the players collision in x- direction.</summary>
		vector<XMFLOAT3> leftDots;
		/// <summary>The dots that define the players collision in z- direction.</summary>
		vector<XMFLOAT3> backDots;

		/// <summary>The timer that is used to calculate the cameras view bobbing effect.</summary>
		float viewBobbingTimer;
		/// <summary>The current y speed of the player.</summary>
		float fallSpeed;
		
		/// <summary>The max speed that the player has while walking.</summary>
		float walkSpeed;					
		/// <summary>The max speed that the player has while running.</summary>
		float runSpeed;
		/// <summary>The current max speed of the player.</summary>
		float currentSpeed;
};