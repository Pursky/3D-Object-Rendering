#include <Windows.h>
#include "Window.h"
#include "Direct3D.h"
#include "Meshes/Sphere.h"
#include "Meshes/Skybox.h"
#include "Camera.h"
#include "Utility/Time.h"
#include "DirLight.h"
#include "Physics/Player.h"
#include "Physics/HeightBox.h"

/// <summary>
/// Initializes the programm, builds the map and runs the application loop.
/// </summary>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	bool isFullscreen = true;
	bool vSyncIsOn = true;

	int width = !isFullscreen ? GetSystemMetrics(0) * 0.6f : GetSystemMetrics(0);
	int height = !isFullscreen ? GetSystemMetrics(1) * 0.6f : GetSystemMetrics(1);

	Window* window = new Window(hInstance, width, height);
	Direct3D* direct3D = new Direct3D(window->Handle, width, height, isFullscreen);
	Input* input = new Input();
	Camera* camera = new Camera(direct3D->Device, width, height, input, {}, {});
	Player* player = new Player(camera, input, {0, 0, -7});

	DirLight* light = new DirLight(
		direct3D->Device,
		{
			{-1.0f,-0.5f, 1.0f},
			1.0f,
			{ 1.0f, 0.8f, 0.6f, 1.0f },
			{ 0.1f, 0.1f, 0.3f, 1.0f },
			-XM_PI * 0.25f
		},
		input
	);

	#pragma region Create Materials

	// Texture source:
	// https://assetstore.unity.com/packages/2d/textures-materials/sky/allsky-free-10-sky-skybox-set-146014

	Material* SkyMat = new Material(
		0,
		direct3D->Device,
		L"UnlitVertexShader.cso",
		L"UnlitPixelShader.cso",
		L"Skybox.jpg",
		{ 64.0f, 1.0f }
	);

	// Texture source: 
	// https://www.vectorstock.com/royalty-free-vector/marble-texture-design-seamless-pattern-vector-18429276

	Material* MarbleMat = new Material(
		1,
		direct3D->Device,
		L"PhongVertexShader.cso",
		L"PhongPixelShader.cso", 
		L"Marble.png",
		{ 32.0f, 0.75f }
	);

	// Texture sources: 
	// https://www.vectorstock.com/royalty-free-vector/marble-texture-design-seamless-pattern-vector-18429276
	// https://www.pinterest.de/pin/424253227367833218/

	Material* MarbleMixedMat = new Material(
		2,
		direct3D->Device,
		L"PhongVertexShader.cso",
		L"PhongPixelShader.cso",
		L"MarbleMixed.png",
		{ 32.0f, 0.75f }
	);

	// Texture source:
	// https://assetstore.unity.com/packages/2d/textures-materials/sky/allsky-free-10-sky-skybox-set-146014

	Material* ReflectionMat = new Material(
		3,
		direct3D->Device,
		L"ReflectVertexShader.cso",
		L"ReflectPixelShader.cso",
		L"SkyboxFlat.png",
		{ 64.0f, 1.0f }
	);

	// Texture source:
	// https://www.polantis.com/de/textures/glass-texture-28?choose-language=fr

	Material* GlassMat = new Material(
		4,
		direct3D->Device,
		L"PhongVertexShader.cso",
		L"PhongPixelShader.cso",
		L"Glass.png",
		{ 64.0f, 1.0f }
	);
	
	#pragma endregion

	std::vector<Mesh*> meshes;

	vector<Vertex> vertices;
	vector<short> indices;

	ReadMesh("Skybox.txt", &vertices, &indices);
	meshes.push_back(new Skybox(direct3D->Device, SkyMat, camera, &vertices, &indices, light, {}, { XM_PI * 0.02f, -XM_PI * 0.25f, 0.0f }, {100, 100, 100}));

	#pragma region Build Level

	// Floors
	ReadMesh("Floor02.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, {}, {}, {}));

	ReadMesh("Floor05.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { 8, 1, 8 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, {8, 1, 12}, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, {12, 1, 12}, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, {12, 1, 8}, {}, {}));
																		   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -8, 1, 8 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -8, 1, 12 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -12, 1, 12 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -12, 1, 8 }, {}, {}));
																		   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { 8, 1, -8 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { 8, 1, -12 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { 12, 1, -12 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { 12, 1, -8 }, {}, {}));
																		   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -8, 1, -8 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -8, 1, -12 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -12, 1, -12 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMixedMat, &vertices, &indices, { -12, 1, -8 }, {}, {}));

	ReadMesh("Floor00.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, {0, 0, 4}, {0, XM_PI * 0.5f, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, {0, 0, 8}, {0, XM_PI * 0.5f, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 0, 0, -4 }, { 0, XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 0, 0, -8 }, { 0, XM_PI * 0.5f, 0 }, {}));
														
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 0, 0 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 8, 0, 0 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 0, 0 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -8, 0, 0 }, {}, {}));

	ReadMesh("Floor01.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, {0, 0, 12}, {0, XM_PI * 0.5f, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 0, 0, -12 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 12, 0, 0 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -12, 0, 0 }, {}, {}));
														  
	ReadMesh("Floor03.txt", &vertices, &indices);			  
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -12, 0, 4 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -8, 0, 4 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 8, 0, 4 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 12, 0, 4 }, { 0, XM_PI, 0 }, {}));
														
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -12, 0, -4 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -8, 0, -4 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 8, 0, -4 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 12, 0, -4 }, {}, {}));
														  
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 0, 12 }, { 0, XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 0, 8 }, { 0, XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 0, -8 }, { 0, XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 0, -12 }, { 0, XM_PI * 0.5f, 0 }, {}));
														  
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 0, 12 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 0, 8 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 0, -8 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 0, -12 }, { 0, -XM_PI * 0.5f, 0 }, {}));
														   
	ReadMesh("Floor04.txt", &vertices, &indices);			   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 0, 4 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 0, 4 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 0, -4 }, { 0, XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 0, -4 }, {}, {}));
														   
	// Walls											   												   
	ReadMesh("Wall00.txt", &vertices, &indices);			   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -8, 1, 14 }, {0, XM_PI, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 8, 1, 14 }, {0, XM_PI, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -8, 1, -14 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 8, 1, -14 }, {}, {}));
														   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 1, -8 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 1, 8 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 1, -8 }, { 0, XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 1, 8 }, { 0, XM_PI * 0.5f, 0 }, {}));
														  
	ReadMesh("Wall02.txt", &vertices, &indices);			  
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 1, 14 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 1, -14 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 1, 4 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 1, -4 }, { 0, XM_PI * 0.5f, 0 }, {}));
														   
	ReadMesh("Wall04.txt", &vertices, &indices);			   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 4, 1, 14 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -4, 1, -14 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 1, -4 }, { 0, -XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 1, 4 }, { 0, XM_PI * 0.5f, 0 }, {}));
														   
	ReadMesh("Wall01.txt", &vertices, &indices);			   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 1, 12 }, {0, -XM_PI * 0.5f, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -12, 1, 14 }, {0, XM_PI, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 1, -12 }, { 0, XM_PI * 0.5f, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 12, 1, -14 }, {}, {}));
														   
	ReadMesh("Wall03.txt", &vertices, &indices);			   
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 0, 0, 14 }, {0, XM_PI * 0.5f, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 0, 0, -14 }, {0, -XM_PI * 0.5f, 0}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 0, 0 }, { 0, XM_PI, 0 }, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 0, 0 }, {}, {}));

	// Objects
	ReadMesh("PillarShort.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 6, 1, 6 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 6, 1, 10 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 10, 1, 6 }, {}, {}));
														
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -6, 1, 6 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -6, 1, 10 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -10, 1, 6 }, {}, {}));

	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 6, 1, -6 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 6, 1, -10 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 10, 1, -6 }, {}, {}));

	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -6, 1, -6 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -6, 1, -10 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -10, 1, -6 }, {}, {}));

	ReadMesh("Pillar.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 1.75f, 0, 1.75f }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -1.75f, 0, 1.75f }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 1.75f, 0, -1.75f }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -1.75f, 0, -1.75f }, {}, {}));

	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 1.75f, 0, 14 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -1.75f, 0, 14 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 1.75f, 0, -14 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -1.75f, 0, -14 }, {}, {}));

	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 0, 1.75f }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14, 0, -1.75f }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 0, 1.75f }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14, 0, -1.75f }, {}, {}));

	ReadMesh("Pedestal.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, {}, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { 14.1f, 0, 0 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, { -14.1f, 0, 0 }, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, {0, 0, 14.1f}, {}, {}));
	meshes.push_back(new Mesh(direct3D->Device, MarbleMat, &vertices, &indices, {0, 0, -14.1f}, {}, {}));

	ReadMesh("Teapot.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, ReflectionMat, &vertices, &indices, {0, 1, 0}, {}, {0.15f, 0.15f, 0.15f }));

	ReadMesh("Dolphin.txt", &vertices, &indices);
	meshes.push_back(new Mesh(direct3D->Device, GlassMat, &vertices, &indices, { 0, 1.25f, 14.1f }, {0, 0, XM_PI * 0.45f}, {40, 40, 40}));
	meshes.push_back(new Mesh(direct3D->Device, GlassMat, &vertices, &indices, { 0, 1.25f, -14.1f }, {0, XM_PI, XM_PI * 0.45f}, {40, 40, 40}));

	meshes.push_back(new Sphere(direct3D->Device, GlassMat, 16, false, { 14.1f, 1.5f, 0 }, {}, {}));
	meshes.push_back(new Sphere(direct3D->Device, GlassMat, 16, false, { -14.1f, 1.5f, 0 }, {}, {}));

	// Height Boxes
	vector<HeightBox*> heightBoxes;
	heightBoxes.push_back(new HeightBox(player, {-2, 2, -16, 16}, 0, 0, 0));
	heightBoxes.push_back(new HeightBox(player, {-16, 16, -2, 2}, 0, 0, 0));

	heightBoxes.push_back(new HeightBox(player, {3, 16, 3, 16}, 1, 1, 0));
	heightBoxes.push_back(new HeightBox(player, {-16, -3, 3, 16}, 1, 1, 0));
	heightBoxes.push_back(new HeightBox(player, {3, 16, -16, -3}, 1, 1, 0));
	heightBoxes.push_back(new HeightBox(player, {-16, -3, -16, -3}, 1, 1, 0));

	// Hit Boxes
	vector<HitBox*> hitBoxes;
	hitBoxes.push_back(new HitBox({-14, 14, 13.5f, 14}));
	hitBoxes.push_back(new HitBox({-14, 14, -14, -13.5f}));
	hitBoxes.push_back(new HitBox({-14, -13.5f, -14, 14}));
	hitBoxes.push_back(new HitBox({13.5f, 14, -14, 14}));

	hitBoxes.push_back(new HitBox({-0.5f, 0.5f, -0.5f, 0.5f}));

	hitBoxes.push_back(new HitBox({ 1.25f, 2.25f, 1.25f, 2.25f}));
	hitBoxes.push_back(new HitBox({-2.25f,-1.25f, 1.25f, 2.25f}));
	hitBoxes.push_back(new HitBox({ 1.25f, 2.25f,-2.25f,-1.25f }));
	hitBoxes.push_back(new HitBox({-2.25f,-1.25f,-2.25f,-1.25f }));

	hitBoxes.push_back(new HitBox({ 5.5f, 6.5f, 5.5f, 6.5f}));
	hitBoxes.push_back(new HitBox({ 5.5f, 6.5f, 9.5f, 10.5f}));
	hitBoxes.push_back(new HitBox({ 9.5f, 10.5f, 5.5f, 6.5f}));

	hitBoxes.push_back(new HitBox({-6.5f,-5.5f, 5.5f, 6.5f }));
	hitBoxes.push_back(new HitBox({-6.5f,-5.5f, 9.5f, 10.5f }));
	hitBoxes.push_back(new HitBox({-10.5f,-9.5f, 5.5f, 6.5f }));

	hitBoxes.push_back(new HitBox({ 5.5f, 6.5f, -6.5f, -5.5f }));
	hitBoxes.push_back(new HitBox({ 5.5f, 6.5f, -10.5f, -9.5f }));
	hitBoxes.push_back(new HitBox({ 9.5f, 10.5f, -6.5f, -5.5f }));

	hitBoxes.push_back(new HitBox({ -6.5f,-5.5f, -6.5f, -5.5f }));
	hitBoxes.push_back(new HitBox({ -6.5f,-5.5f, -10.5f, -9.5f }));
	hitBoxes.push_back(new HitBox({ -10.5f,-9.5f, -6.5f, -5.5f }));

	player->SetHitBoxes(hitBoxes);

	#pragma endregion

	vertices.clear();
	indices.clear();

	Time* time = new Time();

	// Game Loop

	int currentMatID = -1;

	while (window->IsRunning()) 
	{
		// Updates

		time->Update();
		light->Update(time->DeltaTime);
		for (Mesh* mesh : meshes) mesh->Update(time->DeltaTime);
		for (HeightBox* box : heightBoxes) box->Update(time->DeltaTime);
		input->Update(time->DeltaTime);
		player->Update(time->DeltaTime);
		camera->Update(time->DeltaTime);

		// Renders

		direct3D->StartRender();

		light->Render(direct3D->Context);
		camera->Render(direct3D->Context);
		for (Mesh* mesh : meshes) mesh->Render(direct3D->Context, &currentMatID);

		direct3D->EndRender(vSyncIsOn);

		currentMatID = -1;
	}

	return 0;
}