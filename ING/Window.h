#ifndef  WINDOW_H
#define WINDOW_H

#include "INGLib.h"



namespace Infinite {

	class ING;

	class Window {

	public:
		Window();
		~Window();

	public:
		bool Init();

	public:
		ING* pING;

	public:
		UINT clientWidth;
		UINT clientHeight;
		LPCWSTR name;
		HWND hwnd;
		bool isRunning;


	public:
		bool ThisCreateWindow();

	public:
		void OnCreate();
		void OnUpdate();
		void OnDestroy();
		void OnResize();

	public:
		void Boardcast();

	};

};


#endif
