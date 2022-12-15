#include "NightMareKingUI.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"
#include "../GameObject/Zombie.h"
#include "Scene/Scene.h"

CNightMareKingUI::CNightMareKingUI()
{
    m_WindowTypeName = "NightMareKingUI";
}

CNightMareKingUI::CNightMareKingUI(const CNightMareKingUI& Window)  :
    CUIWindow(Window)
{
}

CNightMareKingUI::~CNightMareKingUI()
{
}

void CNightMareKingUI::Start()
{
    CUIWindow::Start();
    //CResourceManager::GetInst()->LoadSound("BGM", "NightMareKingGrimm", true, "Nightmare King Grimm - S87-168 Nightmare Grimm.wav");
    //CResourceManager::GetInst()->SoundPlay("NightMareKingGrimm");
}

bool CNightMareKingUI::Init()
{
    CUIWindow::Init();

    CUIImage* Back = CreateWidget<CUIImage>("GrimmBack");
    Back->SetTexture("GrimmBack", TEXT("HollowKnight/Boss/Event/MessegeBox.png"));
    Back->SetSize(1280.f, 720.f);

    CUIText* Text1 = CreateWidget<CUIText>("NightMareKing");
    Text1->SetSize(1280.f, 60.f);
    Text1->SetPos(0, 400.f);
    Text1->SetText(TEXT("¾Ç¸ùÀÇ ¿Õ"));
    Text1->SetFontSize(35.f);
    Text1->SetAlignH(Text_Align_H::Center);
    Text1->SetColor(251, 32, 2);

    CUIText* Text2 = CreateWidget<CUIText>("Grimm");
    Text2->SetSize(1280.f, 60.f);
    Text2->SetPos(0, 350.f);
    Text2->SetText(TEXT("±×¸²"));
    Text2->SetFontSize(100.f);
    Text2->SetAlignH(Text_Align_H::Center);
    Text2->SetColor(251, 32, 2);

    m_vecText.push_back(Text1);
    m_vecText.push_back(Text2);

    m_Time = 0.f;
    return true;
}

void CNightMareKingUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
    m_Time += DeltaTime;
    if (m_Time >= 3.f)
    {
        m_vecText[0]->SetEnable(false);
        m_vecText[1]->SetEnable(false);
    }

    if (m_Time >= 4.f)
        Destroy();
}

void CNightMareKingUI::Render()
{
    CUIWindow::Render();
}
