#include "MyAnimationWindow.h"

#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorGroup.h"

#include "Animation/Animation2D.h"

//#include "PathManager.h"
//#include "Engine.h"

CMyAnimationWindow::CMyAnimationWindow()
{
}

CMyAnimationWindow::~CMyAnimationWindow()
{
}

bool CMyAnimationWindow::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("애니메이션 툴");
	Label->SetColor(255, 0, 0, 255);
	Label->SetSize(150.f, 30.f);

	m_Messege = CreateWidget<CEditorText>("Messege");
	m_Messege->SetText("* Messege");
	m_Messege->SetColor(0, 255, 0, 255);
	m_Messege->SetSize(250.f, 30.f);

	m_LoadAnimCombo = CreateWidget<CEditorComboBox>("Combo", 250.f, 30.f);
	m_LoadAnimCombo->SetSelectPrevViewName(true);
	m_LoadAnimCombo->SetHideName("Combo");
	m_LoadAnimCombo->SetPrevViewName("애니메이션 선택");
	m_LoadAnimCombo->AddItem("새로 만들기..");
	m_LoadAnimCombo->SetSelectCallback<CMyAnimationWindow>
		(this, &CMyAnimationWindow::ComboBoxCallback);
	
	m_EventList = CreateWidget<CEditorListBox>("List");
	m_EventList->SetHideName("List");
	m_EventList->SetPageItemCount(12);
	m_EventList->SetSize(150.f, 300.f);
	m_EventList->SetSelectCallback<CMyAnimationWindow>
		(this, &CMyAnimationWindow::ListCallback);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	//====================그룹===============================
	CEditorGroup* Group = CreateWidget<CEditorGroup>("Group");

	CEditorButton* LoadSqcBtn = Group->CreateWidget<CEditorButton>("시퀀스 추가", 100.f, 30.f);
	LoadSqcBtn->SetClickCallback<CMyAnimationWindow>
		(this, &CMyAnimationWindow::LoadSqcBtnCallback);

	CEditorButton* DeleteSqcBtn = Group->CreateWidget<CEditorButton>("시퀀스 제거", 100.f, 30.f);
	DeleteSqcBtn->SetClickCallback<CMyAnimationWindow>
		(this, &CMyAnimationWindow::DeleteSqcBtnCallback);

	m_SelectedSqcText = CreateWidget<CEditorText>("SelectedSequence");
	m_SelectedSqcText->SetText("");
	m_SelectedSqcText->SetColor(0, 255, 0, 255);
	//m_SelectedSqcText->SetSize(250.f, 30.f);
	
	m_PlayTimeInput =CreateWidget<CEditorInput>("PlayTime");
	m_PlayTimeInput->SetInputType(EImGuiInputType::Float);

	m_PlayScaleInput = CreateWidget<CEditorInput>("PlayScale");
	m_PlayScaleInput->SetInputType(EImGuiInputType::Float);

	m_FrameTime = CreateWidget<CEditorInput>("FrameTime");
	m_FrameTime->SetInputType(EImGuiInputType::Float);

	m_Loop = CreateWidget<CEditorCheckBox>("                  Loop");
	m_Reverse = CreateWidget<CEditorCheckBox>("                  Reverse");

	Label = CreateWidget<CEditorLabel>("Label");
	Label->SetHideName("Label");
	Label->SetColor(0, 0, 0, 0);
	
	m_SaveAnimationInput = CreateWidget<CEditorInput>("SaveAnimation");
	m_SaveAnimationInput->SetHideName("SaveAnimation");
	m_SaveAnimationInput->SetSizeX(150.f);
	m_SaveAnimationInput->SetHintText("애니메이션 파일명");

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* SaveAnimBtn = CreateWidget<CEditorButton>("변경 및 저장");
	SaveAnimBtn->SetClickCallback<CMyAnimationWindow>(this, &CMyAnimationWindow::SaveBtnCallback);

	//세팅

	SetComboBox();

	return true;
}

void CMyAnimationWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CMyAnimationWindow::ClearSetting()
{
}

void CMyAnimationWindow::SetComboBox()
{

}

void CMyAnimationWindow::SetList()
{
}

void CMyAnimationWindow::ComboBoxCallback(int SelectIndex, const std::string& Item)
{
	OutputDebugStringA(Item.c_str());
}

void CMyAnimationWindow::ListCallback(int SelectIndex, const std::string& Item)
{
	OutputDebugStringA(Item.c_str());
}

void CMyAnimationWindow::LoadSqcBtnCallback()
{
}

void CMyAnimationWindow::DeleteSqcBtnCallback()
{
}

void CMyAnimationWindow::SaveBtnCallback()
{
}
