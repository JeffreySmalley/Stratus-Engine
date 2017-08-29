#ifndef _ENGINECLASS_H_
#define _ENGINECLASS_H

#pragma once
#include <Windows.h>
#include "WindowClass.h"

class EngineClass
{
public:
	EngineClass();
	~EngineClass();
	int Initilize();
	void update();
	void Shutdown();
	
private:
	WindowClass* m_window;
	HWND hWnd;
};
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static EngineClass* AppHandle = nullptr;
#endif // !_ENGINECLASS_H_