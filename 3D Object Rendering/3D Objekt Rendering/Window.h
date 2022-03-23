#pragma once
#include <Windows.h>

/// <summary>
/// An object for a window.
/// </summary>
class Window
{
	public:
		/// <summary>
		/// The constructor of the window.
		/// </summary>
		/// <param name="hInstance">The instance of the application.</param>
		/// <param name="width">The pixel width of the window.</param>
		/// <param name="height">The pixel height of the window.</param>
		Window(HINSTANCE hInstance, int width, int height);

		/// <summary>
		/// Returns whether the window is still up.
		/// </summary>
		bool IsRunning();

		/// <summary>The handle of the window.</summary>
		HWND Handle = nullptr;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);