#pragma once

#include "EngineInfo.h"

class CDevice
{
private:
	ID3D11Device* m_Device; //������� �� �ڿ��Ҵ������ ���̴� ����̽� �������̽�
	ID3D11DeviceContext* m_Context;// ���� ����� �����ϰ� �ڿ��� ���Ķ� ���� GPU�� ������ ������ ��ɵ��� �����ϴµ� ����
	IDXGISwapChain* m_SwapChain; //ȭ���� ǥ�����ִ� ����ü��

	ID3D11RenderTargetView* m_TargetView; //����Ÿ�ٺ�
	ID3D11DepthStencilView* m_DepthView; // ���� ��

	HWND m_hWnd; //������ �ڵ� ����
	Resolution m_RS; //�ػ�

	//d2d���� Ÿ��, 1004���� ����
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

	//�ػ� ���� ����(���� 3d������ ����ϱ� ���� �뵵)
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

