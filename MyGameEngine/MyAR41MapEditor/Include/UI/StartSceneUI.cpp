#include "StartSceneUI.h"
#include "UI/UIButton.h"

CStartSceneUI::CStartSceneUI()
{
    m_WindowTypeName = "StartSceneUI";
}

CStartSceneUI::CStartSceneUI(const CStartSceneUI& Window) :
    CUIWindow(Window)
{
    m_Button = FindWidget<CUIButton>("Button");
}

CStartSceneUI::~CStartSceneUI()
{
}

void CStartSceneUI::Start()
{
    CUIWindow::Start();
}

bool CStartSceneUI::Init()
{
    CUIWindow::Init();

    m_Button = CreateWidget<CUIButton>("Button");

    m_Button->SetSize(100.f, 100.f);
    m_Button->SetPos(300.f, 300.f);
    m_Button->SetTint(255, 0, 0, 255);

    m_Button->SetTexture(EButtonState::Normal, "StartButton", TEXT("Start.png"));
    m_Button->SetTexture(EButtonState::Hovered, "StartButton", TEXT("Start.png"));
    m_Button->SetTexture(EButtonState::Click, "StartButton", TEXT("Start.png"));
    m_Button->SetTexture(EButtonState::Disable, "StartButton", TEXT("Start.png"));

    m_Button->SetSound(EButtonEventState::Hovered, "UI", "ButtonHovered", false, "63.mp3");
    m_Button->SetSound(EButtonEventState::Click, "UI", "ButtonClick", false, "62.mp3");

    return true;
}

void CStartSceneUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CStartSceneUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CStartSceneUI::Render()
{
    CUIWindow::Render();
}

CStartSceneUI* CStartSceneUI::Clone()
{
    return new CStartSceneUI(*this);
}

void CStartSceneUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CStartSceneUI::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_Button = FindWidget<CUIButton>("Button");
}
