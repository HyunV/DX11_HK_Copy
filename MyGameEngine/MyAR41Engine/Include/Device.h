#pragma once

#include "EngineInfo.h"

class CDevice
{
private:
	ID3D11Device* m_Device; //기능점검 및 자원할당용으로 쓰이는 디바이스 인터페이스
	ID3D11DeviceContext* m_Context;// 렌더 대상을 설정하고 자원을 렌파라에 묶고 GPU가 수행할 렌더링 명령들을 지시하는데 쓰임
	IDXGISwapChain* m_SwapChain; //화면을 표시해주는 스왑체인

	ID3D11RenderTargetView* m_TargetView; //렌더타겟뷰
	ID3D11DepthStencilView* m_DepthView; // 깊이 뷰

	HWND m_hWnd; //윈도우 핸들 제어
	Resolution m_RS; //해상도

public:
	Resolution GetResolution()	const
	{
		return m_RS;
	}
	ID3D11Device* GetDevice()	const
	{
		return m_Device;
	}

	ID3D11DeviceContext* GetContext()	const
	{
		return m_Context;
	}

	IDXGISwapChain* GetSwapChain()	const
	{
		return m_SwapChain;
	}

	Vector2 GetResolutionRatio() const;

public:
	bool Init(HWND hWnd, unsigned int DeviceWidth, unsigned int DeviceHeight,
		bool WindowMode);

	void ClearRenderTarget(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void RenderStart();
	void Flip();

	DECLARE_SINGLE(CDevice)
};

