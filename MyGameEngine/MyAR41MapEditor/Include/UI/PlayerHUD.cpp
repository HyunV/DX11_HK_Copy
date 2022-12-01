#include "PlayerHUD.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UIImage.h"
#include "../GameObject/Player2D.h"

#include "Scene/Scene.h"
CPlayerHUD::CPlayerHUD()
{
	m_WindowTypeName = "PlayerHUD";
}

CPlayerHUD::CPlayerHUD(const CPlayerHUD& Window)
{	
	//m_Bar = FindWidget<CUIProgressBar>("EnergyBar");
	//m_Frame = FindWidget<CUIImage>("Frame");
	m_GioCount = FindWidget<CUIText>("GioText");
}

CPlayerHUD::~CPlayerHUD()
{
}

void CPlayerHUD::Start()
{
	CUIWindow::Start();
	//m_Player = (CPlayer2D*)(m_Scene->GetPlayer());
}

bool CPlayerHUD::Init()
{
	CUIWindow::Init();

	//m_Bar = CreateWidget<CUIProgressBar>("EnergyBar");

	//m_Bar->SetPos(100.f, 100.f);
	//m_Bar->SetSize(124.f, 124.f);

	//m_Bar->SetImageTint(EProgressBarTextureType::Back, 0, 0, 255, 255);
	//m_Bar->SetImageTint(EProgressBarTextureType::Bar, 255, 255, 255, 255);

	//m_Bar->SetTexture(EProgressBarTextureType::Back, "HUDBack",
	//	TEXT("HollowKnight/HUD/HUD Cln_264.png"));

	//m_Bar->SetTexture(EProgressBarTextureType::Bar, "HUDBar",
	//	TEXT("HollowKnight/HUD/Idle_000.png"));

	//m_Bar->SetProgressBarMin(0.f);
	//m_Bar->SetProgressBarMax(100.f);
	//m_Bar->SetValue(100.f);
	//m_Bar->SetBarDir(EProgressBarDir::TopToBottom);

	////////////////////////////////////////////////////////
	//CUIImage* Frame = CreateWidget<CUIImage>("Frame");
	//Frame->SetSize(257.f * g_SCALE, 164.f * g_SCALE);
	//Frame->SetPos(50.f, 592.f);
	//Frame->SetTexture("Frame", TEXT("HollowKnight/HUD/HUD Frame Idle_000.png"));

	//CUIImage* Mask = CreateWidget<CUIImage>("Mask");
	//Mask->SetSize(130.f * g_SCALE, 125.f * g_SCALE);	
	//Mask->SetPos(57.f, 593.f);
	//Mask->SetTexture("Mask", TEXT("HollowKnight/HUD/HUD Cln_263.png"));

	//CUIImage* GioImage = CreateWidget<CUIImage>("GioImage");
	//GioImage->SetSize(62.f * g_SCALE, 62.f * g_SCALE);
	//GioImage->SetPos(155.f, 584.f);
	//GioImage->SetTexture("GioImage", TEXT("HollowKnight/HUD/Coin Idle_000.png"));

	m_GioCount = CreateWidget<CUIText>("GioText");
	m_GioCount->SetText(TEXT("1234"));
	m_GioCount->SetAlignH(Text_Align_H::Left);
	m_GioCount->SetFontSize(30.f);
	m_GioCount->SetSize(120.f, 50.f);
	m_GioCount->SetPos(200.f, 577.f);
	m_GioCount->SetShadowEnable(true);
	m_GioCount->SetShadowColor(0, 0, 0);
	m_GioCount->SetShadowOffset(0.5f, 0.5f);

	int a = 0;
	//m_Life = CreateWidget<CUIImage>("Health");
	////126 167 *0.5f
	//m_Life->SetSize(63.f, 83.5f);
	//m_Life->SetPos(140.f, 610.f);

	//for (int i = 0; i < 5; i++)
	//{
	//	std::string s = "Health" + i;

	//	CUIImage* Health = CreateWidget<CUIImage>(s);
	//	Health->SetSize(63.f, 83.5f);
	//	Health->SetPos(140.f +(i*40.f), 610.f);
	//	Health->SetTexture("Health", TEXT("HollowKnight/HUD/Health/001HealthIdle.png"));
	//	for (int i = 0; i < 15; i++)
	//	{
	//		Health->AddFrameData(Vector2(i * 126.f, 0.f), Vector2((i + 1) * 126.f, 167.f));
	//	}
	//	Health->SetPlayTime(100.f);
	//	Health->SetPlayScale(1.f);
	//	m_vecLife.push_back(Health);
	//}
	//m_vecLife;
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

	//int Gio = m_Player->m_Gio;

	//TCHAR c[10] = {};
	//wsprintf(c, TEXT("%d"), Gio);
	//m_GioCount->SetText(c);
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
