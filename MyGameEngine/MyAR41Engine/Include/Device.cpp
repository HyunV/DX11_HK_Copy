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
	//세이프 릴리즈: 레퍼런스 카운트를 1 감소시키고 nullptr로 초기화
	SAFE_RELEASE(m_TargetView);
	SAFE_RELEASE(m_DepthView);
	SAFE_RELEASE(m_SwapChain);

	if (m_Context)
		m_Context->ClearState(); //컨텍스트를 아무것도 설정하지 않은 상태로 초기화

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
							//2D 리소스, 3D리소스 둘 다 관리하겠다는 플래그

#ifdef _DEBUG
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	//쓸 버전 명시: 얘 추적해보면 버전별로 나와있다.
	D3D_FEATURE_LEVEL	FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL	FLevelResult;

	// ※ Device 생성###############################################
	//0보다 작으면 TRUE인 FAILED 매크로
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0,
		Flag, &FLevel, 1, D3D11_SDK_VERSION, &m_Device, &FLevelResult,
		&m_Context)))
		return false;

	//###스왑체인 생성 : 페이지 플립핑 하기 위해 사용해야 하는 놈, 백버퍼도 기본적으로 들고있다.
	DXGI_SWAP_CHAIN_DESC SwapDesc = {}; //구조체 초기화

		// 백버퍼의 가로 해상도
	SwapDesc.BufferDesc.Width = DeviceWidth;

	// 백버퍼의 세로 해상도
	SwapDesc.BufferDesc.Height = DeviceHeight;

	// 각각의 픽셀이 r, g, b, a에 8비트씩 0 ~ 1 사이의 선형컬러 값을 사용한다. 0~255가 아니다.
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //언사인드 노말(부호가 없는 정규화된 타입,

	SwapDesc.BufferDesc.RefreshRate.Numerator = 1; //갱신주기 분자: 1
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60; //갱신주기 분모: 60
	//초당 60회 주기로 갱신

	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//화면 크기 바뀔때 덜 깨지게 해주는 알고리즘, UNSPECIFIED로 많이 씀

	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	// 글카가 알아서 연산해준다 함
	
	SwapDesc.BufferCount = 1; //백버퍼 개수 여부, 일단은 하나면 충분
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	//백버퍼 무슨용도로 쓸거냐? = 렌더타겟으로 쓸거다.

	SwapDesc.OutputWindow = hWnd; //윈도우 그리기

	//SampleDesc: 멀티샘플링(안티앨리어싱이라 보면 됨)
	//근데 얘는 msaa라 느려서 나중에 셰이더때 구현해서 쓴다 캄
	
	SwapDesc.SampleDesc.Quality = 0; // 퀄리티 0~15 조절 가능
	SwapDesc.SampleDesc.Count = 1; //@지금은 1개지만 나중에 알파블렌딩 할 때 늘어날것 

	//나중에 엔비디아의 성능좋은 fxaa코드 갖다 쓴다.

	SwapDesc.Windowed = WindowMode; //창모드, 풀스크린 여부
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //얘도 장치에 맞긴다는거


	//디바이스, 어댑터, 팩토리 삼위일체 순으로 얻어온다.

	IDXGIDevice* DXGIDevice = nullptr; //IDXGIDevice 에 대한 정보를 불러온다. 지금은 null
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice); //__uuidof uid
	//GUID 가리키고 보이드 이중포인터로 형변환해서 담아둠.

	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if (FAILED(Factory->CreateSwapChain(m_Device, &SwapDesc, &m_SwapChain)))
	{
		//스왑체인 생성 실패 시
		SAFE_RELEASE(Factory);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(DXGIDevice);
		return false;
	}

	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(DXGIDevice);

	// SwapChain이 만들어졌다면 SwapChain이 가지고 있는 BackBuffer를 얻어온다.
	ID3D11Texture2D* BackBuffer = nullptr;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;

	//####렌더타겟뷰 생성####
	// BackBuffer와 연결된 RenderTargetView를 생성한다.
	if (FAILED(m_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_TargetView)))
		return false;

	SAFE_RELEASE(BackBuffer);

	//######깊이버퍼, 스탠실 버퍼 생성#####
	// 깊이버퍼를 만든다. 0~1로 물체의 앞 뒤를 판단한다.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};
	DepthDesc.Width = DeviceWidth;
	DepthDesc.Height = DeviceHeight;
	DepthDesc.ArraySize = 1; //1로 고정

	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; //D24: 24비트, 8비트씩 해서 3바이트(R,G,B)
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //
	DepthDesc.Usage = D3D11_USAGE_DEFAULT; //사용처, 종류가 여럿있음, 7.15 메모장 참고
	DepthDesc.SampleDesc.Count = 1;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1; //텍스트 만들때 다시 설명


	//######깊이버퍼, 스탠실 버퍼 진짜로 생성#####
	ID3D11Texture2D* DepthBuffer = nullptr;

	if (FAILED(m_Device->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	if (FAILED(m_Device->CreateDepthStencilView(DepthBuffer, nullptr, &m_DepthView)))
		return false;

	SAFE_RELEASE(DepthBuffer);

	//###뷰 포트 생성
	D3D11_VIEWPORT	VP = {};

	VP.Width = (float)DeviceWidth;
	VP.Height = (float)DeviceHeight;
	VP.MaxDepth = 1.f;

	m_Context->RSSetViewports(1, &VP); 

	return true;
}

void CDevice::ClearRenderTarget(float ClearColor[4])
{
	//렌더타겟 클리어(원하는 색깔을 백버퍼로 클리어 해준다. 검은색, 흰색 하지마라)
	m_Context->ClearRenderTargetView(m_TargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	//깊이 or 스텐실 클리어 여부 혹은 둘 다?
	m_Context->ClearDepthStencilView(m_DepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		Depth, Stencil);
}

void CDevice::RenderStart()
{
	//렌더타겟 세팅하고 플립핑할 준비
	m_Context->OMSetRenderTargets(1, &m_TargetView, m_DepthView);
}

void CDevice::Flip()
{
	m_SwapChain->Present(0, 0);
}
