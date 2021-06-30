#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H

#include "INGLib.h"

namespace Infinite {

	class ING;

	class Graphics;

	class SwapChain {

	public:
		SwapChain();
		~SwapChain();

	public:
		Graphics* pGraphics;

	public:
		ID3D11RenderTargetView* pRenderTargetView;
		ID3D11DepthStencilView* pDepthStencilView;

	public:
		bool Init();

	public:
		UINT clientWidth;
		UINT clientHeight;
		HWND hwnd;


	public:
		IDXGISwapChain* pSwapChain;

	public:
		void Resize(UINT width, UINT height);
		void Present();

	};

}


#endif