#include "TestWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"

CTestWindow::CTestWindow()
{
}

CTestWindow::~CTestWindow()
{
}

bool CTestWindow::Init()
{
	CEditorButton* Btn = CreateWidget<CEditorButton>("��ư");

	Btn->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);
	
	CEditorSameLine* SameLine = CreateWidget<CEditorSameLine>("Line");

	//SameLine->SetOffsetX(100.f);
	SameLine->SetSpacing(100.f);

	Btn = CreateWidget<CEditorButton>("TestButton1");

	Btn->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);

	CEditorLabel* Label = CreateWidget<CEditorLabel>("�渶����");

	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(1.f, 1.f);

	//�̰� ���� Ƽ�� ������ �ƴϰ� ������ ������
	SameLine = CreateWidget<CEditorSameLine>("Line");

	CEditorImage* Image = CreateWidget<CEditorImage>("Image");

	Image->SetTexture("BlackMagiction", TEXT("teemo.png"));
	

	return true;
}

void CTestWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CTestWindow::TestButtonCallback()
{
	MessageBox(0, TEXT("Button"), TEXT("��ƮƮƮƮư"), MB_OK);
}
