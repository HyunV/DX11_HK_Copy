#include "SectionWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorCheckBox.h"

CSectionWindow::CSectionWindow()
{
}

CSectionWindow::~CSectionWindow()
{
}

bool CSectionWindow::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("Collider Section");
	Label->SetColor(255, 0, 0, 255);
	Label->SetSize(250.f, 30.f);

	m_SelectScene = CreateWidget<CEditorInput>("Select Scene");

	CEditorText* textX = CreateWidget<CEditorText>("textX");
	textX->SetText("X: ");

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	m_InputX = CreateWidget<CEditorInput>("InputX");
	m_InputX->SetHideName("InputX");
	m_InputX->SetInputType(EImGuiInputType::Int);

	CEditorText* textY = CreateWidget<CEditorText>("textY");
	textY->SetText("Y: ");

	Line = CreateWidget<CEditorSameLine>("Line");

	m_InputY = CreateWidget<CEditorInput>("InputY");
	m_InputY->SetHideName("InputY");
	m_InputY->SetInputType(EImGuiInputType::Int);


	CEditorText* textCount = CreateWidget<CEditorText>("textCount");
	textCount->SetText("Section Index Count");

	Line = CreateWidget<CEditorSameLine>("Line");

	m_IndexCount = CreateWidget<CEditorInput>("IndexCount");
	m_IndexCount->SetHideName("IndexCount");
	m_IndexCount->SetInputType(EImGuiInputType::Int);
	m_IndexCount->ReadOnly(true);
	
	CEditorButton* ConfirmButton = CreateWidget<CEditorButton>("적용");
	ConfirmButton->SetClickCallback<CSectionWindow>
		(this, &CSectionWindow::ConfirmBtnCallback);

	Line = CreateWidget<CEditorSameLine>("Line");
	m_isPreview = CreateWidget<CEditorCheckBox>("isPreview");
	
	return true;
}

void CSectionWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CSectionWindow::ConfirmBtnCallback()
{
	OutputDebugStringA("확인버튼");
	m_IndexCount->SetInt(m_InputX->GetInt() * m_InputY->GetInt());
}
