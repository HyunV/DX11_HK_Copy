#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice() :
	m_Device(nullptr),
	m_Context(nullptr),
	m_SwapChain(nullptr),
	m_TargetView(nullptr),
	m_DepthView(nullptr),
	m_RS{},
	m_hWnd(0)
{
}

CDevice::~CDevice()
{
	//������ ������: ���۷��� ī��Ʈ�� 1 ���ҽ�Ű�� nullptr�� �ʱ�ȭ
	SAFE_RELEASE(m_TargetView);
	SAFE_RELEASE(m_DepthView);
	SAFE_RELEASE(m_SwapChain);

	if (m_Context)
		m_Context->ClearState(); //���ؽ�Ʈ�� �ƹ��͵� �������� ���� ���·� �ʱ�ȭ

	SAFE_RELEASE(m_Context);
	SAFE_RELEASE(m_Device);
}

bool CDevice::Init(HWND hWnd, unsigned int DeviceWidth, unsigned int DeviceHeight,
	bool WindowMode)
{
	m_hWnd = hWnd;
	m_RS.Width = DeviceWidth;
	m_RS.Height = DeviceHeight;

	unsigned int	Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT; 
							//2D ���ҽ�, 3D���ҽ� �� �� �����ϰڴٴ� �÷���

#ifdef _DEBUG
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	//�� ���� ���: �� �����غ��� �������� �����ִ�.
	D3D_FEATURE_LEVEL	FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL	FLevelResult;

	// �� Device ����###############################################
	//0���� ������ TRUE�� FAILED ��ũ��
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0,
		Flag, &FLevel, 1, D3D11_SDK_VERSION, &m_Device, &FLevelResult,
		&m_Context)))
		return false;

	//###����ü�� ���� : ������ �ø��� �ϱ� ���� ����ؾ� �ϴ� ��, ����۵� �⺻������ ����ִ�.
	DXGI_SWAP_CHAIN_DESC SwapDesc = {}; //����ü �ʱ�ȭ

		// ������� ���� �ػ�
	SwapDesc.BufferDesc.Width = DeviceWidth;

	// ������� ���� �ػ�
	SwapDesc.BufferDesc.Height = DeviceHeight;

	// ������ �ȼ��� r, g, b, a�� 8��Ʈ�� 0 ~ 1 ������ �����÷� ���� ����Ѵ�. 0~255�� �ƴϴ�.
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //����ε� �븻(��ȣ�� ���� ����ȭ�� Ÿ��,

	SwapDesc.BufferDesc.RefreshRate.Numerator = 1; //�����ֱ� ����: 1
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60; //�����ֱ� �и�: 60
	//�ʴ� 60ȸ �ֱ�� ����

	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//ȭ�� ũ�� �ٲ� �� ������ ���ִ� �˰���, UNSPECIFIED�� ���� ��

	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	// ��ī�� �˾Ƽ� �������ش� ��
	
	SwapDesc.BufferCount = 1; //����� ���� ����, �ϴ��� �ϳ��� ���
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	//����� �����뵵�� ���ų�? = ����Ÿ������ ���Ŵ�.

	SwapDesc.OutputWindow = hWnd; //������ �׸���

	//SampleDesc: ��Ƽ���ø�(��Ƽ�ٸ�����̶� ���� ��)
	//�ٵ� ��� msaa�� ������ ���߿� ���̴��� �����ؼ� ���� į
	
	SwapDesc.SampleDesc.Quality = 0; // ����Ƽ 0~15 ���� ����
	SwapDesc.SampleDesc.Count = 1; //@������ 1������ ���߿� ���ĺ��� �� �� �þ�� 

	//���߿� �������� �������� fxaa�ڵ� ���� ����.

	SwapDesc.Windowed = WindowMode; //â���, Ǯ��ũ�� ����
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //�굵 ��ġ�� �±�ٴ°�


	//����̽�, �����, ���丮 ������ü ������ ���´�.

	IDXGIDevice* DXGIDevice = nullptr; //IDXGIDevice �� ���� ������ �ҷ��´�. ������ null
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice); //__uuidof uid
	//GUID ����Ű�� ���̵� ���������ͷ� ����ȯ�ؼ� ��Ƶ�.

	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if (FAILED(Factory->CreateSwapChain(m_Device, &SwapDesc, &m_SwapChain)))
	{
		//����ü�� ���� ���� ��
		SAFE_RELEASE(Factory);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(DXGIDevice);
		return false;
	}

	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(DXGIDevice);

	// SwapChain�� ��������ٸ� SwapChain�� ������ �ִ� BackBuffer�� ���´�.
	ID3D11Texture2D* BackBuffer = nullptr;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;

	//####����Ÿ�ٺ� ����####
	// BackBuffer�� ����� RenderTargetView�� �����Ѵ�.
	if (FAILED(m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_TargetView)))
		return false;

	SAFE_RELEASE(BackBuffer);

	//######���̹���, ���Ľ� ���� ����#####
	// ���̹��۸� �����. 0~1�� ��ü�� �� �ڸ� �Ǵ��Ѵ�.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};
	DepthDesc.Width = DeviceWidth;
	DepthDesc.Height = DeviceHeight;
	DepthDesc.ArraySize = 1; //1�� ����

	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //D24: 24��Ʈ, 8��Ʈ�� �ؼ� 3����Ʈ(R,G,B)
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //
	DepthDesc.Usage = D3D11_USAGE_DEFAULT; //���ó, ������ ��������, 7.15 �޸��� ����
	DepthDesc.SampleDesc.Count = 1;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1; //�ؽ�Ʈ ���鶧 �ٽ� ����


	//######���̹���, ���Ľ� ���� ��¥�� ����#####
	ID3D11Texture2D* DepthBuffer = nullptr;

	if (FAILED(m_Device->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	if (FAILED(m_Device->CreateDepthStencilView(DepthBuffer, nullptr, &m_DepthView)))
		return false;

	SAFE_RELEASE(DepthBuffer);

	//###�� ��Ʈ ����
	D3D11_VIEWPORT	VP = {};

	VP.Width = (float)DeviceWidth;
	VP.Height = (float)DeviceHeight;
	VP.MaxDepth = 1.f;

	m_Context->RSSetViewports(1, &VP); 

	return true;
}

void CDevice::ClearRenderTarget(float ClearColor[4])
{
	//����Ÿ�� Ŭ����(���ϴ� ������ ����۷� Ŭ���� ���ش�. ������, ��� ��������)
	m_Context->ClearRenderTargetView(m_TargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	//���� or ���ٽ� Ŭ���� ���� Ȥ�� �� ��?
	m_Context->ClearDepthStencilView(m_DepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		Depth, Stencil);
}

void CDevice::RenderStart()
{
	//����Ÿ�� �����ϰ� �ø����� �غ�
	m_Context->OMSetRenderTargets(1, &m_TargetView, m_DepthView);
}

void CDevice::Flip()
{
	m_SwapChain->Present(0, 0);
}
