// CGS HW Project A "Line Land".
// Author: L.Norri CD CGS, FullSail University

// Introduction:
// Welcome to the hardware project of the Computer Graphics Systems class.
// This assignment is fully guided but still requires significant effort on your part. 
// Future classes will demand the habits & foundation you develop right now!  
// It is CRITICAL that you follow each and every step. ESPECIALLY THE READING!!!

// TO BEGIN: Open the word document that acompanies this project and start from the top.

//************************************************************
//************ INCLUDES & DEFINES ****************************
//************************************************************

#include <iostream>
#include <ctime>
#include "XTime.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <D3D11.h>
#include <D3DX10math.h>
#include "InjuredSWAT.h"

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")

#include "Trivial_PS.csh"
#include "Trivial_VS.csh"
#include "swatShader.csh"
#include "swatPShader.csh"

#define BACKBUFFER_WIDTH	900
#define BACKBUFFER_HEIGHT	700

//************************************************************
//************ SIMPLE WINDOWS APP CLASS **********************
//************************************************************

class DEMO_APP
{	
	HINSTANCE						application;
	WNDPROC							appWndProc;
	HWND							window;
	

public:
	//stuff that is required to create the window
	XTime timer;
	DXGI_SWAP_CHAIN_DESC scd;
	ID3D11Device *tDev;
	ID3D11DeviceContext *tdContext;
	IDXGISwapChain *sC;
	ID3D11Texture2D *t2D;
	ID3D11RenderTargetView *rtV;
	D3D11_VIEWPORT vP;

	//input layouts
	ID3D11InputLayout *ilayOut;
	ID3D11InputLayout *ilayOutSwat;

	//vertex buffer descriptions
	D3D11_BUFFER_DESC gbDesc;
	D3D11_BUFFER_DESC vbDesc;
	D3D11_BUFFER_DESC vbDesc2;
	D3D11_BUFFER_DESC lvbuffDesc;
	D3D11_BUFFER_DESC swatbuffDesc;
	D3D11_BUFFER_DESC swatindexbuffDesc;

	//subresource data
	D3D11_SUBRESOURCE_DATA srData;

	//vertex buffers
	ID3D11Buffer *vB;
	ID3D11Buffer *gB;
	ID3D11Buffer *lvBuff;
	ID3D11Buffer *vBuff2;
	ID3D11Buffer *swatBuffer;
	ID3D11Buffer *swatindexBuff;
	

	//strides
	UINT stride; 
	UINT gS;
	UINT lStride;
	UINT swatdataStride;
	UINT swatindexStride;

	//offsets
	UINT oS = 0.0f;
	UINT goS = 0.0f;
	UINT loS = 0.0f;
	UINT swatoS = 0.0f;

	//shaders
	ID3D11PixelShader *pS;
	ID3D11VertexShader *vS;
	ID3D11VertexShader *svS;
	ID3D11PixelShader *spS;

	//mapped subresource
	D3D11_MAPPED_SUBRESOURCE mappedsubRe;

	ID3D11Texture2D *texture;
	D3D11_TEXTURE2D_DESC textDesc;
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ID3D11DepthStencilState *dsState;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ID3D11DepthStencilView *Dsv;

	float degVal = XMConvertToRadians(90.0f);
	
	
	struct Vert
	{
		XMFLOAT4 pos;
		XMFLOAT4 color;
		XMFLOAT4 norm;
		XMFLOAT3 dir;
	};

	struct Light
	{
		XMFLOAT4 position;
		XMFLOAT4 color;
		XMFLOAT4 direction;
	};

	struct Matrices
	{
		XMMATRIX worldMat, perspectiveMat, vMat, projection, cam;
	}; Matrices m;

	Vert simpVerts[36];
	Vert grid[44];
	Light light;
	OBJ_VERT swat;


	DEMO_APP(HINSTANCE hinst, WNDPROC proc);
	bool Run();
	void Render();
	void Move();
	void Zoom();
	bool ShutDown();
};


//************************************************************
//************ CREATION OF OBJECTS & RESOURCES ***************
//************************************************************

DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
{
	// ****************** BEGIN WARNING ***********************// 
	// WINDOWS CODE, I DON'T TEACH THIS YOU MUST KNOW IT ALREADY! 
	//starting the window up
	application = hinst; 
	appWndProc = proc; 

	WNDCLASSEX  wndClass;
    ZeroMemory( &wndClass, sizeof( wndClass ) );
    wndClass.cbSize         = sizeof( WNDCLASSEX );             
    wndClass.lpfnWndProc    = appWndProc;						
    wndClass.lpszClassName  = L"DirectXApplication";            
	wndClass.hInstance      = application;		               
    wndClass.hCursor        = LoadCursor( NULL, IDC_ARROW );    
    wndClass.hbrBackground  = ( HBRUSH )COLOR_WINDOW; 
	//wndClass.hIcon			= LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FSICON));
    RegisterClassEx( &wndClass );

	RECT window_size = { 0, 0, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT };
	AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);

	window = CreateWindow(	L"DirectXApplication", L"P&P4 Scene",	WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME|WS_MAXIMIZEBOX), 
							CW_USEDEFAULT, CW_USEDEFAULT, window_size.right-window_size.left, window_size.bottom-window_size.top,					
							NULL, NULL,	application, this );												

    ShowWindow( window, SW_SHOW );
	//********************* END WARNING ************************//
	

