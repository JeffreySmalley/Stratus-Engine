#include <Windows.h>
#include "EngineClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPSTR lpCmdLine, int nCmdShow)
{
	EngineClass* engine = new EngineClass;
	engine->Initilize();
	engine->update();
	engine->Shutdown();
	delete engine;
	engine = nullptr;
	return 0;
}