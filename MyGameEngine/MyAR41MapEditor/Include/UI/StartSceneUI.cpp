#include "StartSceneUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIProgressBar.h"
#include "UI/UINumber.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../Scene/LoadingSceneInfo.h"
#include "Engine.h"
#include "Input.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/NightMareKingGrimm.h"

CStartSceneUI::CStartSceneUI()
{
    m_WindowTypeName = "StartSceneUI";
}

CStartSceneUI::CStartSceneUI(const CStartSceneUI& Window) :
    CUIWindow(Window)
{
    m_Button = FindWidget<CUIButton>("Button");
    m_Title = FindWidget<CUIText>("Title");
    m_Number = FindWidget<CUINumber>("Number");

    m_MousePosX = FindWidget<CUINumber>("MouseX");
    m_MousePosY = FindWidget<CUINumber>("MouseY");
}

CStartSceneUI::~CStartSceneUI()
{
}

void CStartSceneUI::Start()
{
    CUIWindow::Start();

    m_Button->SetCallback<CStartSceneUI>(EButtonEventState::Click,
        this, &CStartSceneUI::StartButtonClick);
}

bool CStartSceneUI::Init()
{
    CUIWindow::Init();
    
    //버튼
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

    m_Button->SetCallback<CStartSceneUI>(EButtonEventState::Click,
        this, &CStartSceneUI::StartButtonClick);

    //텍스트
    m_Title = CreateWidget<CUIText>("Title");

    m_Title->SetSize(300.f, 100.f);
    m_Title->SetPos(200.f, 500.f);

    m_Title->SetFontSize(50.f);
    m_Title->SetText(TEXT("망나니의 대모험 ABCDEF 123456"));
    //m_Title->SetColor(255, 255, 0);
    //m_Title->SetColor(83, 45, 0);
    m_Title->SetColor(254, 254, 254);
    //m_Title->SetTransparency(true);
    //m_Title->SetOpacity(0.8f);

    m_Title->SetShadowEnable(true);
    m_Title->SetShadowColor(128, 128, 128);
    m_Title->SetShadowTransparency(true);
    m_Title->SetShadowOpacity(0.5f);

    //프로그래스 바
    m_ProgressBar = CreateWidget<CUIProgressBar>("ProgressBar");

    m_ProgressBar->SetPos(200.f, 600.f);
    m_ProgressBar->SetSize(200.f, 40.f);

    m_ProgressBar->SetImageTint(EProgressBarTextureType::Back, 100, 100, 100, 255);
    m_ProgressBar->SetImageTint(EProgressBarTextureType::Bar, 255, 255, 255, 255);

    m_ProgressBar->SetTexture(EProgressBarTextureType::Bar, "HPBar",
        TEXT("HPBar.png"));

    m_ProgressBar->SetProgressBarMin(0.f);
    m_ProgressBar->SetProgressBarMax(100.f);
    m_ProgressBar->SetValue(50.f);
    m_ProgressBar->SetBarDir(EProgressBarDir::RightToLeft);

    //넘버위젯
    m_Number = CreateWidget<CUINumber>("Number");

    m_Number->SetPos(200.f, 400.f);
    m_Number->SetSize(20.f, 30.f);

    m_Number->SetNumber(2392);

    m_Number->SetTexture("Number", TEXT("Number.png"));

    for (int i = 0; i < 10; ++i)
    {
        m_Number->AddFrameData(Vector2(i * 46.4f, 0.f), Vector2((i + 1) * 46.4f, 68.5f));
    }

    CUIText* Text = CreateWidget<CUIText>("MousePos");
    Text->SetFontSize(14.f);
    Text->SetSize(100.f, 30.f);
    Text->SetPos(1000.f, 650.f);
    Text->SetText(TEXT("Mouse Pos"));
    Text->SetColor(0, 0, 255);
    Text->SetAlignH(Text_Align_H::Right);


    m_MousePosX = CreateWidget<CUINumber>("MouseX");
    m_MousePosX->SetTexture("Number", TEXT("Number.png"));
    for (int i = 0; i < 10; ++i)
    {
        m_MousePosX->AddFrameData(Vector2(i * 46.4f, 0.f), Vector2((i + 1) * 46.4f, 68.5f));
    }
    m_MousePosX->SetPos(1100.f, 660.f);
    m_MousePosX->SetSize(10.f, 15.f);

    m_MousePosY = CreateWidget<CUINumber>("MouseY");
    m_MousePosY->SetTexture("Number", TEXT("Number.png"));
    for (int i = 0; i < 10; ++i)
    {
        m_MousePosY->AddFrameData(Vector2(i * 46.4f, 0.f), Vector2((i + 1) * 46.4f, 68.5f));
    }
    m_MousePosY->SetPos(1100.f, 640.f);
    m_MousePosY->SetSize(10.f, 15.f);
    
    return true;
}

void CStartSceneUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    float FPS = CEngine::GetInst()->GetFPS();

    m_Number->SetNumber((unsigned int)FPS);
    //Vector3 v = m_Scene->FindObject("NightMareKingGrimm")->GetWorldPos();
    //m_MousePosX->SetNumber((unsigned int)v.x);
    //m_MousePosY->SetNumber((unsigned int)v.y);
     
    
    //Vector2 v1 = CInput::GetInst()->GetMousePos();
    //Vector2 v2 = CInput::GetInst()->ComputeWorldMousePos();

    //m_MousePosX->SetNumber((unsigned int)v1.x);
    //m_MousePosY->SetNumber((unsigned int)v1.y);

    //Vector3 v = m_Scene->GetPlayer()->GetWorldPos();

    //m_MousePosX->SetNumber((unsigned int)v.x);
    //m_MousePosY->SetNumber((unsigned int)v.y);

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
    m_Title = FindWidget<CUIText>("Title");
}

void CStartSceneUI::StartButtonClick()
{
    // 로딩 Scene을 생성한다.
    //CSceneManager::GetInst()->CreateNextScene(true);

    //CSceneManager::GetInst()->CreateSceneInfo<CLoadingSceneInfo>(false);

    //빈 씬 생성
    CSceneManager::GetInst()->CreateNextScene(true);
    CSceneManager::GetInst()->ChangeNextScene();
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    int a = 0;
}