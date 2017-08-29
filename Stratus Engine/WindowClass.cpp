#include "WindowClass.h"

#include "resource.h"

WindowClass::WindowClass()
{
}


WindowClass::~WindowClass()
{
}

int WindowClass::Initilize(WNDPROC proc)
{
	GetClipCursor(&oldClip);
	m_currentMode = WINDOWED;
	WNDCLASSEX winClass;
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.hInstance = m_hInst = GetModuleHandle(NULL);
	winClass.lpfnWndProc = proc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.style = CS_HREDRAW | CS_VREDRAW| CS_OWNDC;
	winClass.hIcon = LoadIcon(winClass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	winClass.hIconSm = winClass.hIcon;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = m_className = L"Stratus Engine";
	

	if (!RegisterClassEx(&winClass))
	{
		MessageBox(NULL, L"Window class failed!", L"Stratus Engine Failure", MB_ICONERROR | MB_OK);
		return 1;
	}
	
	return 0;
}

int WindowClass::NewWindow(int height, int width, LPCWSTR title, LPCWSTR windowClassName)
{
	int posX, posY;
	posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, windowClassName, title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, width, height, NULL, NULL, m_hInst, NULL);
	if (!m_hWnd)
	{
		MessageBox(NULL, L"Failed to create window", L"Stratus Engine Failure", MB_ICONERROR | MB_OK);
		return 2;
	}
	return 0;
}

void WindowClass::ActivateWindow()
{
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void WindowClass::ResizeWindow(int height, int width)
{
	SetWindowPos(m_hWnd, NULL, 0, 0, width, height, SWP_NOMOVE);
}

void WindowClass::ClipMouse(bool clip)
{
	if (clip)
	{
		SetCapture(m_hWnd);
		RECT clipBox;
		GetClientRect(m_hWnd, &clipBox);
		ClipCursor(&clipBox);
		cursorIsClipped = true;
	}
	else
	{
		ReleaseCapture();
		ClipCursor(&oldClip);
		cursorIsClipped = false;
	}
}

void WindowClass::HideMouse(bool hide)
{
	if (hide)
	{
		ShowCursor(false);
	}
	else
	{
		ShowCursor(true);
	}
}

void WindowClass::ChangeWindowMode(Mode mode)
{
	switch (mode)
	{
	case BORDERLESS:
		if (HandleCurrentMode(mode)== 0)
		{
			int width = GetSystemMetrics(SM_CXSCREEN);
			int height = GetSystemMetrics(SM_CYSCREEN);
			MoveWindow(m_hWnd, 0, 0, width, height, true);
			SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP);
			ShowWindow(m_hWnd, SW_SHOW);
			m_currentMode = BORDERLESS;
			if (cursorIsClipped)
			{
				SetCapture(m_hWnd);
				RECT clipBox;
				GetClientRect(m_hWnd, &clipBox);
				ClipCursor(&clipBox);
			}
		}
		break;
	case FULLSCREEN:
		if (HandleCurrentMode(mode) == 0)
		{
			int width = GetSystemMetrics(SM_CXSCREEN);
			int height = GetSystemMetrics(SM_CYSCREEN);
		}
		break;
	}
}

void WindowClass::ChangeWindowMode(Mode mode, int height, int width)
{
	switch (mode)
	{
	case WINDOWED:
		if (HandleCurrentMode(mode) == 0)
		{
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);
			MoveWindow(m_hWnd, 0, 0, width, height, true);
			RECT winRect;
			winRect.top = 0;
			winRect.left = 0;
			winRect.bottom = height;
			winRect.right = width;
			AdjustWindowRectEx(&winRect, WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, NULL, NULL);
			MoveWindow(m_hWnd,(screenWidth-width/2), (screenHeight-height)/2, width, height, true);
			SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP);
			ShowWindow(m_hWnd, SW_SHOW);
			m_currentMode = WINDOWED;
			if (cursorIsClipped)
			{
				SetCapture(m_hWnd);
				RECT clipBox;
				GetClientRect(m_hWnd, &clipBox);
				ClipCursor(&clipBox);
			}
		}
		break;
	}
}

int WindowClass::HandleCurrentMode(Mode mode)
{
	if (mode == m_currentMode && mode != WINDOWED)
	{
		return 1;
	}
	if (m_currentMode == FULLSCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
		return 0;
	}
	return 0;
}

void WindowClass::Shutdown()
{
	ShowCursor(true);
	ClipCursor(&oldClip);

	if (m_currentMode == FULLSCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	UnregisterClass(m_className, m_hInst);
	
	m_hInst = NULL;
}