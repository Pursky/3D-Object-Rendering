#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include "Util.h"

using namespace DirectX;

/// <summary>
/// An object that handles mouse movement and input axes.
/// </summary>
class Input {
	public:
		/// <summary>
		/// The constructor of the input object.
		/// </summary>
		Input();

		/// <summary>
		/// Updates the input object every frame.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		void Update(float deltaTime);

		/// <summary>The last frames cursor position on the screen.</summary>
		XMFLOAT2 DeltaMouse;
		/// <summary>The current value of the horizontal input axis.</summary>
		float HAxis;
		/// <summary>The current value of the vertical input axis.</summary>
		float VAxis;
		/// <summary>The current value of the Q and E input axis.</summary>
		float QEAxis;

	private:
		/// <summary>
		/// Updates an input axis.
		/// </summary>
		/// <param name="axis">Pointer to the axis.</param>
		/// <param name="nKey">The negative key of the axis.</param>
		/// <param name="pKey">The positive key of the axis.</param>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		void UpdateAxis(float* axis, int nKey, int pKey, float deltaTime);
};