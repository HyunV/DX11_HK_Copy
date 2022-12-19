#include "MainBackUI.h"
#include "UI/UIImage.h"

#include "Scene/Scene.h"
#include "MainTitleUI.h"
#include "MainParticleUI.h"

CMainBackUI::CMainBackUI()
{
	m_WindowTypeName = "MainBackUI";
}

CMainBackUI::CMainBackUI(const CMainBackUI& Window)	:
	CUIWindow(Window)
{
	m_Back = FindWidget<CUIImage>("Back");
}

CMainBackUI::~CMainBackUI()
{
}

void CMainBackUI::Start()
{
	CUIWindow::Start();

	m_Scene->GetViewport()->CreateUIWindow<CMainParticleUI>("MainParticleUI");
	CMainTitleUI* MainTitle = m_Scene->GetViewport()->CreateUIWindow<CMainTitleUI>("MainTitleUI");
	MainTitle->Start();
}

bool CMainBackUI::Init()
{
	m_Back = CreateWidget<CUIImage>("Back");
	m_Back->SetSize(1400.f, 1225.f);
	m_Back->SetPivot(0.5f, 0.f);
	m_Back->SetPos(640.f, -130.f);
	m_Back->SetTexture("MainTitleBack", TEXT("HollowKnight/MainTitle/Voidheart_menu_BG.png"));

	return true;
}

void CMainBackUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
}

void CMainBackUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CMainBackUI::Render()
{
	CUIWindow::Render();
}

CMainBackUI* CMainBackUI::Clone()
{
	return new CMainBackUI(*this);
}

void CMainBackUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CMainBackUI::Load(FILE* File)
{
	CUIWindow::Load(File);
}
