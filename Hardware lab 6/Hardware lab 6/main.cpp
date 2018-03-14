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
#include <algorithm>
#include "XTime.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <D3D11.h>
#include "injuredswatdude.h"
#include "broken pillar.h"
//#include "InjuredSWAT.h"
//#include "blood.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

#pragma comment(lib, "d3d11.lib")

#include "Trivial_PS.csh"
#include "Trivial_VS.csh"
#include "swatShader.csh"
#include "swatPShader.csh"
#include "pillarPShader.csh"
#include "pillarVShader.csh"
#include "gridpShader.csh"
#include "gridVShader.csh"
#include "GeometryShader.csh"
#include "swatShaderI10.csh"

#define BACKBUFFER_WIDTH	900
#define BACKBUFFER_HEIGHT	700
//#define gore blood_pixels

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
	ID3D11InputLayout *ilayOutPillar;
	ID3D11InputLayout *ilayOutGrid;

	//vertex buffer descriptions
	D3D11_BUFFER_DESC gbDesc;
	D3D11_BUFFER_DESC vbDesc;
	D3D11_BUFFER_DESC vbDesc2;
	D3D11_BUFFER_DESC lvbuffDesc;
	D3D11_BUFFER_DESC swatbuffDesc;
	D3D11_BUFFER_DESC swatindexbuffDesc;
	D3D11_BUFFER_DESC swattextbuffDesc;
	D3D11_BUFFER_DESC pillarbuffDesc;
	D3D11_BUFFER_DESC pillarindexbuffDesc;
	D3D11_BUFFER_DESC pillartextbuffDesc;
	D3D11_BUFFER_DESC PLightbuffDesc;
	D3D11_BUFFER_DESC SLightbuffDesc;
	D3D11_BUFFER_DESC PbuffDesc;
	D3D11_BUFFER_DESC GSbuffDesc;
	D3D11_BUFFER_DESC ibDesc;

	//subresource data
	D3D11_SUBRESOURCE_DATA srData;

	//vertex buffers
	ID3D11Buffer *vB;
	ID3D11Buffer *gB;
	ID3D11Buffer *lvBuff;
	ID3D11Buffer *vBuff2;
	ID3D11Buffer *swatBuffer;
	ID3D11Buffer *swatindexBuff;
	ID3D11Buffer *swattextBuff;
	ID3D11Buffer *pillarBuff;
	ID3D11Buffer *pillarindexBuff;
	ID3D11Buffer *pillartextBuff;
	ID3D11Buffer *PlvBuff;
	ID3D11Buffer *SlvBuff;
	ID3D11Buffer *PvBuff;
	ID3D11Buffer *gseBuff;
	ID3D11Buffer *iBuff;
	

	//strides
	UINT stride, gS, lStride, swatdataStride, swatindexStride, pillardataStride, pillarindexStride, pStride, gseStride; 

	//offsets
	UINT oS = 0.0f;
	UINT goS = 0.0f;
	UINT loS = 0.0f;
	UINT swatoS = 0.0f;
	UINT pillaroS = 0.0f;
	UINT poS = 0.0f;
	UINT gseoS = 0.0f;

	//shaders
	ID3D11PixelShader *pS;
	ID3D11VertexShader *vS;
	ID3D11VertexShader *svS;
	ID3D11PixelShader *spS;
	ID3D11VertexShader *pvS;
	ID3D11PixelShader *ppS;
	ID3D11PixelShader *gpS;
	ID3D11VertexShader *gvS;
	ID3D11GeometryShader *gsS;
	ID3D11VertexShader *ssI10;

	//mapped subresource
	D3D11_MAPPED_SUBRESOURCE mappedsubRe;

	//STUFF REQUIRED FOR TEXTURING
	D3D11_SAMPLER_DESC sampDesc;
	ID3D11SamplerState *sampState;
	D3D11_SAMPLER_DESC SBsampdesc;
	ID3D11SamplerState *SBsampState;
	ID3D11ShaderResourceView *srV;
	ID3D11ShaderResourceView *SBsrV;
	ID3D11Texture2D *texture;
	ID3D11Texture2D *SBtext;
	D3D11_SAMPLER_DESC PsampDesc;
	ID3D11SamplerState *PsampState;
	ID3D11ShaderResourceView *PsrV;
	ID3D11Texture2D *Ptext;
	D3D11_TEXTURE2D_DESC textDesc;
	//

	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ID3D11DepthStencilState *dsState;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ID3D11DepthStencilView *Dsv;
	ID3D11BlendState *bState;
	D3D11_BLEND_DESC bsDesc;
	D3D11_RASTERIZER_DESC rastDesc;
	ID3D11RasterizerState *rState;


	float degVal = XMConvertToRadians(90.0f);
	
	
	struct Vert
	{
		XMFLOAT4 pos;
	};

	/*struct Instance
	{
		XMFLOAT4 pos;
	};*/

	struct DLight
	{
		XMFLOAT4 position;
		XMFLOAT4 color;
		XMFLOAT4 direction;
	};

	struct PLight
	{
		XMFLOAT4 pos, col, dir;
	};

	struct SLight
	{
		XMFLOAT4 sPos, sCol;
		XMFLOAT3 sDir;
		float inner;
		XMFLOAT3 cDir;
		float outter;
		XMFLOAT3 padding;
		float fallOff;
	};

	struct Matrices
	{
		XMMATRIX CUBEworldMat, SWATworldmat, PILLARworldMat, perspectiveMat, vMat;
	}; Matrices m;

	struct instanceMats
	{
		XMMATRIX CUBEworldMat, SWATworldmat[2], PILLARworldMat, perspectiveMat, vMat;
	}; instanceMats im;

	Vert simpVerts[36];
	Vert grid[44];
	DLight dlight;
	PLight pLight;
	SLight sLight;
	OBJ_VERT swat;
	OBJ_VERT plane[6];
	OBJ_VERT GSVertex[2];
	//OBJ_VERT pillar;


	DEMO_APP(HINSTANCE hinst, WNDPROC proc);
	bool Run();
	void Render();
	void Move();
	void resize();
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

	window = CreateWindow(	L"DirectXApplication", L"P&P4 Scene",	WS_OVERLAPPEDWINDOW /*& ~(WS_THICKFRAME|WS_MAXIMIZEBOX)*/, 
							CW_USEDEFAULT, CW_USEDEFAULT, window_size.right-window_size.left, window_size.bottom-window_size.top,					
							NULL, NULL,	application, this );												

    ShowWindow( window, SW_SHOW );
	//********************* END WARNING ************************//
	

