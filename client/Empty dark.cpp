//--------------------------------------------------------------------------------------
// File: Empty dark.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "Home.h"

CTexture* g_pTexture = NULL;//텍스쳐 객체
CSprite* g_pSprite = NULL;//스프라이트 객체
CCamera* g_pCamera = NULL;//카메라 객체
CGameObjPool* g_pGameObjPool = NULL;//게임오브젝트 객체
CGameObjMgr* g_pGameObjMgr = NULL;//게임오브젝트매니저 객체
CUIMgr* g_pUIMgr = NULL;//ui매니저 객체
CGameStage* g_pStage = NULL;//스테이지 객체
CGameFontMgr * g_pGameFontMgr = NULL;//게임폰트매니저 객체
CMouse* g_pMouse = NULL;//마우스 객체
CDebug* g_pDebug = NULL;//디버그 객체
CGameTileMgr* g_pGameTileMgr = NULL;//게임타일매니저 객체

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{

	//#include <float.h>
 //
	//int cw = _controlfp( 0, 0 );
	//cw &=~EM_ZERODIVIDE;
	//_controlfp( cw, MCW_EM );

	
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	g_pTexture = new CTexture;
	g_pSprite = new CSprite;
	g_pGameObjPool = new CGameObjPool;
	g_pGameObjMgr = new CGameObjMgr;
	g_pGameFontMgr = new CGameFontMgr;
	g_pUIMgr = new CUIMgr;

	g_pMouse = new CMouse;
	
	g_pStage = new CGameStage;
	g_pStage->Load();

	g_pCamera = new CCamera;
	
	g_pDebug = new CDebug;

	CAniEvent::m_pfEventFunc = OnAniEvent;
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
	g_pSprite->OnResetDevice();
	g_pCamera->InitSize( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	g_pCamera->OnFrameMove( fElapsedTime );
	g_pMouse->OnFrameMove( fElapsedTime );
	g_pStage->OnFrameMove( fElapsedTime );
	g_pGameObjMgr->OnFrameMove( fElapsedTime );
	g_pDebug->OnFrameMove( fElapsedTime );
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );
			pd3dDevice->SetRenderState( D3DRS_ZENABLE, false );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		g_pSprite->OnBegin();
		g_pGameObjMgr->OnFrameRender();
		g_pSprite->OnEnd();
		g_pGameFontMgr->OnFrameRender();
        V( pd3dDevice->EndScene() );
    }
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
	g_pSprite->OnLostDevice();
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	SAFE_DELETE( g_pGameFontMgr );
	SAFE_DELETE( g_pGameObjMgr );
	SAFE_DELETE( g_pGameObjPool );
	SAFE_DELETE( g_pTexture );
	SAFE_DELETE( g_pCamera );
	SAFE_DELETE( g_pSprite );
}


//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // TODO: Perform any application-level initialization here

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"Empty dark" );
    DXUTCreateDevice( true, 1024, 768 );

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


