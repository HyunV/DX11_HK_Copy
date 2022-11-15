#include "MyLoadingUI.h"
#include "UI/UIImage.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "UI/UINumber.h"

CMyLoadingUI::CMyLoadingUI()
{
	m_WindowTypeName = "MyLoadingUI";
}

CMyLoadingUI::CMyLoadingUI(const CMyLoadingUI& Window)	:
	CUIWindow(Window)
{
}

CMyLoadingUI::~CMyLoadingUI()
{
}


void CMyLoadingUI::Start()
{
	CUIWindow::Start();
}

bool CMyLoadingUI::Init()
{
	CUIWindow::Init();

	m_LoadingAnim = CreateWidget<CUINumber>("Loading");
	m_LoadingAnim->SetTexture("LoadingTexture", TEXT("HollowKnight/MainTitle/Loading.png"));
	m_LoadingAnim->SetSize(169.f, 126.f);
	m_LoadingAnim->SetPos(1050.f, 50.f);

	for (int i = 0; i < 11; i++)
	{
		m_LoadingAnim->AddFrameData(Vector2(i * 169.f, 0.f), Vector2((i + 1) * 169.f, 126.f));
	}
	m_count = 0;

	return true;
}

void CMyLoadingUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	m_count += DeltaTime * 15.f;

	if (m_count > 10.f)
		m_count = 0;

	m_LoadingAnim->SetNumber((unsigned int)m_count);
}

void CMyLoadingUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CMyLoadingUI::Render()
{
	CUIWindow::Render();
}

CMyLoadingUI* CMyLoadingUI::Clone()
{
	return new CMyLoadingUI(*this);
}

void CMyLoadingUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CMyLoadingUI::Load(FILE* File)
{
	CUIWindow::Load(File);
}
