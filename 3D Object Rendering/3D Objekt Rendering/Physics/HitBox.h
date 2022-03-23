#pragma once
#include <DirectXMath.h>

using namespace DirectX;

/// <summary>
/// An object that the player can collide with.
/// </summary>
class HitBox
{
	public:
		/// <summary>
		/// The constructor of the hitbox.
		/// </summary>
		/// <param name="dimensions">The dimensions of the box: x = left wall, y = right wall, z = back wall, w = front wall.</param>
		HitBox(XMFLOAT4 dimensions);

		/// <summary>
		/// Returns whether a point is within the box or not.
		/// </summary>
		/// <param name="point">The point that is tested.</param>
		bool PointIsInBox(XMFLOAT3 point);

	private:
		/// <summary>The dimensions of the box: x = left wall, y = right wall, z = back wall, w = front wall.</summary>
		XMFLOAT4 dimensions;
};