#pragma region Cube
	//top face
	simpVerts[0].pos = XMFLOAT4(-0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[1].pos = XMFLOAT4(0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[2].pos = XMFLOAT4(0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[3].pos = XMFLOAT4(-0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[4].pos = XMFLOAT4(0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[5].pos = XMFLOAT4(-0.25f, 0.50f, -0.25f, 1.0f);

	//front face
	simpVerts[6].pos = XMFLOAT4(-0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[7].pos = XMFLOAT4(0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[8].pos = XMFLOAT4(0.25f, 0.0f, -0.25f, 1.0f);
	simpVerts[9].pos = XMFLOAT4(-0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[10].pos = XMFLOAT4(0.25f, 0.0f, -0.25f, 1.0f);
	simpVerts[11].pos = XMFLOAT4(-0.25f, 0.0f, -0.25f, 1.0f);

	//left face
	simpVerts[12].pos = XMFLOAT4(-0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[13].pos = XMFLOAT4(-0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[14].pos = XMFLOAT4(-0.25f, 0.0f, -0.25f, 1.0f);
	simpVerts[15].pos = XMFLOAT4(-0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[16].pos = XMFLOAT4(-0.25f, 0.0f, -0.25f, 1.0f);
	simpVerts[17].pos = XMFLOAT4(-0.25f, 0.0f, 0.25f, 1.0f);

	//back face
	simpVerts[18].pos = XMFLOAT4(0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[19].pos = XMFLOAT4(-0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[20].pos = XMFLOAT4(-0.25f, 0.0f, 0.25f, 1.0f);
	simpVerts[21].pos = XMFLOAT4(0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[22].pos = XMFLOAT4(-0.25f, 0.0f, 0.25f, 1.0f);
	simpVerts[23].pos = XMFLOAT4(0.25f, 0.0f, 0.25f, 1.0f);

	//right face
	simpVerts[24].pos = XMFLOAT4(0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[25].pos = XMFLOAT4(0.25f, 0.50f, 0.25f, 1.0f);
	simpVerts[26].pos = XMFLOAT4(0.25f, 0.0f, 0.25f, 1.0f);
	simpVerts[27].pos = XMFLOAT4(0.25f, 0.50f, -0.25f, 1.0f);
	simpVerts[28].pos = XMFLOAT4(0.25f, 0.0f, 0.25f, 1.0f);
	simpVerts[29].pos = XMFLOAT4(0.25f, 0.0f, -0.25f, 1.0f);

	//bottom face
	simpVerts[30].pos = XMFLOAT4(-0.25f, 0.0f, 0.25f, 1.0f);
	simpVerts[31].pos = XMFLOAT4(0.25f, 0.0f, 0.25f, 1.0f);
	simpVerts[32].pos = XMFLOAT4(0.25f, 0.0f, -0.25f, 1.0f);
	simpVerts[33].pos = XMFLOAT4(-0.25f, 0.0f, 0.25f, 1.0f);
	simpVerts[34].pos = XMFLOAT4(0.25f, 0.0f, -0.25f, 1.0f);
	simpVerts[35].pos = XMFLOAT4(-0.25f, 0.0f, -0.25f, 1.0f);
#pragma endregion cube faces

#pragma region Grid
	//grid coordinates
	grid[0].pos = XMFLOAT4(-0.5f, 0.0f, 0.5f, 1.0f);
	grid[1].pos = XMFLOAT4(-0.5f, 0.0f, -0.5f, 1.0f);
	grid[2].pos = XMFLOAT4(-0.4f, 0.0f, 0.5f, 1.0f);
	grid[3].pos = XMFLOAT4(-0.4f, 0.0f, -0.5f, 1.0f);
	grid[4].pos = XMFLOAT4(-0.3f, 0.0f, 0.5f, 1.0f);
	grid[5].pos = XMFLOAT4(-0.3f, 0.0f, -0.5f, 1.0f);
	grid[6].pos = XMFLOAT4(-0.2f, 0.0f, 0.5f, 1.0f);
	grid[7].pos = XMFLOAT4(-0.2f, 0.0f, -0.5f, 1.0f);
	grid[8].pos = XMFLOAT4(-0.1f, 0.0f, 0.5f, 1.0f);
	grid[9].pos = XMFLOAT4(-0.1f, 0.0f, -0.5f, 1.0f);
	grid[10].pos = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
	grid[11].pos = XMFLOAT4(0.0f, 0.0f, -0.5f, 1.0f);
	grid[12].pos = XMFLOAT4(0.1f, 0.0f, 0.5f, 1.0f);
	grid[13].pos = XMFLOAT4(0.1f, 0.0f, -0.5f, 1.0f);
	grid[14].pos = XMFLOAT4(0.2f, 0.0f, 0.5f, 1.0f);
	grid[15].pos = XMFLOAT4(0.2f, 0.0f, -0.5f, 1.0f);
	grid[16].pos = XMFLOAT4(0.3f, 0.0f, 0.5f, 1.0f);
	grid[17].pos = XMFLOAT4(0.3f, 0.0f, -0.5f, 1.0f);
	grid[18].pos = XMFLOAT4(0.4f, 0.0f, 0.5f, 1.0f);
	grid[19].pos = XMFLOAT4(0.4f, 0.0f, -0.5f, 1.0f);
	grid[20].pos = XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f);
	grid[21].pos = XMFLOAT4(0.5f, 0.0f, -0.5f, 1.0f);
	grid[22].pos = XMFLOAT4(-0.5f, 0.0f, -0.5f, 1.0f);
	grid[23].pos = XMFLOAT4(0.5f, 0.0f, -0.5f, 1.0f);
	grid[24].pos = XMFLOAT4(-0.5f, 0.0f, -0.4f, 1.0f);
	grid[25].pos = XMFLOAT4(0.5f, 0.0f, -0.4f, 1.0f);
	grid[26].pos = XMFLOAT4(-0.5f, 0.0f, -0.3f, 1.0f);
	grid[27].pos = XMFLOAT4(0.5f, 0.0f, -0.3f, 1.0f);
	grid[28].pos = XMFLOAT4(-0.5f, 0.0f, -0.2f, 1.0f);
	grid[29].pos = XMFLOAT4(0.5f, 0.0f, -0.2f, 1.0f);
	grid[30].pos = XMFLOAT4(-0.5f, 0.0f, -0.1f, 1.0f);
	grid[31].pos = XMFLOAT4(0.5f, 0.0f, -0.1f, 1.0f);
	grid[32].pos = XMFLOAT4(-0.5f, 0.0f, 0.0f, 1.0f);
	grid[33].pos = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
	grid[34].pos = XMFLOAT4(-0.5f, 0.0f, 0.1f, 1.0f);
	grid[35].pos = XMFLOAT4(0.5f, 0.0f, 0.1f, 1.0f);
	grid[36].pos = XMFLOAT4(-0.5f, 0.0f, 0.2f, 1.0f);
	grid[37].pos = XMFLOAT4(0.5f, 0.0f, 0.2f, 1.0f);
	grid[38].pos = XMFLOAT4(-0.5f, 0.0f, 0.3f, 1.0f);
	grid[39].pos = XMFLOAT4(0.5f, 0.0f, 0.3f, 1.0f);
	grid[40].pos = XMFLOAT4(-0.5f, 0.0f, 0.4f, 1.0f);
	grid[41].pos = XMFLOAT4(0.5f, 0.0f, 0.4f, 1.0f);
	grid[42].pos = XMFLOAT4(-0.5f, 0.0f, 0.5f, 1.0f);
	grid[43].pos = XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f);
#pragma endregion stuff for the grid

#pragma region Light
	light.position = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	light.color = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	light.direction = XMFLOAT4(-0.25f, -0.25f, -0.25f, 1.0f);
#pragma endregion light stuff


	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = BACKBUFFER_WIDTH;
	scd.BufferDesc.Height = BACKBUFFER_HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;
	scd.OutputWindow = window;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, &scd, &sC, &tDev, NULL, &tdContext);


	sC->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&t2D);
	tDev->CreateRenderTargetView(t2D, NULL, &rtV);
	t2D->Release();

	texture = NULL;
	ZeroMemory(&textDesc, sizeof(textDesc));
	textDesc.Width = BACKBUFFER_WIDTH;
	textDesc.Height = BACKBUFFER_HEIGHT;
	textDesc.MipLevels = 1;
	textDesc.ArraySize = 1;
	textDesc.Format = DXGI_FORMAT_D32_FLOAT;
	textDesc.SampleDesc.Count = 1;
	textDesc.SampleDesc.Quality = 0;
	textDesc.Usage = D3D11_USAGE_DEFAULT;
	textDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textDesc.CPUAccessFlags = 0;
	textDesc.MiscFlags = 0;
	tDev->CreateTexture2D(&textDesc, NULL, &texture);

	//depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xff;
	dsDesc.StencilWriteMask = 0xff;

	//stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	

	//stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


	tDev->CreateDepthStencilState(&dsDesc, &dsState);
	tdContext->OMSetDepthStencilState(dsState, 1);

	//dsvDesc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	tDev->CreateDepthStencilView(texture, &dsvDesc, &Dsv);


	vP.Width = (float)BACKBUFFER_WIDTH;
	vP.Height = (float)BACKBUFFER_HEIGHT;
	vP.MinDepth = 0.0f;
	vP.MaxDepth = 1.0f;
	vP.TopLeftX = 0.0f;
	vP.TopLeftY = 0.0f;
	tdContext->RSSetViewports(1, &vP);

	D3D11_INPUT_ELEMENT_DESC layOut[] =
	{ {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
	  {"RGBVal", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
	  {"theNORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
	  {"dir", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numofElements = ARRAYSIZE(layOut);

	tDev->CreateInputLayout(layOut, numofElements, Trivial_VS, sizeof(Trivial_VS), &ilayOut);

	D3D11_INPUT_ELEMENT_DESC swatlayOut[] = 
	{
		{"LOCATION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXTURE", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numofelements2 = ARRAYSIZE(swatlayOut);
	tDev->CreateInputLayout(swatlayOut, numofelements2, swatShader, sizeof(swatShader), &ilayOutSwat);

	

	ZeroMemory(&vbDesc, sizeof(vbDesc));
	vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vbDesc.ByteWidth = sizeof(simpVerts);
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = simpVerts;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&vbDesc, &srData, &vB); 

	ZeroMemory(&gbDesc, sizeof(gbDesc));
	gbDesc.Usage = D3D11_USAGE_IMMUTABLE;
	gbDesc.ByteWidth = sizeof(grid);
	gbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	gbDesc.CPUAccessFlags = 0;
	gbDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = &grid;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&gbDesc, &srData, &gB);

	ZeroMemory(&vbDesc2, sizeof(vbDesc2));
	vbDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vbDesc2.ByteWidth = sizeof(Matrices);
	vbDesc2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbDesc2.MiscFlags = 0;
	vbDesc2.StructureByteStride = 0;
	vbDesc2.Usage = D3D11_USAGE_DYNAMIC;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = &m;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&vbDesc2, &srData, &vBuff2);

	ZeroMemory(&swatbuffDesc, sizeof(swatbuffDesc));
	swatbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	swatbuffDesc.ByteWidth = sizeof(OBJ_VERT) * 3119;
	swatbuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	swatbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	swatbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = InjuredSWAT_data;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&swatbuffDesc, &srData, &swatBuffer);

	ZeroMemory(&swatindexbuffDesc, sizeof(swatindexbuffDesc));
	swatindexbuffDesc.Usage = D3D11_USAGE_DEFAULT;
	swatindexbuffDesc.ByteWidth = sizeof(unsigned int) * 12594;
	swatindexbuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	swatindexbuffDesc.CPUAccessFlags = 0;
	swatindexbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = InjuredSWAT_indicies;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&swatindexbuffDesc, &srData, &swatindexBuff);

	ZeroMemory(&lvbuffDesc, sizeof(lvbuffDesc));
	lvbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	lvbuffDesc.ByteWidth = sizeof(Light);
	lvbuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lvbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lvbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = &light;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&lvbuffDesc, &srData, &lvBuff);

	//setting the initial inverse for the camera
	
	float rtX = XMConvertToRadians(32.0f);
	m.vMat = XMMatrixMultiply(XMMatrixTranslation(0, 0, -5), XMMatrixRotationX(rtX));
	m.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 10);
	
	//creating pixel shaders
	tDev->CreatePixelShader(Trivial_PS, sizeof(Trivial_PS), NULL, &pS);
	tDev->CreatePixelShader(swatPShader, sizeof(swatPShader), NULL, &spS);

	//creating vertex shaders
	tDev->CreateVertexShader(Trivial_VS, sizeof(Trivial_VS), NULL, &vS);
	tDev->CreateVertexShader(swatShader, sizeof(swatShader), NULL, &svS);
}

//************************************************************
//************ EXECUTION *************************************
//************************************************************

bool DEMO_APP::Run()
{
	//while the app is running
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DEMO_APP::Render();
		}
	}

	return true; 
}

void DEMO_APP::Render()
{
	tdContext->ClearDepthStencilView(Dsv, 1, 1, 1);
	timer.Signal();
	tdContext->OMSetRenderTargets(1, &rtV, Dsv);
	float colors[4] = { 0.0f, 0.125f, 0.6f, 1.0f };
	tdContext->ClearRenderTargetView(rtV, colors);
	
	
	float zIn = XMConvertToRadians(120.0f);
	float zOut = XMConvertToRadians(20.0f);
	m.worldMat = XMMatrixIdentity();
	
	m.worldMat = XMMatrixMultiply(XMMatrixTranslation(0, 0.25f, 0), XMMatrixRotationY(timer.TotalTime() * 1));
	Move();
	if (GetAsyncKeyState('Z'))
	{
		m.perspectiveMat = XMMatrixPerspectiveFovLH(zOut, 1, .1, 10);
	}
	else if (GetAsyncKeyState('X'))
	{
		m.perspectiveMat = XMMatrixPerspectiveFovLH(zIn, 1, .1, 10);
	}
	else if (GetAsyncKeyState('N'))
	{
		m.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 10);
	}
	
	m.vMat = XMMatrixInverse(nullptr, m.vMat);
	tdContext->Map(vBuff2, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedsubRe);
	memcpy(mappedsubRe.pData, &m, sizeof(m));
	tdContext->Unmap(vBuff2, NULL);
	tdContext->VSSetConstantBuffers(2, 1, &vBuff2);



	m.vMat = XMMatrixInverse(nullptr, m.vMat);
	tdContext->Map(lvBuff, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedsubRe);
	memcpy(mappedsubRe.pData, &light, sizeof(light));
	tdContext->Unmap(lvBuff, NULL);
	tdContext->VSSetConstantBuffers(1, 1, &lvBuff);
	


	tdContext->IASetInputLayout(ilayOut);
	stride = sizeof(Vert);
	tdContext->IASetVertexBuffers(0, 1, &vB, &stride, &oS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//Triangle strip references previously used vertices, Triangle List requires all new vertices
	tdContext->VSSetShader(vS, NULL, 0);
	tdContext->PSSetShader(pS, NULL, 0);
	tdContext->Draw(36, 0);

	gS = sizeof(Vert);
	tdContext->IASetVertexBuffers(0, 1, &gB, &gS, &goS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	tdContext->VSSetShader(vS, NULL, 0);
	tdContext->PSSetShader(pS, NULL, 0);
	tdContext->Draw(44, 0);

	tdContext->IASetInputLayout(ilayOutSwat);
	swatdataStride = sizeof(OBJ_VERT);
	tdContext->IASetVertexBuffers(0, 1, &swatBuffer, &swatdataStride, &swatoS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	tdContext->VSSetShader(svS, NULL, 0);
	tdContext->PSSetShader(spS, NULL, 0);

	swatindexStride = sizeof(unsigned int);
	tdContext->IASetIndexBuffer(swatindexBuff, DXGI_FORMAT_R32_UINT, 0);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	tdContext->VSSetShader(svS, NULL, 0);
	tdContext->PSSetShader(spS, NULL, 0);
	tdContext->DrawIndexed(12594, 0, 0);


	sC->Present(1, 0);
}


void DEMO_APP::Move()
{
	if (GetAsyncKeyState('W'))
	{
		XMMATRIX tMat = XMMatrixTranslation(0, 0, 1 * timer.Delta());
		m.vMat = XMMatrixMultiply(tMat, m.vMat);
	}
	if (GetAsyncKeyState('A'))
	{
		XMMATRIX tMat = XMMatrixTranslation(-1 * timer.Delta(), 0, 0);
		m.vMat = XMMatrixMultiply(tMat, m.vMat);
	}
	if (GetAsyncKeyState('S'))
	{
		XMMATRIX tMat = XMMatrixTranslation(0, 0, -1 * timer.Delta());
		m.vMat = XMMatrixMultiply(tMat, m.vMat);
	}
	if (GetAsyncKeyState('D'))
	{
		XMMATRIX tMat = XMMatrixTranslation(1 * timer.Delta(), 0, 0);
		m.vMat = XMMatrixMultiply(tMat, m.vMat);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		float rtX = XMConvertToRadians(-1.0f);
		XMMATRIX tMat = XMMatrixRotationY(rtX);
		XMVECTOR temp = m.vMat.r[3];
		m.vMat.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		m.vMat = XMMatrixMultiply(m.vMat, tMat);
		m.vMat.r[3] = temp;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		float rtX = XMConvertToRadians(1.0f);
		XMMATRIX tMat = XMMatrixRotationY(rtX);
		XMVECTOR temp = m.vMat.r[3];
		m.vMat.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		m.vMat = XMMatrixMultiply(m.vMat, tMat);
		m.vMat.r[3] = temp;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		float rtX = XMConvertToRadians(-1.0f);
		XMMATRIX tMat = XMMatrixRotationX(rtX);
		m.vMat = XMMatrixMultiply(tMat, m.vMat);
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		float rtX = XMConvertToRadians(1.0f);
		XMMATRIX tMat = XMMatrixRotationX(rtX);
		m.vMat = XMMatrixMultiply(tMat, m.vMat);
	}
}

//void DEMO_APP::Zoom()
//{
//	if (GetAsyncKeyState('I'))
//	{
//		XMMATRIX tmat = XMMatrixTranslation(0.0f, 0.0f, )
//	}
//}

//************************************************************
//************ DESTRUCTION ***********************************
//************************************************************

bool DEMO_APP::ShutDown()
{
	//release the kraken(stuff)
	sC->Release();
	rtV->Release();
	tDev->Release();
	tdContext->Release();
	pS->Release();
	vS->Release();
	ilayOut->Release();
	ilayOutSwat->Release();
	Dsv->Release();
	texture->Release();
	
	UnregisterClass( L"DirectXApplication", application ); 
	return true;
}



//************************************************************
//************ WINDOWS RELATED *******************************
//************************************************************

// ****************** BEGIN WARNING ***********************// 
// WINDOWS CODE, I DON'T TEACH THIS YOU MUST KNOW IT ALREADY!
	
//shutting down everything
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,	int nCmdShow );						   
LRESULT CALLBACK WndProc(HWND hWnd,	UINT message, WPARAM wparam, LPARAM lparam );		
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
	srand(unsigned int(time(0)));
	DEMO_APP myApp(hInstance,(WNDPROC)WndProc);	
    MSG msg; ZeroMemory( &msg, sizeof( msg ) );
    while ( msg.message != WM_QUIT && myApp.Run() )
    {	
	    if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        { 
            TranslateMessage( &msg );
            DispatchMessage( &msg ); 
        }
    }
	myApp.ShutDown(); 
	return 0; 
}
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    if(GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;
    switch ( message )
    {
        case ( WM_DESTROY ): { PostQuitMessage( 0 ); }
        break;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}
//********************* END WARNING ************************//