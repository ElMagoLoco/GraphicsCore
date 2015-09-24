#include "..\\D3D9Graphics\\GFX.h"
#include "..\\D3D9Graphics\\ABC.h"
#include "Test.h"
using namespace GFXCore;
using namespace GSP420;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);
	UNREFERENCED_PARAMETER(showCmd);

	if (false == GFX->initGFX(hInstance, L"test"))
		return 0;
	if (false == GFX->initModules())
		return 0;

	int m = GFX->loadModel(L"..\\GraphicsCoreTests\\Assets\\PlayerSPaceShipV2.X", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
//	GFX->cameraSetPos(D3DXVECTOR3(0.0f, 0.0f, -0.0f));
	GFX->cameraSetLens(GFX->windowWidth(), GFX->windowHeight(), -1000.0f, 1000.0f);

	Test obj1 = Test(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.20f, 1.20f, 1.20f));
	obj1.init(m, -1);
	Test obj2 = Test(D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	obj2.init(m, -1);
	Test obj3 = Test(D3DXVECTOR3(0.0f, -300.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	obj3.init(m, -1);
	Test obj4 = Test(D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	obj4.init(m, -1);
	Test obj5 = Test(D3DXVECTOR3(-400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(0.0f, -0.0f, -0.0f), D3DXVECTOR3(1.80f, 1.80f, 1.80f));
	obj5.init(m, -1);

	DirectInput di(hInstance, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDInput = &di;

	FontData newFont;
	memset(&newFont, NULL, sizeof(FontData));
	newFont.bItalics = false;
	newFont.nFontHeight = 20;
	newFont.nFontWidth = 10;
	wcscpy_s(newFont.strFontName, L"Delicious-Roman");
	newFont.textBoxDimens = { 00, 00, 300, 200 };
	newFont.textColor = D3DCOLOR_XRGB(255, 0, 0);
	
	int fontId = GFX->loadFont(newFont);
	GFX->setFont(fontId, L"This now works better!");

	memset(&newFont, NULL, sizeof(FontData));
	newFont.bItalics = false;
	newFont.nFontHeight = 20;
	newFont.nFontWidth = 10;
	wcscpy_s(newFont.strFontName, L"Delicious-Roman");
	newFont.textBoxDimens = { 300, 200, 600, 400 };
	newFont.textColor = D3DCOLOR_XRGB(0, 255, 0);
	int fontId2 = GFX->loadFont(newFont);
	GFX->setFont(fontId2, L"Second Font");
	int textIds[2];
	textIds[0] = fontId;
	textIds[1] = fontId2;

	MSG msg;
	memset(&msg, NULL, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		GFX->addToModelRenderList(&obj5);
		GFX->addToModelRenderList(&obj1);
		GFX->addToModelRenderList(&obj2);
		GFX->addToModelRenderList(&obj3);
		GFX->addToModelRenderList(&obj4);
		GFX->addToTextRenderList(textIds, 2);
		GFX->renderScene();
	}

	GFX->shutdown();

	return 0;
}