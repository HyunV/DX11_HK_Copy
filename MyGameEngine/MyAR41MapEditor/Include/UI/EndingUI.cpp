#include "EndingUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"
#include "UI/UIImageBlack.h"

#include "MyGameManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "PathManager.h"

CEndingUI::CEndingUI()
{
    m_WindowTypeName = "EndingUI";
}

CEndingUI::CEndingUI(const CEndingUI& Window)   :
    CUIWindow(Window)
{
    m_Back = FindWidget<CUIImage>("EndingBack");
    m_ClearText = FindWidget<CUIImage>("ClearText");
    m_UpFrame = FindWidget<CUIImage>("UpFrame");
    m_DownFrame = FindWidget<CUIImage>("DownFrame");
    
    m_ButtonBack = FindWidget<CUIImage>("ButtonBack");
    m_MainButton = FindWidget<CUIButton>("MainButton");
}

CEndingUI::~CEndingUI()
{
}

void CEndingUI::Start()
{
    CUIWindow::Start();

    CResourceManager::GetInst()->LoadSound("BGM", "Ending", false, "dream_enter_pt_2.wav");
    CResourceManager::GetInst()->SoundPlay("Ending");

    m_MainButton->SetCallback<CEndingUI>(EButtonEventState::Click,
        this, &CEndingUI::MainButtonClick);

    CUImageBlack* black = CreateWidget<CUImageBlack>("black");
    black->StartFade(EFade::FadeIn, 5.f);
}

bool CEndingUI::Init()
{
    CUIWindow::Init();
    
    m_Back = CreateWidget<CUIImage>("EndingBack");
    m_Back->SetTexture("EndingBack", TEXT("HollowKnight/EndingTitle/Ending.png"));
    m_Back->SetSize(1280.f, 867.f);
    m_Back->SetPos(0.f, -60.f);

    m_ClearText = CreateWidget<CUIImage>("ClearText");
    m_ClearText->SetTexture("CleatText", TEXT("HollowKnight/EndingTitle/CLEAR2.png"));
    m_ClearText->SetSize(500.f, 140.f);
    m_ClearText->SetPivot(0.5f, 0.5f);
    m_ClearText->SetPos(850.f, 470.f);

    m_UpFrame = CreateWidget<CUIImage>("UpFrame");
    m_UpFrame->SetTexture("UpFrame", TEXT("HollowKnight/EndingTitle/Fleur Top Up_008.png"));
    m_UpFrame->SetSize(300.f, 44.f);
    m_UpFrame->SetPivot(0.5f, 0.5f);
    m_UpFrame->SetPos(840.f, 560.f);

    m_DownFrame = CreateWidget<CUIImage>("DownFrame");
    m_DownFrame->SetTexture("DownFrame", TEXT("HollowKnight/EndingTitle/Fleur Bot Up_008.png"));
    m_DownFrame->SetSize(216.f, 36.f);
    m_DownFrame->SetPivot(0.5f, 0.5f);
    m_DownFrame->SetPos(840.f, 375.f);

    m_ButtonBack = CreateWidget<CUIImage>("ButtonBack");
    m_ButtonBack->SetSize(240.f, 80.f);
    m_ButtonBack->SetPivot(0.5f, 0.5f);
    m_ButtonBack->SetPos(1120.f, 80.f);
    m_ButtonBack->SetOpacity(0.8f);
    m_ButtonBack->SetTexture("TextBack", TEXT("HollowKnight/HUD/HUD Cln_264.png"));

    m_MainButton = CreateWidget<CUIButton>("MainButton");
    m_MainButton->SetSize(140.f, 40.f);
    m_MainButton->SetPos(1050.f, 60.f);

    m_MainButton->SetTexture(EButtonState::Normal, "MainButton", TEXT("HollowKnight/EndingTitle/GoTitle1.png"));
    m_MainButton->SetTexture(EButtonState::Hovered, "MainButton2", TEXT("HollowKnight/EndingTitle/GoTitle2.png"));
    m_MainButton->SetTexture(EButtonState::Click, "MainButton", TEXT("HollowKnight/EndingTitle/GoTitle2.png"));

    m_MainButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
    m_MainButton->SetSound(EButtonEventState::Click, "UI", "BtnClick", false, "Main/ui_button_confirm.wav");

    return true;
}

void CEndingUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);
}

void CEndingUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);
}

void CEndingUI::Render()
{
    CUIWindow::Render();
}

CEndingUI* CEndingUI::Clone()
{
    return new CEndingUI(*this);
}

void CEndingUI::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CEndingUI::Load(FILE* File)
{
    CUIWindow::Load(File);

    m_MainButton = FindWidget<CUIButton>("MainButton");
}

void CEndingUI::MainButtonClick()
{
    //클리어 게임매니저
    CMyGameManager::GetInst()->ClearPlayerInfo();


    //메인타이틀 이동
    CSceneManager::GetInst()->CreateNextScene();

    char Name[256] = {};
    const PathInfo* Path = CPathManager::GetInst()->FindPath(SCENE_PATH);
    strcat_s(Name, Path->PathMultibyte);
    strcat_s(Name, "HollowScene6");
    strcat_s(Name, ".scn");

    CScene* NextScene = CSceneManager::GetInst()->GetNextScene();
    NextScene->Load(Name);

    CSceneManager::GetInst()->ChangeNextScene();
}
