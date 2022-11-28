#include "PlayerHUD.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UIImage.h"

CPlayerHUD::CPlayerHUD()
{
	m_WindowTypeName = "PlayerHUD";
}

CPlayerHUD::CPlayerHUD(const CPlayerHUD& Window)
{	
	m_Bar = FindWidget<CUIProgressBar>("EnergyBar");
}

CPlayerHUD::~CPlayerHUD()
{
}

void CPlayerHUD::Start()
{
	CUIWindow::Start();
}

bool CPlayerHUD::Init()
{
	CUIWindow::Init();

	m_Bar = CreateWidget<CUIProgressBar>("EnergyBar");

	m_Bar->SetPos(100.f, 100.f);
	m_Bar->SetSize(124.f, 124.f);

	m_Bar->SetImageTint(EProgressBarTextureType::Back, 0, 0, 255, 255);
	m_Bar->SetImageTint(EProgressBarTextureType::Bar, 255, 255, 255, 255);

	m_Bar->SetTexture(EProgressBarTextureType::Back, "HUDBack",
		TEXT("HollowKnight/HUD/HUD Cln_264.png"));

	m_Bar->SetTexture(EProgressBarTextureType::Bar, "HUDBar",
		TEXT("HollowKnight/HUD/Idle_000.png"));

	m_Bar->SetProgressBarMin(0.f);
	m_Bar->SetProgressBarMax(100.f);
	m_Bar->SetValue(100.f);
	m_Bar->SetBarDir(EProgressBarDir::TopToBottom);
	
	return true;
}

void CPlayerHUD::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
	//m_Count += DeltaTime * 10.f;
	//if (m_Count > 100.f)
	//	m_Count = 0;
	//
	//m_Bar->SetValue((int)m_Count);
}

void CPlayerHUD::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CPlayerHUD::Render()
{
	CUIWindow::Render();
}

CPlayerHUD* CPlayerHUD::Clone()
{
	return new CPlayerHUD(*this);
}

void CPlayerHUD::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CPlayerHUD::Load(FILE* File)
{
	CUIWindow::Load(File);
}
