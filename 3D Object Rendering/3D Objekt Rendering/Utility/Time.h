#pragma once
#include <Windows.h>
#include <chrono>
#include "Util.h"

using namespace std::chrono;

/// <summary>
/// An object that calculates the delta time.
/// </summary>
class Time
{
	public:
		/// <summary>
		/// The constructor of the time object.
		/// </summary>
		Time();

		/// <summary>
		/// Updates the time object every frame and refreshes delta time.
		/// </summary>
		void Update();

		/// <summary>The time that has passed since the last frame.</summary>
		float DeltaTime;

	private:
		/// <summary>The time point of the last frame.</summary>
		high_resolution_clock::time_point lastTime = {};
};