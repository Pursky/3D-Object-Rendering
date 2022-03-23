#pragma once
#include <d3d11.h>
#include <xutility>

#pragma comment(lib, "d3d11.lib")

/// <summary>
/// An object that sets up and updates the direct3D11 connection to the application.
/// </summary>
class Direct3D
{
	public:
		/// <summary>
		/// The constructor of the direct3D object.
		/// </summary>
		/// <param name="windowHandle">A Handle to the applcations window.</param>
		/// <param name="width">The pixel width of the window.</param>
		/// <param name="height">The pixel height of the window.</param>
		/// <param name="isFullscreen">Whether the window is in fullscreen mode.</param>
		Direct3D(HWND windowHandle, int width, int height, bool isFullscreen);

		/// <summary>
		/// Clears the screen and starts a new render view.
		/// </summary>
		void StartRender();

		/// <summary>
		/// Presents the frame, when the render view is complete.
		/// </summary>
		/// <param name="vSyncIsOn">Whether vertical sync is enabled.</param>
		void EndRender(bool vSyncIsOn);

		/// <summary>The d3d device of the application.</summary>
		ID3D11Device* Device = nullptr;
		/// <summary>The d3d device context of the application.</summary>
		ID3D11DeviceContext* Context = nullptr;

	private:
		/// <summary>The rasterizer state of the application.</summary>
		ID3D11RasterizerState* rasterizerState = nullptr;
		/// <summary>The swap chain of the application.</summary>
		IDXGISwapChain* swapChain = nullptr;
		/// <summary>The render target view of the application.</summary>
		ID3D11RenderTargetView* renderTargetView = nullptr;
		/// <summary>The depth stencil view of the application.</summary>
		ID3D11DepthStencilView* depthStencilView = nullptr;
};