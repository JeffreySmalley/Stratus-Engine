#ifndef _WINDOWCLASS_H_
#define _WINDOWCLASS_H_

#pragma once
#include <windows.h>

class WindowClass
{
public:

	WindowClass();
	~WindowClass();
	int Initilize(WNDPROC proc);
	int NewWindow(int height, int width, LPCWSTR title, LPCWSTR windowClassName);
	void ActivateWindow();
	HWND GetHWnd() { return m_hWnd; }
	void ResizeWindow(int height, int width);
	void ClipMouse(bool clip);
	void HideMouse(bool hide);
	enum Mode;
	void ChangeWindowMode(Mode mode);
	void ChangeWindowMode(Mode mode, int height, int width);
	void Shutdown();
	enum Mode
	{
		BORDERLESS, FULLSCREEN, WINDOWED
	};
private:
	int HandleCurrentMode(Mode newMode);

	Mode m_currentMode;
	HWND m_hWnd;
	HINSTANCE m_hInst;
	LPCWSTR m_className;
	RECT oldClip;
	bool cursorIsClipped = false;
};

#endif // !_WINDOWCLASS_H_