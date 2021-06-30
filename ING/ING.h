#ifndef  ING_H
#define ING_H

#include "INGLib.h"
#include <iostream>



namespace Infinite {

	class Window;

	class Graphics;

	class ResourcesManager;

	class Time;

	class ING {

	public:
		ING();
		~ING();

	public:
		Window* pWindow;
		Graphics* pGraphics;
		Time* pTime;
		ResourcesManager* pResourcesManager;

	public:
		friend class Window;
		friend class Graphics;
		friend class Time;
		friend class ResourcesManager;

	public:
		virtual bool baseInit();
		virtual bool baseRun();

	public:
		virtual void Init();
		virtual void Run();
		virtual void Update();
		virtual void Draw();

	};

};



#endif
