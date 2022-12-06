#include "MessageBoxUI.h"
#include "UI/UIText.h"
#include "UI/UIImage.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "../GameObject/Player2D.h"

CMessageBoxUI::CMessageBoxUI()
{
	m_WindowTypeName = "MessageBoxUI";
}

CMessageBoxUI::CMessageBoxUI(const CMessageBoxUI& Window)	:
	CUIWindow(Window)
{
}

CMessageBoxUI::~CMessageBoxUI()
{	
	CInput::GetInst()->DeleteBindFunction("Space", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction("Z", Input_Type::Down, this);
	CInput::GetInst()->DeleteBindFunction("X", Input_Type::Down, this);
}

void CMessageBoxUI::Start()
{
	CUIWindow::Start();
}

bool CMessageBoxUI::Init()
{
	CUIWindow::Init();

	CUIImage* MsgBox = CreateWidget<CUIImage>("MsgBox");
	MsgBox->SetTexture("MsgBox", TEXT("HollowKnight/NPCS/Dir/MessegeBox.png"));
	MsgBox->SetPivot(0.5f, 0.5f);
	MsgBox->SetSize(840.f, 225.f);
	MsgBox->SetPos(640.f, 550.f);
	MsgBox->SetOpacity(0.8f);

	CUIImage* MsgFrameUp = CreateWidget<CUIImage>("MsgFrameUp");
	MsgFrameUp->SetTexture("MsgFrameUp", TEXT("HollowKnight/NPCS/Dir/DirUp.png"));
	MsgFrameUp->SetPivot(0.5f, 0.5f);
	MsgFrameUp->SetSize(619.f* g_SCALE, 90.f * g_SCALE);
	MsgFrameUp->SetPos(640.f, 665.f);

	CUIImage* MsgFrameDown = CreateWidget<CUIImage>("MsgFrameDown");
	MsgFrameDown->SetTexture("MsgFrameDown", TEXT("HollowKnight/NPCS/Dir/DirDown.png"));
	MsgFrameDown->SetPivot(0.5f, 0.5f);
	MsgFrameDown->SetSize(424.f * g_SCALE, 70.f * g_SCALE);
	MsgFrameDown->SetPos(640.f, 440.f);

	CUIImage* MsgCursor = CreateWidget<CUIImage>("MsgCursor");
	MsgCursor->SetTexture("MsgCursor", TEXT("HollowKnight/NPCS/Dir/CurDown.png"));
	MsgCursor->SetPivot(0.5f, 0.5f);
	MsgCursor->SetSize(32.f, 46.f);
	MsgCursor->SetPos(640.f, 435.f);

	for (int i = 0; i < 12; i++)
	{
		MsgCursor->AddFrameData(Vector2(i * 32.f, 0.f), Vector2((i + 1) * 32.f, 46.f));
	}
	MsgCursor->SetPlayTime(100.f);
	MsgCursor->SetPlayScale(1.f);

	m_NPCName = CreateWidget<CUIText>("NPCName");
	m_NPCName->SetText(TEXT("���� ����"));
	m_NPCName->SetAlignH(Text_Align_H::Left);
	m_NPCName->SetFontSize(50.f);
	m_NPCName->SetSize(250.f, 100.f);
	m_NPCName->SetPos(70.f, 20.f);
	m_NPCName->SetShadowEnable(true);
	m_NPCName->SetShadowColor(0, 0, 0);

	
	CInput::GetInst()->AddBindFunction<CMessageBoxUI>("Space", Input_Type::Down, this,
		&CMessageBoxUI::CloseBox, m_Scene);
	CInput::GetInst()->AddBindFunction<CMessageBoxUI>("Z", Input_Type::Down, this,
		&CMessageBoxUI::CloseBox, m_Scene);
	CInput::GetInst()->AddBindFunction<CMessageBoxUI>("X", Input_Type::Down, this,
		&CMessageBoxUI::CloseBox, m_Scene);


	return true;
}

void CMessageBoxUI::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);
}

void CMessageBoxUI::Render()
{
	CUIWindow::Render();
}

void CMessageBoxUI::ElderBugMessage()
{
	CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
	player->m_KeyLock = true;

	m_NPCName->SetText(TEXT("��ι���"));
	CUIText* Text1 = CreateWidget<CUIText>("TextElder");
	Text1->SetAlignH(Text_Align_H::Left);
	Text1->SetFontSize(16.f);
	Text1->SetSize(820.f, 225.f);
	Text1->SetPos(450.f, 410.f);
	Text1->SetShadowEnable(true);
	Text1->SetShadowColor(0, 0, 0);
	Text1->SetText(TEXT("������ ���۹��� �˷��ְڼ�...\n\
	�� ����Ű�� �̵�\n\
	�� Z: ����, ��������\n\
	�� X: ����(����Ű�� ���� ���� ���� ����)\n\
	�� C: ���\n\
	�� V: ü�� ȸ��(�ٸ� �ൿ �� ĵ��)\n\
	�� SPACE : ��������(��Ÿ�� 3��)\n"));
}

void CMessageBoxUI::HonnetMessage()
{
	CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
	player->m_KeyLock = true;

	m_NPCName->SetText(TEXT("ȣ��"));
	CUIText* Text1 = CreateWidget<CUIText>("TextHonnet");
	Text1->SetAlignH(Text_Align_H::Center);
	Text1->SetFontSize(36.f);
	Text1->SetSize(820.f, 225.f);
	Text1->SetPos(230.f, 410.f);
	Text1->SetShadowEnable(true);
	Text1->SetShadowColor(0, 0, 0);
	Text1->SetText(TEXT("�� ���� �������̾�. \n���� �� �� ������\n������ ƴ�� ����ġ�°� �����ž�."));
}

void CMessageBoxUI::BrumMessage()
{
	CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
	player->m_KeyLock = true;

	m_NPCName->SetText(TEXT("�귳"));
	CUIText* Text1 = CreateWidget<CUIText>("TextHonnet");
	Text1->SetAlignH(Text_Align_H::Center);
	Text1->SetFontSize(36.f);
	Text1->SetSize(820.f, 225.f);
	Text1->SetPos(230.f, 410.f);
	Text1->SetShadowEnable(true);
	Text1->SetShadowColor(0, 0, 0);
	Text1->SetText(TEXT("�츮 ������� �̱�� ������ �� �� �־�.\n������ �װ� �����ұ�? Ǫ����!"));
}

void CMessageBoxUI::CloseBox()
{
	OutputDebugStringA("�޽��� �ݱ�");
	CPlayer2D* player = (CPlayer2D*)(m_Scene->FindObject("Player2D"));
	player->m_KeyLock = false;
	player->SetNextState();
	Destroy();
}
