#include "TestWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorSliderBar.h"
#include "Editor/EditorCheckBox.h"

CTestWindow::CTestWindow()	:
	m_AddText{},
	m_AddIndex(0),
	m_AddCount(0),
	m_AddTime(0.f)
{
}

CTestWindow::~CTestWindow()
{
}

bool CTestWindow::Init()
{
	CEditorButton* Btn = CreateWidget<CEditorButton>("버튼");

	Btn->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);
	
	CEditorSameLine* SameLine = CreateWidget<CEditorSameLine>("Line");

	//SameLine->SetOffsetX(100.f);
	SameLine->SetSpacing(100.f);

	Btn = CreateWidget<CEditorButton>("TestButton1");

	Btn->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);

	CEditorLabel* Label = CreateWidget<CEditorLabel>("흑마법사");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(1.f, 1.f);

	//이걸 빼면 티모가 옆에가 아니고 밑으로 내려감
	SameLine = CreateWidget<CEditorSameLine>("Line");

	CEditorImage* Image = CreateWidget<CEditorImage>("Image");

	Image->SetTexture("BlackMagiction", TEXT("teemo.png"));

	//텍스트

	m_Text = CreateWidget<CEditorText>("Text");

	m_Text->SetText("작심하루");
	m_Text->SetColor(255, 0, 0, 255);

	strcpy_s(m_AddText, "F는 Fire 마을을 불태우지");

	m_AddCount = (int)strlen(m_AddText);

	m_Input = CreateWidget<CEditorInput>("Input");

	m_Input->SetHideName("Input");
	//m_Input->SetMultiLine(true);
	//m_Input->ReadOnly(true); //수정 가능 여부
	//m_Input->PasswordMode(true); //*로 뜨게
	//m_Input->SetInputType(EImGuiInputType::Int); //숫자만 가능?
	m_Input->SetInputType(EImGuiInputType::Float);

	m_Input->SetInputCallback<CTestWindow>(this, &CTestWindow::InputCallback);
	
	//리스트박스
	m_List = CreateWidget<CEditorListBox>("ListBox");

	m_List->SetHideName("ListBox");

	m_List->AddItem("List1");
	m_List->AddItem("List2");
	m_List->AddItem("List3");
	m_List->AddItem("List4");
	m_List->SetSize(120.f, 150.f);

	m_List->SetSelectCallback<CTestWindow>(this, &CTestWindow::ListCallback);

	//콤보박스
	m_Combo = CreateWidget<CEditorComboBox>("ComboBox");
	
	m_Combo->SetSelectPrevViewName(true);

	m_Combo->SetHideName("ComboBox");
	m_Combo->SetPrevViewName("흑마법사");

	m_Combo->AddItem("Combo1");
	m_Combo->AddItem("Combo2");
	m_Combo->AddItem("Combo3");
	m_Combo->AddItem("Combo4");

	m_Combo->SetSelectCallback<CTestWindow>(this, &CTestWindow::ListCallback);

	//트리
	m_Tree = CreateWidget<CEditorTree<int>>("Tree");

	m_Tree->SetHideName("Tree");

	m_Tree->AddItem(0, "Root");
	m_Tree->AddItem(0, "진짜 최상위 부모");
	m_Tree->AddItem(0, "자식1", "진짜 최상위 부모");
	m_Tree->AddItem(0, "자식2", "Root");
	m_Tree->AddItem(0, "자식3", "자식2");

	m_Tree->SetSelectCallback<CTestWindow>(this, &CTestWindow::TreeCallback);

	//슬라이더 바
	CEditorSliderBar* Slide = CreateWidget<CEditorSliderBar>("슬라이드");
	//Slide->SetClickCallback<CTestWindow>(this, &CTestWindow::SliderCallback);

	//체크박스
	m_Check = CreateWidget<CEditorCheckBox>("쳌박");
	m_Check->SetHideName("쳌박");
	//m_Check->SetClickCallback<CTestWindow>(this, &CTestWindow::CheckCallback);

	return true;
}

void CTestWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_AddIndex < m_AddCount)
	{
		m_AddTime += DeltaTime;

		if (m_AddTime >= 1.f) //1초 지나면 
		{
			m_AddTime -= 1.f; //1초 빼주고

			char	Text[2] = {};
			Text[0] = m_AddText[m_AddIndex]; //해당 텍스트의 n번째 인덱스 문자를 넣어줌

			m_Text->AddText(Text); //그 문자 추가

			++m_AddIndex;
		}
	}
}

void CTestWindow::TestButtonCallback()
{
	MessageBox(0, TEXT("Button"), TEXT("버트트트트튼"), MB_OK);
}

void CTestWindow::InputCallback()
{
	char	Text[256] = {};

	sprintf_s(Text, "%.5f\n", m_Input->GetFloat());

	OutputDebugStringA(Text);
}

void CTestWindow::ListCallback(int SelectIndex, const std::string& Item)
{
	char	Text[256] = {};

	sprintf_s(Text, "%d : %s\n", SelectIndex, Item.c_str());

	OutputDebugStringA(Text);
}

void CTestWindow::TreeCallback(CEditorTreeItem<int>* Node, const std::string& Item)
{
	char	Text[256] = {};

	sprintf_s(Text, "%s\n", Item.c_str());

	OutputDebugStringA(Text);
}

void CTestWindow::SliderCallback()
{	
	OutputDebugStringA("Test");
}


