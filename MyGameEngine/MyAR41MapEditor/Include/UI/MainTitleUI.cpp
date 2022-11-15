#include "MainTitleUI.h"
#include "UI/UIButton.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"
#include "UI/UINumber.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../Scene/LoadingSceneInfo.h"
//#include "Resource/ResourceManager.h"
//#include "Animation/AnimationSequence2D.h"

CMainTitleUI::CMainTitleUI()
{
	m_WindowTypeName = "MainTitleUI";
}

CMainTitleUI::CMainTitleUI(const CMainTitleUI& Window)	:
	CUIWindow(Window)
{
	m_StartButton = FindWidget<CUIButton>("Button");
}

CMainTitleUI::~CMainTitleUI()
{
}

void CMainTitleUI::Start()
{
	CUIWindow::Start();

	m_StartButton->SetCallback<CMainTitleUI>(EButtonEventState::Click,
		this, &CMainTitleUI::StartButtonClick);

	//CResourceManager::GetInst()->LoadSound("BGM", "MainTitle", true, "Nightmare King Grimm - S87-168 Nightmare Grimm.wav");
	CResourceManager::GetInst()->LoadSound("BGM", "MainTitle", true, "Main/Main menu theme - Title.wav");
	CResourceManager::GetInst()->SoundPlay("MainTitle");
}

bool CMainTitleUI::Init()
{
	CUIWindow::Init();



	m_Back = CreateWidget<CUIImage>("Back");
	m_Back->SetSize(1280.f, 720.f);
	m_Back->SetTexture("MainTitleBack", TEXT("HollowKnight/MainTitle/Voidheart_menu_BG.png"));

	m_Logo = CreateWidget <CUIImage>("Logo");
	m_Logo->SetSize(841.f, 324.f);
	m_Logo->SetPivot(0.5f, 0.5f);
	m_Logo->SetPos(640.f, 500.f);
	m_Logo->SetTexture("MainTitleLoge", TEXT("HollowKnight/MainTitle/TitleLight896350.png"));
	m_Logo->SetImageTint(255, 255, 255, 255);
	
	m_Dev = CreateWidget <CUIImage>("Dev");
	m_Dev->SetSize(71.f, 58.f);
	m_Dev->SetPos(1020.f, 100.f);
	m_Dev->SetTexture("DevLogo", 
		TEXT("HollowKnight/MainTitle/Dev2.png"));

	//텍스트
	m_StartTitle = CreateWidget<CUIText>("StartTitle");
	
	m_StartTitle->SetSize(300.f, 100.f);
	m_StartTitle->SetPos(487.f, 150.f);
	m_StartTitle->SetPivot(0.5f, 0.5f);
	
	m_StartTitle->SetFontSize(25.f);
	m_StartTitle->SetText(TEXT("게임 시작"));
	m_StartTitle->SetColor(255, 255, 255);
	m_StartTitle->SetTint(255, 255, 255, 255);
	m_StartTitle->SetAlignH(Text_Align_H::Center);

	m_StartButton = CreateWidget<CUIButton>("Button");

	m_StartButton->SetSize(105.f, 40.f);
	m_StartButton->SetPos(585.f, 210.f);
	m_StartButton->SetTexture(EButtonState::Normal, "StartButton", TEXT("Start.png"));
	m_StartButton->SetTexture(EButtonState::Hovered, "StartButton", TEXT("Start.png"));
	m_StartButton->SetTexture(EButtonState::Click, "StartButton", TEXT("Start.png"));

	m_StartButton->SetOpacity(0.f);
	m_StartButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
	m_StartButton->SetSound(EButtonEventState::Click, "UI", "BtnClick", false, "Main/ui_button_confirm.wav");

	m_ExitTitle = CreateWidget<CUIText>("EndTitle");

	m_ExitTitle->SetSize(300.f, 100.f);
	m_ExitTitle->SetPos(487.f, 50.f);
	m_ExitTitle->SetPivot(0.5f, 0.5f);

	m_ExitTitle->SetFontSize(25.f);
	m_ExitTitle->SetText(TEXT("게임 종료"));
	m_ExitTitle->SetColor(255, 255, 255);
	m_ExitTitle->SetAlignH(Text_Align_H::Center);

	m_ExitButton = CreateWidget<CUIButton>("ExitButton");

	m_ExitButton->SetSize(105.f, 40.f);
	m_ExitButton->SetPos(585.f, 110.f);
	//m_ExitButton->SetTexture(EButtonState::Normal, "ExitButton", TEXT("Start.png"));
	m_ExitButton->SetOpacity(0.f);
	m_ExitButton->SetCallback<CMainTitleUI>(EButtonEventState::Click,
		this, &CMainTitleUI::ExitButtonClick);
	m_ExitButton->SetSound(EButtonEventState::Hovered, "UI", "BtnHovered", false, "Main/ui_change_selection.wav");
	m_ExitButton->SetSound(EButtonEventState::Click, "UI", "BtnClick", false, "Main/ui_button_confirm.wav");
	
	for (int i = 0; i < 4; i++)
	{
		std::string s = "Cursor";
		s += i;
		m_Cursor[i] = CreateWidget<CUIImage>(s);
		m_Cursor[i]->SetSize(49.5f, 36.f);
		m_Cursor[i]->SetPivot(0.5f, 0.5f);
		m_Cursor[i]->SetTexture(s, TEXT("HollowKnight/MainTitle/Pointer Down_000.png"));
	}

	m_Cursor[0]->SetPos(550.f, 230.f);
	m_Cursor[1]->SetPos(720.f, 230.f);
	m_Cursor[1]->SetAngle(180.f);
	
	m_Cursor[2]->SetPos(550.f, 130.f);
	m_Cursor[3]->SetPos(720.f, 130.f);
	m_Cursor[3]->SetAngle(180.f);

	return true;
}

void CMainTitleUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
	if (m_StartButton->GetMouseHovered())
	{
		m_Cursor[0]->SetEnable(true);
		m_Cursor[1]->SetEnable(true);
	}
	else if (m_ExitButton->GetMouseHovered())
	{
		m_Cursor[2]->SetEnable(true);
		m_Cursor[3]->SetEnable(true);
	}
	else
	{
		for (int i = 0; i < 4; i++)
			m_Cursor[i]->SetEnable(false);
	}
}

void CMainTitleUI::PostUpdate(float DeltaTime)
{
	CUIWindow::PostUpdate(DeltaTime);
}

void CMainTitleUI::Render()
{
	CUIWindow::Render();
}

CMainTitleUI* CMainTitleUI::Clone()
{
	return new CMainTitleUI(*this);
}

void CMainTitleUI::Save(FILE* File)
{
	CUIWindow::Save(File);
}

void CMainTitleUI::Load(FILE* File)
{
	CUIWindow::Load(File);

	//구현
	m_StartButton = FindWidget<CUIButton>("Button");
}

void CMainTitleUI::StartButtonClick()
{
	OutputDebugStringA("Main Test");

	//CSceneManager::GetInst()->CreateNextScene(true);
	//CSceneManager::GetInst()->ChangeNextScene();

	CSceneManager::GetInst()->CreateNextScene(true);
	CSceneManager::GetInst()->CreateSceneInfo<CLoadingSceneInfo>(false);
}

void CMainTitleUI::ExitButtonClick()
{
	OutputDebugStringA("Exit");
	CResourceManager::GetInst()->SoundStop("MainTitle");

}
