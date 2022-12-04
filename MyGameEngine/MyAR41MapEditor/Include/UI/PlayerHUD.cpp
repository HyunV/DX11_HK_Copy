#include "PlayerHUD.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UIImage.h"
#include "../GameObject/Player2D.h"
#include "Scene/SceneManager.h"
#include "UI/UIImageBlack.h"

#include "Scene/Scene.h"
CPlayerHUD::CPlayerHUD()
{
	m_WindowTypeName = "PlayerHUD";
}

CPlayerHUD::CPlayerHUD(const CPlayerHUD& Window)	:
	CUIWindow(Window)
{	
	m_Mask = FindWidget<CUIImage>("Mask");
	m_GioCount = FindWidget<CUIText>("GioText");

}

CPlayerHUD::~CPlayerHUD()
{

}

void CPlayerHUD::Start()
{
	CUIWindow::Start();
	m_Name = "PlayerHUD";
	m_Player = (CPlayer2D*)(CSceneManager::GetInst()->GetScene()->FindObject("Player2D"));
	
	//CreateEmptyHeart();
	//CreateHeart(m_Player->m_HP);

	CreateFadeUI(EFade::FadeIn, 1.f);
}

bool CPlayerHUD::Init()
{
	CUIWindow::Init();
	////////////////////////////////////////////////////////
	CUIImage* Frame = CreateWidget<CUIImage>("Frame");
	Frame->SetSize(257.f * g_SCALE, 164.f * g_SCALE);
	Frame->SetPos(50.f, 592.f);
	Frame->SetTexture("Frame", TEXT("HollowKnight/HUD/HUD Frame Idle_000.png"));

	m_Mask = CreateWidget<CUIImage>("Mask");
	m_Mask->SetSize(130.f * g_SCALE, 125.f * g_SCALE);
	m_Mask->SetPos(57.f, 593.f);
	m_Mask->SetTexture("Mask", TEXT("HollowKnight/HUD/HUD Cln_263.png"));

	CUIImage* GioImage = CreateWidget<CUIImage>("GioImage");
	GioImage->SetSize(62.f * g_SCALE, 62.f * g_SCALE);
	GioImage->SetPos(155.f, 584.f);
	GioImage->SetTexture("GioImage", TEXT("HollowKnight/HUD/Coin Idle_000.png"));


	//지오 
	m_GioCount = CreateWidget<CUIText>("GioText");
	m_GioCount->SetText(TEXT("1234"));
	m_GioCount->SetAlignH(Text_Align_H::Left);
	m_GioCount->SetFontSize(30.f);
	m_GioCount->SetSize(120.f, 50.f);
	m_GioCount->SetPos(200.f, 577.f);
	m_GioCount->SetShadowEnable(true);
	m_GioCount->SetShadowColor(0, 0, 0);
	m_GioCount->SetShadowOffset(0.5f, 0.5f);
	return true;
}

void CPlayerHUD::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	//게이지
	float percent = m_Player->m_vecCoolDown[3].CoolDown / 3.f;
	if(!(percent == 1.f))
		m_Mask->SetOpacity(1.f-percent);

	//지오
	int Gio = m_Player->m_Gio;

	TCHAR c[10] = {};
	wsprintf(c, TEXT("%d"), Gio);
	m_GioCount->SetText(c);

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

void CPlayerHUD::CreateHeart(int count)
{
	int size = (int)m_LifeStack.size();
	for (int i = size; i < size+count; i++)
	{
		int size2 = (int)m_LifeStack.size();
		
		char c[256] = {};
		sprintf_s(c, "Life%d", size2);

		CUIImage* life = CreateWidget<CUIImage>(c);
		life->SetSize(63.f, 83.5f);
		life->SetPos(140.f + (i * 40.f), 610.f);
		life->SetTexture("Health", TEXT("HollowKnight/HUD/Health/001HealthIdle.png"));

		for (int i = 0; i < 15; i++)
			life->AddFrameData(Vector2(i * 126.f, 0.f), Vector2((i + 1) * 126.f, 167.f));

		life->SetPlayTime(100.f);
		life->SetPlayScale(1.f);
		m_LifeStack.push(life);
	}
}

void CPlayerHUD::CreateEmptyHeart()
{
	for (int i = 0; i < 8; i++)
	{		
		//빈 라이프
		char c2[256] = {};
		sprintf_s(c2, "EmptyLife%d", i);
		CUIImage* Emptylife = CreateWidget<CUIImage>(c2);
		Emptylife->SetSize(63.f, 83.5f);
		Emptylife->SetPos(140.f + (i * 40.f), 610.f);
		Emptylife->SetTexture("EmptyLife", TEXT("HollowKnight/HUD/Health/003HealthEmpty.png"));
		m_EmptyLife.push_back(Emptylife);
	}

	m_EmptyLife[5]->SetEnable(false);
	m_EmptyLife[6]->SetEnable(false);
	m_EmptyLife[7]->SetEnable(false);
}

void CPlayerHUD::CreateBreakHeart()
{
	CUIImage* BreakHeart = CreateWidget<CUIImage>("HeartBreak");
	CUIImage* image = m_LifeStack.top();

	BreakHeart->SetSize(63.f, 83.5f);

	BreakHeart->SetPos(image->GetPos());
	BreakHeart->SetTexture("BreakLife", TEXT("HollowKnight/HUD/Health/002HealthBreak.png"));
	for (int i = 0; i < 7; i++)
		BreakHeart->AddFrameData(Vector2(i * 126.f, 0.f), Vector2((i + 1) * 126.f, 167.f));

	BreakHeart->SetDestroy(true);
	BreakHeart->SetPlayTime(100.f);
	BreakHeart->SetPlayScale(1.f);
}

void CPlayerHUD::CreateRefillHeart()
{
	if (m_Player->m_MaxHP <= (int)m_LifeStack.size())
		return;

	CreateHeart(1);

	CUIImage* RefillHeart = CreateWidget<CUIImage>("HeartRefill");
	//CUIImage* image = m_LifeStack.top();
	//int size = (int)m_LifeStack.size();
	
	RefillHeart->SetSize(63.f, 83.5f);

	RefillHeart->SetPos(m_LifeStack.top()->GetPos());
	//RefillHeart->SetPos(m_EmptyLife[size]->GetPos());
	RefillHeart->SetTexture("RefillLife", TEXT("HollowKnight/HUD/Health/005HealthRefill.png"));
	for (int i = 0; i < 7; i++)
		RefillHeart->AddFrameData(Vector2(i * 126.f, 0.f), Vector2((i + 1) * 126.f, 167.f));

	RefillHeart->SetDestroy(true);
	RefillHeart->SetPlayTime(100.f);
	RefillHeart->SetPlayScale(1.f);
}

void CPlayerHUD::DeleteHeart()
{
	m_LifeStack.top()->Destroy();
	m_LifeStack.pop();
}

void CPlayerHUD::UpgradeMaxHeart()
{
	m_EmptyLife[5]->SetEnable(true);
	m_EmptyLife[6]->SetEnable(true);
	m_EmptyLife[7]->SetEnable(true);

	int HP = (int)(5 - m_LifeStack.size());
	CreateHeart(HP);

	if(m_LifeStack.size()<= 8)
		CreateHeart(3);
}

void CPlayerHUD::CreateFadeUI(EFade Fade, float PlayTime)
{
	CUImageBlack* Black = CreateWidget<CUImageBlack>("Fade");
	Black->StartFade(Fade, PlayTime);
}
