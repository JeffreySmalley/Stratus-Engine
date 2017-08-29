#include "EngineClass.h"


EngineClass::EngineClass()
{
}


EngineClass::~EngineClass()
{
}

int EngineClass::Initilize()
{
	AppHandle = this;
	m_window = new WindowClass;
	m_window->Initilize(WndProc);
	return 0;
}

void EngineClass::update()
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
void EngineClass::Shutdown()
{
	m_window->Shutdown();
	
	delete m_window;
	m_window = nullptr;
	AppHandle = nullptr;
}