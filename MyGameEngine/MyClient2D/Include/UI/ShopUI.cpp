#include "ShopUI.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"
#include "UI/UIButton.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "MyGameManager.h"
#include "../GameObject/Player2D.h"


CShopUI::CShopUI()
{
	m_WindowTypeName = "ShopUI";
}

CShopUI::CShopUI(const CShopUI& Window)	:
	CUIWindow(Window)
{

}

CShopUI::~CShopUI()
{
	CInput::GetInst()->DeleteBindFunction("Esc", Input_Type::Down, this);
}

void CShopUI::Start()
{
	CUIWindow::Start();

}

bool CShopUI::Init()
{
	CUIWindow::Init();

	CUIImage* MsgBox = CreateWidget<CUIImage>("MsgBox");
	MsgBox->SetTexture("MsgBox", TEXT("HollowKnight/NPCS/Dir/MessegeBox.png"));
	MsgBox->SetPivot(0.5f, 0.5f);
	MsgBox->SetSize(450.f, 550.f);
	MsgBox->SetPos(1020.f, 360.f);
	MsgBox->SetOpacity(0.8f);

	CUIImage* ShopTop = CreateWidget<CUIImage>("ShopTop");
	ShopTop->SetTexture("MsgFrameUp", TEXT("HollowKnight/NPCS/Shop/ShopTop.png"));
	ShopTop->SetPivot(0.5f, 0.5f);
	ShopTop->SetSize(709.f * g_SCALE, 392.f * g_SCALE);
	ShopTop->SetPos(1020.f, 542.f);

	CUIImage* ShopBottom = CreateWidget<CUIImage>("ShopBottom");
	ShopBottom->SetTexture("ShopBottom", TEXT("HollowKnight/NPCS/Shop/ShopBottom.png"));
	ShopBottom->SetPivot(0.5f, 0.5f);
	ShopBottom->SetSize(697.f * g_SCALE, 235.f * g_SCALE);
	ShopBottom->SetPos(1020.f, 107.f);

	CUIImage* ShopIcon = CreateWidget<CUIImage>("ShopIcon");
	ShopIcon->SetTexture("ShopIcon", TEXT("HollowKnight/NPCS/Shop/ShopSly.png"));
	ShopIcon->SetPivot(0.5f, 0.5f);
	ShopIcon->SetSize(124.f*g_SCALE, 148.f * g_SCALE);
	ShopIcon->SetPos(1020.f, 675.f);

	CUIText* NPCName = CreateWidget<CUIText>("ShopNPC");
	NPCName->SetText(TEXT("슬라이"));
	NPCName->SetAlignH(Text_Align_H::Left);
	NPCName->SetFontSize(50.f);
	NPCName->SetSize(250.f, 100.f);
	NPCName->SetPos(70.f, 20.f);
	NPCName->SetShadowEnable(true);
	NPCName->SetShadowColor(0, 0, 0);

	//메시지
	CUIText* Text1 = CreateWidget<CUIText>("TextSly");
	Text1->SetAlignH(Text_Align_H::Left);
	Text1->SetFontSize(16.f);
	Text1->SetSize(250.f, 30.f);
	Text1->SetPos(940.f, 100.f);
	Text1->SetShadowEnable(true);
	Text1->SetShadowColor(0, 0, 0);
	Text1->SetText(TEXT("- ESC 키를 눌러 닫기 -"));

	m_SlyText = CreateWidget<CUIText>("TextSly2");
	m_SlyText->SetAlignH(Text_Align_H::Center);
	m_SlyText->SetFontSize(24.f);
	m_SlyText->SetSize(450.f, 30.f);
	m_SlyText->SetPos(790.f, 560.f);
	m_SlyText->SetShadowEnable(true);
	m_SlyText->SetShadowColor(0, 0, 0);
	m_SlyText->SetText(TEXT("업그레이드로 더 강해지세요!"));

	//==================상점아이템======================================
	//체력 증가
	CUIText* HPUpItem = CreateWidget<CUIText>("HPUpItem");
	HPUpItem->SetAlignH(Text_Align_H::Left);
	HPUpItem->SetFontSize(24.f);
	HPUpItem->SetSize(450.f, 30.f);
	HPUpItem->SetPos(820.f, 500.f);
	HPUpItem->SetShadowEnable(true);
	HPUpItem->SetShadowColor(0, 0, 0);
	HPUpItem->SetText(TEXT("체력 증가		300"));

	CUIImage* GioImage = CreateWidget<CUIImage>("GioImage");
	GioImage->SetTexture("GioImage", TEXT("HollowKnight/NPCS/Shop/Coin Idle_000.png"));
	GioImage->SetPos(1020.f, 497.f);
	GioImage->SetSize(31.f, 31.f);

	CUIText* HPUpText = CreateWidget<CUIText>("HPUpText");
	HPUpText->SetAlignH(Text_Align_H::Left);
	HPUpText->SetFontSize(16.f);
	HPUpText->SetSize(450.f, 30.f);
	HPUpText->SetPos(840.f, 465.f);
	HPUpText->SetShadowEnable(true);
	HPUpText->SetShadowColor(0, 0, 0);
	HPUpText->SetText(TEXT("최대 체력이 3 증가합니다."));
	HPUpText->SetColor(200, 200, 200);

	m_HPUpButton = CreateWidget<CUIButton>("HPUpButton");
	m_HPUpButton->SetSize(90.f, 45.f);
	m_HPUpButton->SetPos(1120.f, 487.f);
	m_HPUpButton->SetTexture(EButtonState::Normal, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_HPUpButton->SetTexture(EButtonState::Hovered, "Purchase2", TEXT("HollowKnight/NPCS/Shop/Purchase2.png"));
	m_HPUpButton->SetTexture(EButtonState::Click, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_HPUpButton->SetTexture(EButtonState::Disable, "Purchased", TEXT("HollowKnight/NPCS/Shop/Purchased.png"));
	m_HPUpButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
	m_HPUpButton->SetCallback<CShopUI>(EButtonEventState::Click, this, &CShopUI::HPUpButton);

	//공격력 증가
	CUIText* AtkUpItem = CreateWidget<CUIText>("AtkUpItem");
	AtkUpItem->SetAlignH(Text_Align_H::Left);
	AtkUpItem->SetFontSize(24.f);
	AtkUpItem->SetSize(450.f, 30.f);
	AtkUpItem->SetPos(820.f, 420.f);
	AtkUpItem->SetShadowEnable(true);
	AtkUpItem->SetShadowColor(0, 0, 0);
	AtkUpItem->SetText(TEXT("공격 강화		500"));

	CUIImage* GioImage2 = CreateWidget<CUIImage>("GioImage2");
	GioImage2->SetTexture("GioImage", TEXT("HollowKnight/NPCS/Shop/Coin Idle_000.png"));
	GioImage2->SetPos(1020.f, 417.f);
	GioImage2->SetSize(31.f, 31.f);

	CUIText* AtkUpText = CreateWidget<CUIText>("AtkUpText");
	AtkUpText->SetAlignH(Text_Align_H::Left);
	AtkUpText->SetFontSize(16.f);
	AtkUpText->SetSize(450.f, 30.f);
	AtkUpText->SetPos(840.f, 385.f);
	AtkUpText->SetShadowEnable(true);
	AtkUpText->SetShadowColor(0, 0, 0);
	AtkUpText->SetText(TEXT("일반 공격 피해가 증가합니다."));
	AtkUpText->SetColor(200, 200, 200);

	m_AtkUpButton = CreateWidget<CUIButton>("AtkUpButton");
	m_AtkUpButton->SetSize(90.f, 45.f);
	m_AtkUpButton->SetPos(1120.f, 407.f);
	m_AtkUpButton->SetTexture(EButtonState::Normal, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_AtkUpButton->SetTexture(EButtonState::Hovered, "Purchase2", TEXT("HollowKnight/NPCS/Shop/Purchase2.png"));
	m_AtkUpButton->SetTexture(EButtonState::Click, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_AtkUpButton->SetTexture(EButtonState::Disable, "Purchased", TEXT("HollowKnight/NPCS/Shop/Purchased.png"));
	m_AtkUpButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
	m_AtkUpButton->SetCallback<CShopUI>(EButtonEventState::Click, this, &CShopUI::AtkUpButton);

	CUIText* ShadowDashItem = CreateWidget<CUIText>("ShadowDashItem");
	ShadowDashItem->SetAlignH(Text_Align_H::Left);
	ShadowDashItem->SetFontSize(24.f);
	ShadowDashItem->SetSize(450.f, 30.f);
	ShadowDashItem->SetPos(820.f, 340.f);
	ShadowDashItem->SetShadowEnable(true);
	ShadowDashItem->SetShadowColor(0, 0, 0);
	ShadowDashItem->SetText(TEXT("대시 강화		800"));

	CUIImage* GioImage3 = CreateWidget<CUIImage>("GioImage3");
	GioImage3->SetTexture("GioImage", TEXT("HollowKnight/NPCS/Shop/Coin Idle_000.png"));
	GioImage3->SetPos(1020.f, 337.f);
	GioImage3->SetSize(31.f, 31.f);

	CUIText* ShadowDashText = CreateWidget<CUIText>("ShadowDashText");
	ShadowDashText->SetAlignH(Text_Align_H::Left);
	ShadowDashText->SetFontSize(16.f);
	ShadowDashText->SetSize(450.f, 30.f);
	ShadowDashText->SetPos(840.f, 305.f);
	ShadowDashText->SetShadowEnable(true);
	ShadowDashText->SetShadowColor(0, 0, 0);
	ShadowDashText->SetText(TEXT("대시에 무적 효과가 추가됩니다."));
	ShadowDashText->SetColor(200, 200, 200);

	m_ShadowDashButton = CreateWidget<CUIButton>("ShadowDashButton");
	m_ShadowDashButton->SetSize(90.f, 45.f);
	m_ShadowDashButton->SetPos(1120.f, 327.f);
	m_ShadowDashButton->SetTexture(EButtonState::Normal, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_ShadowDashButton->SetTexture(EButtonState::Hovered, "Purchase2", TEXT("HollowKnight/NPCS/Shop/Purchase2.png"));
	m_ShadowDashButton->SetTexture(EButtonState::Click, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_ShadowDashButton->SetTexture(EButtonState::Disable, "Purchased", TEXT("HollowKnight/NPCS/Shop/Purchased.png"));
	m_ShadowDashButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
	m_ShadowDashButton->SetCallback<CShopUI>(EButtonEventState::Click, this, &CShopUI::ShadowDashButton);

	CUIText* ShadowFireItem = CreateWidget<CUIText>("ShadowFireItem");
	ShadowFireItem->SetAlignH(Text_Align_H::Left);
	ShadowFireItem->SetFontSize(24.f);
	ShadowFireItem->SetSize(450.f, 30.f);
	ShadowFireItem->SetPos(820.f, 260.f);
	ShadowFireItem->SetShadowEnable(true);
	ShadowFireItem->SetShadowColor(0, 0, 0);
	ShadowFireItem->SetText(TEXT("쉐도우 볼		1000"));

	CUIImage* GioImage4 = CreateWidget<CUIImage>("GioImage4");
	GioImage4->SetTexture("GioImage", TEXT("HollowKnight/NPCS/Shop/Coin Idle_000.png"));
	GioImage4->SetPos(1020.f, 257.f);
	GioImage4->SetSize(31.f, 31.f);

	CUIText* ShadowFireText = CreateWidget<CUIText>("ShadowFireText");
	ShadowFireText->SetAlignH(Text_Align_H::Left);
	ShadowFireText->SetFontSize(16.f);
	ShadowFireText->SetSize(450.f, 30.f);
	ShadowFireText->SetPos(840.f, 225.f);
	ShadowFireText->SetShadowEnable(true);
	ShadowFireText->SetShadowColor(0, 0, 0);
	ShadowFireText->SetText(TEXT("에너지파에 관통 효과가 부여됩니다."));
	ShadowFireText->SetColor(200, 200, 200);

	m_ShadowBallButton = CreateWidget<CUIButton>("ShadowBallButton");
	m_ShadowBallButton->SetSize(90.f, 45.f);
	m_ShadowBallButton->SetPos(1120.f, 247.f);
	m_ShadowBallButton->SetTexture(EButtonState::Normal, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_ShadowBallButton->SetTexture(EButtonState::Hovered, "Purchase2", TEXT("HollowKnight/NPCS/Shop/Purchase2.png"));
	m_ShadowBallButton->SetTexture(EButtonState::Click, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_ShadowBallButton->SetTexture(EButtonState::Disable, "Purchased", TEXT("HollowKnight/NPCS/Shop/Purchased.png"));
	m_ShadowBallButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
	m_ShadowBallButton->SetCallback<CShopUI>(EButtonEventState::Click, this, &CShopUI::ShadowBallButton);

	CUIText* SuperEnding = CreateWidget<CUIText>("SuperEnding");
	SuperEnding->SetAlignH(Text_Align_H::Left);
	SuperEnding->SetFontSize(24.f);
	SuperEnding->SetSize(450.f, 30.f);
	SuperEnding->SetPos(820.f, 180.f);
	SuperEnding->SetShadowEnable(true);
	SuperEnding->SetShadowColor(0, 0, 0);
	SuperEnding->SetText(TEXT("자본주의		10000"));

	CUIImage* GioImage5 = CreateWidget<CUIImage>("GioImage5");
	GioImage5->SetTexture("GioImage", TEXT("HollowKnight/NPCS/Shop/Coin Idle_000.png"));
	GioImage5->SetPos(1020.f, 177.f);
	GioImage5->SetSize(31.f, 31.f);

	CUIText* SuperEndingText = CreateWidget<CUIText>("SuperEndingText");
	SuperEndingText->SetAlignH(Text_Align_H::Left);
	SuperEndingText->SetFontSize(16.f);
	SuperEndingText->SetSize(450.f, 30.f);
	SuperEndingText->SetPos(840.f, 145.f);
	SuperEndingText->SetShadowEnable(true);
	SuperEndingText->SetShadowColor(0, 0, 0);
	SuperEndingText->SetText(TEXT("이유는 모르겠으나 엔딩을 볼 수 있습니다."));
	SuperEndingText->SetColor(200, 200, 200);

	m_EndingButton = CreateWidget<CUIButton>("EndingButton");
	m_EndingButton->SetSize(90.f, 45.f);
	m_EndingButton->SetPos(1120.f, 167.f);
	m_EndingButton->SetTexture(EButtonState::Normal, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_EndingButton->SetTexture(EButtonState::Hovered, "Purchase2", TEXT("HollowKnight/NPCS/Shop/Purchase2.png"));
	m_EndingButton->SetTexture(EButtonState::Click, "Purchase", TEXT("HollowKnight/NPCS/Shop/Purchase.png"));
	m_EndingButton->SetTexture(EButtonState::Disable, "Purchased", TEXT("HollowKnight/NPCS/Shop/Purchased.png"));
	m_EndingButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
	m_EndingButton->SetCallback<CShopUI>(EButtonEventState::Click, this, &CShopUI::EndingButton);



	//기타 함수
	CInput::GetInst()->AddBindFunction<CShopUI>("Esc", Input_Type::Down, this,
		&CShopUI::CloseShop, m_Scene);

	CResourceManager::GetInst()->LoadSound("Effect", "PurchaseSuccess", false, "Main/geo_deplete_count_down.wav");

	m_Player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
	m_PlayerGio = m_Player->m_PlayerInfo.Gio;
	SetShop();

	return true;
}

void CShopUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
	if (m_Product.HPUp)
		m_HPUpButton->ButtonEnable(false);
	if (m_Product.AtkUp)
		m_AtkUpButton->ButtonEnable(false);
	if (m_Product.ShadowDash)
		m_ShadowDashButton->ButtonEnable(false);
	if (m_Product.ShadowBall)
		m_ShadowBallButton->ButtonEnable(false);

}

void CShopUI::Render()
{
	CUIWindow::Render();
}

void CShopUI::SetShop()
{
	CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
	m_Product.HPUp = player->m_PlayerInfo.AdvHP;
	m_Product.AtkUp = player->m_PlayerInfo.AdvAttack;
	m_Product.ShadowDash = player->m_PlayerInfo.AdvDash;
	m_Product.ShadowBall = player->m_PlayerInfo.AdvFire;
}

void CShopUI::CloseShop()
{
	OutputDebugStringA("메시지 닫기");
	CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
	player->m_KeyLock = false;
	player->SetNextState();
	Destroy();
}

void CShopUI::HPUpButton()
{
	OutputDebugStringA("체력증가 구매");

	if (m_PlayerGio >= 300)
	{
		m_SlyText->SetText(TEXT("감사합니다 손님!"));
		CResourceManager::GetInst()->SoundPlay("PurchaseSuccess");
		m_Product.HPUp = true;
		m_PlayerGio -= 300;
		m_Player->PurchaseItem(300);
		m_Player->UpgradeMaxHeart();
	}
	else
	{
		m_SlyText->SetText(TEXT("지오가 부족해요 손님!"));
		return;
	}
}

void CShopUI::AtkUpButton()
{
	OutputDebugStringA("공격력 증가");

	if (m_PlayerGio >= 500)
	{
		m_SlyText->SetText(TEXT("감사합니다 손님!"));
		CResourceManager::GetInst()->SoundPlay("PurchaseSuccess");
		m_Product.AtkUp = true;
		m_PlayerGio -= 500;
		m_Player->PurchaseItem(500);
		m_Player->m_PlayerInfo.AdvAttack = true;
	}
	else
	{
		m_SlyText->SetText(TEXT("지오가 부족해요 손님!"));
		return;
	}
	
}

void CShopUI::ShadowDashButton()
{
	OutputDebugStringA("쉐도우 대시 활성화");

	if (m_PlayerGio >= 800)
	{
		m_SlyText->SetText(TEXT("감사합니다 손님!"));
		CResourceManager::GetInst()->SoundPlay("PurchaseSuccess");
		m_Product.ShadowDash = true;
		m_PlayerGio -= 800;
		m_Player->PurchaseItem(800);
		m_Player->m_PlayerInfo.AdvDash = true;
	}
	else
	{
		m_SlyText->SetText(TEXT("지오가 부족해요 손님!"));
		return;
	}
}

void CShopUI::ShadowBallButton()
{
	OutputDebugStringA("쉐도우 볼 활성화");
	if (m_PlayerGio >= 1000)
	{
		m_SlyText->SetText(TEXT("감사합니다 손님!"));
		CResourceManager::GetInst()->SoundPlay("PurchaseSuccess");
		m_Product.ShadowBall = true;
		m_PlayerGio -= 1000;
		m_Player->PurchaseItem(1000);
		m_Player->m_PlayerInfo.AdvFire = true;
	}
	else
	{
		m_SlyText->SetText(TEXT("지오가 부족해요 손님!"));
		return;
	}
}

void CShopUI::EndingButton()
{
	OutputDebugStringA("엔딩 씬!");
	if (m_PlayerGio >= 10000)
	{
		//엔딩	
	}
	else
	{
		m_SlyText->SetText(TEXT("후후 이건 아무나 살 수 있는게 아닙니다"));
		return;
	}	
}
