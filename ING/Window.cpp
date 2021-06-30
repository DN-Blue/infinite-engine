#include "Window.h"
#include <iostream>
#include "ING.h"

using namespace Infinite;



Window::Window():
	pING(0) 
{

}

Window::~Window() {

}








LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	Window* pWindow;

	if (msg == WM_CREATE) {
		pWindow = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)pWindow);
		pWindow->OnCreate();
	}
	else {
		pWindow = (Window*)GetWindowLong(hwnd, GWL_USERDATA);

	}


	switch (msg)
	{
	case WM_CREATE:
	{
		
		break;
	}

	case WM_DESTROY:
	{
		pWindow->OnDestroy();
		pWindow->isRunning = false;
		::PostQuitMessage(0);
		break;
	}


	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}


bool Window::ThisCreateWindow() {
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"INGWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;

	hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"INGWindowClass", name,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, clientWidth, clientHeight,
		NULL, NULL, NULL, this);

	if (!hwnd)
		return false;


	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	isRunning = true;
	return true;
}


bool Window::Init() {

	if (!(this->ThisCreateWindow())) {
		return false;
	}

	return true;
}



void Window::OnCreate() {

}

void Window::OnUpdate() {

}


void  Window::OnDestroy() {
	isRunning = false;
}

void Window::OnResize() {
	//pING->pGraphics->SetScreenSize();
}

void Window::Boardcast() {
	MSG msg;

	this->OnUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
}