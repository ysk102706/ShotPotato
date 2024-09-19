#include "Engine.h"

Engine::Engine(HINSTANCE hInstance, int width, int height, std::wstring title) {
	if (!Window::InitWindow(hInstance, width, height, title) || !Init()) {
		MessageBox(nullptr, L"엔진 초기화 실패", L"오류", 0);
		exit(-1);
	}
}

bool Engine::Init() {
	if (!InitDirect3D()) return false;
	if (!InitScene()) return false;
	return true;
}

int Engine::Run() {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			if (InputProcessor::IsKeyDown(Keyboard::Keys::Escape)) {
				if (MessageBox(nullptr, L"종료하시겠습니까?", L"종료", MB_YESNO) == IDYES) {
					DestroyWindow(Window::GetHWND());
					return 0;
				}
			}

			Update();
			Draw();
		}
	}

	return 0;
}

void Engine::Update() {
	static float moveSpeed = 0.1f;
	if (InputProcessor::IsKeyDown(Keyboard::Keys::W)) camera.MoveForward(moveSpeed);
	if (InputProcessor::IsKeyDown(Keyboard::Keys::S)) camera.MoveForward(-moveSpeed);
	if (InputProcessor::IsKeyDown(Keyboard::Keys::A)) camera.MoveRight(-moveSpeed);
	if (InputProcessor::IsKeyDown(Keyboard::Keys::D)) camera.MoveRight(moveSpeed);
	if (InputProcessor::IsKeyDown(Keyboard::Keys::Q)) camera.MoveUp(moveSpeed);
	if (InputProcessor::IsKeyDown(Keyboard::Keys::E)) camera.MoveUp(-moveSpeed);

	Mouse::State state = InputProcessor::MouseState();
	static float rotationSpeed = 0.2f;
	if (state.leftButton == true) {
		camera.Yaw((float)state.x * rotationSpeed);
		camera.Pitch((float)state.y * rotationSpeed);
	}

	camera.UpdateCamera();
	modelUV.UpdateBuffers(deviceContext.Get());
}

void Engine::Draw()
{
	float backgroundColor[4] = { 0, 0.75f, 0, 1 };

	deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), backgroundColor);

	camera.BindBuffer(deviceContext.Get());

	textureShader.Bind(deviceContext.Get());

	modelUV.RenderBuffers(deviceContext.Get());

	swapChain.Get()->Present(1, 0);
}

bool Engine::InitScene()
{
	camera = Camera(
		70.0f * Math::Deg2Rad,
		(float)Window::Width(),
		(float)Window::Height(),
		0.1f,
		1000.0f
	);

	camera.SetPosition(0.0f, 0.0f, -10.0f);

	if (!camera.CreateBuffer(device.Get())) return false;

	if (!textureShader.Init(device.Get(), L"potato.png")) return false;
	if (!modelUV.InitBuffers(device.Get(), textureShader.ShaderBuffer(), "cube.fbx")) return false;
	modelUV.SetPosition(4.0f, 5.0f, 6.0f);
	modelUV.SetRotation(20.0f, 80.0f, 50.0f);
	modelUV.SetScale(1.0f, 1.0f, 1.0f);

	return true;
}

bool Engine::InitDirect3D() {
	DXGI_SWAP_CHAIN_DESC sc_desc;
	ZeroMemory(&sc_desc, sizeof(sc_desc));
	sc_desc.BufferCount = 1; 
	sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	sc_desc.OutputWindow = Window::GetHWND(); 
	sc_desc.Windowed = true; 
	sc_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; 
	sc_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	sc_desc.BufferDesc.Width = Window::Width(); 
	sc_desc.BufferDesc.Height = Window::Height(); 
	sc_desc.SampleDesc.Count = 1;
	sc_desc.SampleDesc.Quality = 0; 

	HRESULT ret = D3D11CreateDeviceAndSwapChain(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, 
		0, 
		nullptr, 
		0, 
		D3D11_SDK_VERSION, 
		&sc_desc,
		swapChain.GetAddressOf(), 
		device.GetAddressOf(), 
		NULL, 
		deviceContext.GetAddressOf() 
	);

	if (FAILED(ret)) return false;

	ID3D11Texture2D* backbufferTexture;
	ret = swapChain.Get()->GetBuffer(
		NULL,
		__uuidof(ID3D11Texture2D),
		(void**)(&backbufferTexture)
	);

	if (FAILED(ret)) return false;

	ret = device.Get()->CreateRenderTargetView(
		backbufferTexture,
		nullptr,
		renderTargetView.GetAddressOf()
	);

	if (FAILED(ret)) return false;

	backbufferTexture->Release();

	deviceContext.Get()->OMSetRenderTargets(
		1,
		renderTargetView.GetAddressOf(),
		nullptr
	);

	viewport.TopLeftX = 0; 
	viewport.TopLeftY = 0; 
	viewport.Width = (float)Window::Width(); 
	viewport.Height = (float)Window::Height(); 
	viewport.MinDepth = 0.0f; 
	viewport.MaxDepth = 1.0f; 

	deviceContext.Get()->RSSetViewports(1, &viewport);

	return true;
}