#pragma region Cube
	//top face
	simpVerts[5].pos = XMFLOAT4(-0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[4].pos = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[3].pos = XMFLOAT4(0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[2].pos = XMFLOAT4(-0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[1].pos = XMFLOAT4(0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[0].pos = XMFLOAT4(-0.25f, 0.25f, -0.25f, 1.0f);

	//front face
	simpVerts[11].pos = XMFLOAT4(-0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[10].pos = XMFLOAT4(0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[9].pos = XMFLOAT4(0.25f, -0.25f, -0.25f, 1.0f);
	simpVerts[8].pos = XMFLOAT4(-0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[7].pos = XMFLOAT4(0.25f, -0.25f, -0.25f, 1.0f);
	simpVerts[6].pos = XMFLOAT4(-0.25f, -0.25f, -0.25f, 1.0f);

	////left face
	simpVerts[17].pos = XMFLOAT4(-0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[16].pos = XMFLOAT4(-0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[15].pos = XMFLOAT4(-0.25f, -0.25f, -0.25f, 1.0f);
	simpVerts[14].pos = XMFLOAT4(-0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[13].pos = XMFLOAT4(-0.25f, -0.25f, -0.25f, 1.0f);
	simpVerts[12].pos = XMFLOAT4(-0.25f, -0.25f, 0.25f, 1.0f);

	////back face
	simpVerts[23].pos = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[22].pos = XMFLOAT4(-0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[21].pos = XMFLOAT4(-0.25f, -0.25f, 0.25f, 1.0f);
	simpVerts[20].pos = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[19].pos = XMFLOAT4(-0.25f, -0.25f, 0.25f, 1.0f);
	simpVerts[18].pos = XMFLOAT4(0.25f, -0.25f, 0.25f, 1.0f);

	////right face
	simpVerts[29].pos = XMFLOAT4(0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[28].pos = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	simpVerts[27].pos = XMFLOAT4(0.25f, -0.25f, 0.25f, 1.0f);
	simpVerts[26].pos = XMFLOAT4(0.25f, 0.25f, -0.25f, 1.0f);
	simpVerts[25].pos = XMFLOAT4(0.25f, -0.25f, 0.25f, 1.0f);
	simpVerts[24].pos = XMFLOAT4(0.25f, -0.25f, -0.25f, 1.0f);

	////bottom face
	simpVerts[30].pos = XMFLOAT4(-0.25f, -0.25f, 0.25f, 1.0f);
	simpVerts[31].pos = XMFLOAT4(0.25f, -0.25f, 0.25f, 1.0f);
	simpVerts[32].pos = XMFLOAT4(0.25f, -0.25f, -0.25f, 1.0f);
	simpVerts[33].pos = XMFLOAT4(-0.25f, -0.25f, 0.25f, 1.0f);
	simpVerts[34].pos = XMFLOAT4(0.25f, -0.25f, -0.25f, 1.0f);
	simpVerts[35].pos = XMFLOAT4(-0.25f, -0.25f, -0.25f, 1.0f);
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

#pragma region Directional Light
	dlight.position = XMFLOAT4(0.75f, 0.75f, 0.75f, 1.0f);
	dlight.color = XMFLOAT4(1.0f, 0.75f, 0.25f, 1.0f);
	dlight.direction = XMFLOAT4(-0.25f, -0.25f, -0.25f, 1.0f);
#pragma endregion light stuff

#pragma region Point Light
	pLight.pos = XMFLOAT4(-0.75f, 0.25f, 0.0f, 1.0f);
	pLight.col = XMFLOAT4(0.0f, 1.0f, 0.75f, 1.0f);
	pLight.dir = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
#pragma endregion stuff for Point light

#pragma region Spot Light
	sLight.sPos = XMFLOAT4(0.0F, 1.0F, 0.0f, 1.0f);
	sLight.sCol = XMFLOAT4(0.25f, 1.0f, 0.17f, 0.0f);
	sLight.sDir = XMFLOAT3(0.0f, -1.0f, 0.0f);
	sLight.cDir = XMFLOAT3(0.0f, -1.0f, 0.0f);
	sLight.inner = XMConvertToRadians(20.0f);
	sLight.outter = XMConvertToRadians(40.0f);
	sLight.fallOff = 1.0f;
#pragma endregion stuff for Spot light

#pragma region PLane
	float size = 100.0f;
	plane[0] = { size, 0.0f, size, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 };

	plane[1] = { -size, 0.0f, -size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	plane[2] = { -size, 0.0f, size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};

	plane[3] = { size, 0.0f, size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};

	plane[4] = { size, 0.0f, -size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};

	plane[5] = { -size, 0.0f, -size, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
#pragma endregion making plane

#pragma region Geometry Shader test
	GSVertex[0] = { -25.0f, 0.0f, -25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f};
	GSVertex[1] = { -23.0f, 0.0f, -25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f};
#pragma endregion test for the geometry shader

#pragma region depth stencil and swapchain
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

	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	tDev->CreateDepthStencilView(texture, &dsvDesc, &Dsv);
#pragma endregion depth stencil and swapchain

	

#pragma region viewport
	vP.Width = (float)BACKBUFFER_WIDTH;
	vP.Height = (float)BACKBUFFER_HEIGHT;
	vP.MinDepth = 0.0f;
	vP.MaxDepth = 1.0f;
	vP.TopLeftX = 0.0f;
	vP.TopLeftY = 0.0f;
	tdContext->RSSetViewports(1, &vP);
#pragma endregion setting up the viewport

	D3D11_INPUT_ELEMENT_DESC layOut[] =
	{ {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
	};
	UINT numofElements = ARRAYSIZE(layOut);

	tDev->CreateInputLayout(layOut, numofElements, Trivial_VS, sizeof(Trivial_VS), &ilayOut);

	D3D11_INPUT_ELEMENT_DESC swatlayOut[] = 
	{
		{"LOCATION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numofelements2 = ARRAYSIZE(swatlayOut);
	tDev->CreateInputLayout(swatlayOut, numofelements2, swatShader, sizeof(swatShader), &ilayOutSwat);

	D3D11_INPUT_ELEMENT_DESC pillarlayOut[] =
	{
		{"LOCATION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMALS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numofElements3 = ARRAYSIZE(pillarlayOut);
	tDev->CreateInputLayout(pillarlayOut, numofElements3, pillarVShader, sizeof(pillarVShader), &ilayOutPillar);

	D3D11_INPUT_ELEMENT_DESC gridlayOut[] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numofelementsGRID = ARRAYSIZE(gridlayOut);
	tDev->CreateInputLayout(gridlayOut, numofelementsGRID, gridVShader, sizeof(gridVShader), &ilayOutGrid);


	OBJ_VERT swatverts[3119];
	unsigned int indices[12595];

	for (unsigned int i = 0; i < 3119; i++)
	{
		swatverts[i] = injuredswatdude_data[i];
		swatverts[i].pos[0] = -swatverts[i].pos[0];
		swatverts[i].nrm[0] = -swatverts[i].nrm[0];
	}
	for (unsigned int i = 0; i < 12595; i++)
		indices[i] = injuredswatdude_indicies[i];
	for (unsigned int i = 0; i < 12595; i += 3)
		std::swap(indices[i + 1], indices[i + 2]);

	OBJ_VERT pillarverts[1418];
	unsigned int pillarindices[2322];
	for (unsigned int i = 0; i < 1418; ++i)
	{
		pillarverts[i] = broken_pillar_data[i];
		pillarverts[i].pos[0] = -pillarverts[i].pos[0];
		pillarverts[i].nrm[0] = -pillarverts[i].nrm[0];
	}
	for (unsigned int i = 0; i < 2322; ++i)
		pillarindices[i] = broken_pillar_indicies[i];
	for (unsigned int i = 0; i < 2322; i += 3)
		std::swap(pillarindices[i + 1], pillarindices[i + 2]);


#pragma region Buffers and buffer descs
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
	srData.pSysMem = swatverts;
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
	srData.pSysMem = indices;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&swatindexbuffDesc, &srData, &swatindexBuff);

	ZeroMemory(&lvbuffDesc, sizeof(lvbuffDesc));
	lvbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	lvbuffDesc.ByteWidth = sizeof(DLight);
	lvbuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; 
	lvbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lvbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = &dlight;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&lvbuffDesc, &srData, &lvBuff);

	ZeroMemory(&PLightbuffDesc, sizeof(PLightbuffDesc));
	PLightbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	PLightbuffDesc.ByteWidth = sizeof(PLight);
	PLightbuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	PLightbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	PLightbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = &pLight;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&PLightbuffDesc, &srData, &PlvBuff);

	ZeroMemory(&pillarbuffDesc, sizeof(pillarbuffDesc));
	pillarbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	pillarbuffDesc.ByteWidth = sizeof(OBJ_VERT) * 1418;
	pillarbuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	pillarbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pillarbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = pillarverts;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&pillarbuffDesc, &srData, &pillarBuff);

	ZeroMemory(&pillarindexbuffDesc, sizeof(pillarindexbuffDesc));
	pillarindexbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	pillarindexbuffDesc.ByteWidth = sizeof(unsigned int) * 2322;
	pillarindexbuffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	pillarindexbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pillarindexbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = pillarindices;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&pillarindexbuffDesc, &srData, &pillarindexBuff);

	ZeroMemory(&SLightbuffDesc, sizeof(SLightbuffDesc));
	SLightbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	SLightbuffDesc.ByteWidth = sizeof(SLight);
	SLightbuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	SLightbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	SLightbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = &sLight;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&SLightbuffDesc, &srData, &SlvBuff);

	ZeroMemory(&PbuffDesc, sizeof(PbuffDesc));
	PbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	PbuffDesc.ByteWidth = sizeof(OBJ_VERT) * ARRAYSIZE(plane);
	PbuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	PbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	PbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = plane;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&PbuffDesc, &srData, &PvBuff);

	ZeroMemory(&ibDesc, sizeof(ibDesc));
	ibDesc.Usage = D3D11_USAGE_DYNAMIC;
	ibDesc.ByteWidth = sizeof(im);
	ibDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ibDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = &im;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&ibDesc, &srData, &iBuff);

	//BUFFER FOR INSTANCING
	ZeroMemory(&GSbuffDesc, sizeof(GSbuffDesc));
	GSbuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	GSbuffDesc.ByteWidth = sizeof(OBJ_VERT);
	GSbuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	GSbuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GSbuffDesc.MiscFlags = 0;

	ZeroMemory(&srData, sizeof(srData));
	srData.pSysMem = GSVertex;
	srData.SysMemPitch = 0;
	srData.SysMemSlicePitch = 0;
	tDev->CreateBuffer(&GSbuffDesc, &srData, &gseBuff);
	

	//sample description for swat soldier texture
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	tDev->CreateSamplerState(&sampDesc, &sampState);

	//sample description for skybox (possibly not needed)
	ZeroMemory(&SBsampdesc, sizeof(SBsampdesc));
	SBsampdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SBsampdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SBsampdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SBsampdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SBsampdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SBsampdesc.MinLOD = 0;
	SBsampdesc.MaxLOD = D3D11_FLOAT32_MAX;
	tDev->CreateSamplerState(&SBsampdesc, &SBsampState);

	ZeroMemory(&PsampDesc, sizeof(PsampDesc));
	PsampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	PsampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	PsampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	PsampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	PsampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	PsampDesc.MinLOD = 0;
	PsampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	tDev->CreateSamplerState(&PsampDesc, &PsampState);

#pragma endregion filling out buffer descs and creating buffers



#pragma region Shader resources and Samplers
	tdContext->PSSetShaderResources(0, 1, &srV);
	tdContext->PSSetShaderResources(0, 1, &SBsrV);
	tdContext->PSSetShaderResources(0, 1, &PsrV);
	tdContext->PSSetSamplers(0, 1, &sampState);
	tdContext->PSSetSamplers(1, 1, &SBsampState);
	tdContext->PSSetSamplers(2, 1, &PsampState);


#pragma endregion setting sampler states and shader resources

	//setting the initial position for the camera
	float rtX = XMConvertToRadians(32.0f);
	m.vMat = XMMatrixMultiply(XMMatrixTranslation(0, 0, -5), XMMatrixRotationX(rtX));
	m.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 1000.0f);
	m.CUBEworldMat = XMMatrixIdentity();
	m.PILLARworldMat = XMMatrixIdentity();
	m.PILLARworldMat = XMMatrixTranslation(-5.0f, 0, 0);
	m.SWATworldmat = XMMatrixIdentity();
	im.SWATworldmat[0] = XMMatrixIdentity();
	im.SWATworldmat[1] = XMMatrixTranslation(5.0f, 0.0f, 0.0f);
	im.vMat = XMMatrixMultiply(XMMatrixTranslation(0, 0, -5), XMMatrixRotationX(rtX));
	im.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 1000.0f);
	//m.GRIDworldMat = XMMatrixIdentity();

	//loading texture
	CreateDDSTextureFromFile(tDev, L"swat_D.dds", (ID3D11Resource**)&texture, &srV, 0);
	CreateDDSTextureFromFile(tDev, L"OutputCube.dds", (ID3D11Resource**)&SBtext, &SBsrV, 0);
	CreateDDSTextureFromFile(tDev, L"heavenpillar_d.dds", (ID3D11Resource**)&Ptext, &PsrV, 0);
	
	
	//creating pixel shaders
	tDev->CreatePixelShader(Trivial_PS, sizeof(Trivial_PS), NULL, &pS);
	tDev->CreatePixelShader(swatPShader, sizeof(swatPShader), NULL, &spS);
	tDev->CreatePixelShader(pillarPShader, sizeof(pillarPShader), NULL, &ppS);
	//tDev->CreatePixelShader(gridPShader, sizeof(gridPShader), NULL, &gpS);

	//creating vertex shaders
	tDev->CreateVertexShader(Trivial_VS, sizeof(Trivial_VS), NULL, &vS);
	tDev->CreateVertexShader(swatShader, sizeof(swatShader), NULL, &svS);
	tDev->CreateVertexShader(pillarVShader, sizeof(pillarVShader), NULL, &pvS);
	tDev->CreateVertexShader(swatShaderI10, sizeof(swatShaderI10), NULL, &ssI10);
	//tDev->CreateVertexShader(gridVShader, sizeof(gridVShader), NULL, &gvS);

	//creating geometry shader
	//tDev->CreateGeometryShader(GeometryShader, sizeof(GeometryShader), NULL, &gsS);
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
			//DEMO_APP::resize();
		}
	}

	return true; 
}

void DEMO_APP::Render()
{
	timer.Signal();
	tdContext->OMSetRenderTargets(1, &rtV, Dsv);
	float colors[4] = { 0.0f, 0.125f, 0.6f, 1.0f };
	tdContext->ClearRenderTargetView(rtV, colors);
	Move();
	m.CUBEworldMat.r[3] = m.vMat.r[3];


	if (GetAsyncKeyState('Z'))
	{
		DEMO_APP::degVal += XMConvertToRadians(0.5f);
		m.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 1000.0f);

		if (DEMO_APP::degVal >= XMConvertToRadians(115.0f))
		{
			DEMO_APP::degVal = XMConvertToRadians(115.0f);
			m.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 1000.0f);
		}
	}
	else if (GetAsyncKeyState('X'))
	{
		DEMO_APP::degVal -= XMConvertToRadians(0.5f);
		m.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 1000.0f);

		if (DEMO_APP::degVal <= XMConvertToRadians(45.0f))
		{
			DEMO_APP::degVal = XMConvertToRadians(45.0f);
			m.perspectiveMat = XMMatrixPerspectiveFovLH(DEMO_APP::degVal, 1, .1, 1000.0f);
		}
	}

	//changing direction of directional light
	if (GetAsyncKeyState('J'))
		dlight.direction.x += 0.1f;
	else if (GetAsyncKeyState('K'))
		dlight.direction.x -= 0.1f;

	//changing position of point light
	if (GetAsyncKeyState('V'))
		pLight.pos.y += 0.1f;
	else if (GetAsyncKeyState('B'))
		pLight.pos.y -= 0.1f;

	//changing position of spot light
	if (GetAsyncKeyState('T'))
		sLight.sPos.x -= 0.1f;
	else if (GetAsyncKeyState('Y'))
		sLight.sPos.x += 0.1f;

	//changing the direction of the spot light
	if (GetAsyncKeyState('G'))
	{
		XMVECTOR tVec = XMLoadFloat3(&sLight.sDir);
		XMMATRIX tmat = XMMatrixRotationX(XMConvertToRadians(5.0f));
		tVec = XMVector3Transform(tVec, tmat);
		XMStoreFloat3(&sLight.sDir, tVec);
	}
	else if (GetAsyncKeyState('H'))
	{
		XMVECTOR tVec = XMLoadFloat3(&sLight.sDir);
		XMMATRIX tMat = XMMatrixRotationX(XMConvertToRadians(-5.0f));
		tVec = XMVector3Transform(tVec, tMat);
		XMStoreFloat3(&sLight.sDir, tVec);
	}
		
	m.vMat = XMMatrixInverse(nullptr, m.vMat);
	tdContext->Map(vBuff2, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedsubRe);
	memcpy(mappedsubRe.pData, &m, sizeof(m));
	tdContext->Unmap(vBuff2, NULL);
	tdContext->VSSetConstantBuffers(2, 1, &vBuff2);

	//UPDATING CONSTANT BUFFERS
	m.vMat = XMMatrixInverse(nullptr, m.vMat);
	tdContext->Map(lvBuff, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedsubRe);
	memcpy(mappedsubRe.pData, &dlight, sizeof(DLight));
	tdContext->Unmap(lvBuff, NULL);
	tdContext->PSSetConstantBuffers(2, 1, &lvBuff);

	tdContext->Map(PlvBuff, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedsubRe);
	memcpy(mappedsubRe.pData, &pLight, sizeof(PLight));
	tdContext->Unmap(PlvBuff, NULL);
	tdContext->PSSetConstantBuffers(1, 1, &PlvBuff);

	tdContext->Map(SlvBuff, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedsubRe);
	memcpy(mappedsubRe.pData, &sLight, sizeof(SLight));
	tdContext->Unmap(SlvBuff, NULL);
	tdContext->PSSetConstantBuffers(3, 1, &SlvBuff);

	tdContext->Map(iBuff, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedsubRe);
	memcpy(mappedsubRe.pData, &im, sizeof(instanceMats));
	tdContext->Unmap(iBuff, NULL);
	tdContext->VSSetConstantBuffers(3, 1, &iBuff);
	//

	tdContext->IASetInputLayout(ilayOut);
	stride = sizeof(Vert);
	tdContext->IASetVertexBuffers(0, 1, &vB, &stride, &oS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//Triangle strip references previously used vertices, Triangle List requires all new vertices
	tdContext->VSSetShader(vS, NULL, 0);
	tdContext->PSSetShader(pS, NULL, 0);
	tdContext->PSSetShaderResources(1, 1, &SBsrV);
	tdContext->Draw(36, 0);
	tdContext->ClearDepthStencilView(Dsv, 1, 1.0f, 1); 
	

	/*tdContext->IASetInputLayout(ilayOutGrid);
	gS = sizeof(Vert);
	tdContext->IASetVertexBuffers(0, 1, &gB, &gS, &goS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	tdContext->VSSetShader(gvS, NULL, 0);
	tdContext->PSSetShader(gpS, NULL, 0);
	tdContext->Draw(44, 0);*/

	tdContext->IASetInputLayout(ilayOutSwat);
	swatdataStride = sizeof(OBJ_VERT);
	tdContext->IASetVertexBuffers(0, 1, &swatBuffer, &swatdataStride, &swatoS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	swatindexStride = sizeof(unsigned int);
	tdContext->IASetIndexBuffer(swatindexBuff, DXGI_FORMAT_R32_UINT, 0);
	tdContext->VSSetShader(svS, NULL, 0);
	tdContext->PSSetShader(spS, NULL, 0);
	//tdContext->VSSetShader(ssI10, NULL, 0);
	tdContext->PSSetShaderResources(0, 1, &srV);
	//tdContext->DrawIndexedInstanced(12594, 2, 0, 0, 0);
	tdContext->DrawIndexed(12594, 0, 0);

	pStride = sizeof(OBJ_VERT);
	tdContext->IASetVertexBuffers(0, 1, &PvBuff, &pStride, &poS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	tdContext->Draw(6, 0);

	//gseStride = sizeof(OBJ_VERT);
	//tdContext->IASetVertexBuffers(0, 1, &gseBuff, &gseStride, &gseoS);
	//tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	////tdContext->GSSetShader(gsS, NULL, 0);
	//tdContext->DrawInstanced(3, 1, 1, 0);

	tdContext->IASetInputLayout(ilayOutPillar);
	pillardataStride = sizeof(OBJ_VERT);
	tdContext->IASetVertexBuffers(0, 1, &pillarBuff, &pillardataStride, &pillaroS);
	tdContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pillarindexStride = sizeof(unsigned int);
	tdContext->IASetIndexBuffer(pillarindexBuff, DXGI_FORMAT_R32_UINT, 0);
	tdContext->VSSetShader(pvS, NULL, 0);
	tdContext->PSSetShader(ppS, NULL, 0);
	tdContext->PSSetShaderResources(0, 1, &PsrV);
	tdContext->DrawIndexed(2322, 0, 0);
	//tdContext->ClearDepthStencilView(Dsv, 1, 1, 1);

	
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

void DEMO_APP::resize()
{
	
}

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
	svS->Release();
	spS->Release();
	srV->Release();
	SBsrV->Release();
	sampState->Release();
	rState->Release();
	bState->Release();
	dsState->Release();
	SBtext->Release();
	vB->Release();
	gB->Release();
	lvBuff->Release();
	vBuff2->Release();
	swatBuffer->Release();
	swatindexBuff->Release();
	swattextBuff->Release();
	SBsampState->Release();
	ssI10->Release();
	gsS->Release();
	gvS->Release();
	gpS->Release();
	ppS->Release();
	pvS->Release();
	iBuff->Release();
	gseBuff->Release();
	PvBuff->Release();
	SlvBuff->Release();
	PlvBuff->Release();
	pillarBuff->Release();
	pillarindexBuff->Release();
	pillartextBuff->Release(); 
	ilayOutGrid->Release();
	ilayOutPillar->Release();
	
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