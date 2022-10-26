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

	//d2d렌터 타겟, 1004문서 참고
private:
	ID2D1RenderTarget* m_2DTarget;
	ID2D1RenderTarget* m_2DTargetWorld;
	ID2D1Factory* m_2DFactory;

public:
	ID2D1RenderTarget* Get2DTarget()	const
	{
		return m_2DTarget;
	}

	ID2D1RenderTarget* Get2DWorldTarget()	const
	{
		return m_2DTargetWorld;
	}

	ID2D1Factory* Get2DFactory()	const
	{
		return m_2DFactory;
	}
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

	//해상도 비율 관리(이후 3d에서도 사용하기 위한 용도)
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

