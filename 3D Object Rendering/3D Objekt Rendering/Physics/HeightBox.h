#pragma once
#include "Player.h"

/// <summary>
/// An object that actively updates the height of the ground, if the player is inside of it.
/// </summary>
class HeightBox
{
	public:
		/// <summary>
		/// The constructor of the height box.
		/// </summary>
		/// <param name="player">The player object of the application.</param>
		/// <param name="dimensions">The dimensions of the box: x = left wall, y = right wall, z = back wall, w = front wall.</param>
		/// <param name="height">The ground height within the box.</param>
		/// <param name="rimSize">The size of the rim outside of the box, that the players height is interpolated in.</param>
		/// <param name="rimHeight">The height at the edge of rim.</param>
		HeightBox(Player* player, XMFLOAT4 dimensions, float height, float rimSize, float rimHeight);

		/// <summary>
		/// Updates the height box every frame.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		void Update(float deltaTime);

	private:
		/// <summary>The player object of the application.</summary>
		Player* player;
		/// <summary>The dimensions of the box: x = left wall, y = right wall, z = back wall, w = front wall.</summary>
		XMFLOAT4 dimensions;
		/// <summary>The ground height within the box.</summary>
		float height;
		/// <summary>The size of the rim outside of the box, that the players height is interpolated in.</summary>
		float rimSize; 
		/// <summary>The height at the edge of rim.</summary>
		float rimHeight;
};