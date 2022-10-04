#include "NMyAnimationWindow2.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorCheckBox.h"

#include "Component/SpriteComponent.h"
#include "PathManager.h"
#include "Animation/Animation2DData.h"
#include "Animation/Animation2D.h"
#include "Engine.h"
#include "Component/SceneComponent.h"
//#include "Resource/ResourceManager.h"
//#include "Resource/Animation/AnimationManager.h"

CNMyAnimationWindow2::CNMyAnimationWindow2()
{
}

CNMyAnimationWindow2::~CNMyAnimationWindow2()
{
	//CDO ����?
}

bool CNMyAnimationWindow2::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("�ִϸ��̼� ��");
	Label->SetColor(255, 0, 0, 255);
	Label->SetSize(250.f, 30.f);	

	//CEditorLabel* HiddenLabel = CreateWidget<CEditorLabel>("�޽��� ��");
	//HiddenLabel->SetColor(1, 1, 1, 1);
	//HiddenLabel->SetHideName("�޽��� ��");
	// Line = CreateWidget<CEditorSameLine>("Line");

	m_SaveMessege = CreateWidget<CEditorText>("Messege");
	m_SaveMessege->SetText("* Messege");
	m_SaveMessege->SetColor(0, 255, 0, 255);
	m_SaveMessege->SetSize(250.f, 30.f);
	//m_SaveMessege->SetAlign(0.5f, 0.5f);
	
	CEditorButton* LoadAnimationButton = CreateWidget<CEditorButton>("Load Animation");
	LoadAnimationButton->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::LoadAnimationCallback);
	
	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* SaveAnimationButton = CreateWidget<CEditorButton>("����");
	SaveAnimationButton->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::SaveAnimationCallback);

	
	m_ActName = CreateWidget<CEditorInput>("ActName");
	m_ActName->SetHideName("ActName");
	m_ActName->SetHintText("�ൿ��");

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* AddAnimationActButton = CreateWidget<CEditorButton>("�ൿ �߰�");
	AddAnimationActButton->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::AddActCallback);
	


	CEditorLabel* Label2 = CreateWidget<CEditorLabel>("�ൿ ���");
	Label2->SetColor(255, 0, 0, 255);
	Label2->SetAlign(0.5f, 0.5f);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorLabel* Label3 = CreateWidget<CEditorLabel>("������ ����");
	Label3->SetColor(255, 0, 0, 255);
	Label3->SetAlign(0.5f, 0.5f);
	
	m_AniList = CreateWidget<CEditorListBox>("�ִϸ��̼� �ൿ");
	m_AniList->SetHideName("�ִϸ��̼� �ൿ");
	m_AniList->SetPageItemCount(5);
	m_AniList->SetSelectCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::SelectActCallback);

	Line = CreateWidget<CEditorSameLine>("Line");
	m_SqcList = CreateWidget<CEditorListBox>("������ ���");
	m_SqcList->SetHideName("������ ���");
	m_SqcList->SetPageItemCount(5);
	m_SqcList->SetSelectCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::SelectSqcCallback);

	CEditorButton* NewAnimation = CreateWidget<CEditorButton>("�ִϸ��̼� ����(������Ʈ �޾ƿ���)");
	NewAnimation->SetSize(250.f, 30);
	NewAnimation->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::CreateAnimationCallback);

	CEditorLabel* Label4 = CreateWidget<CEditorLabel>("����");
	Label4->SetColor(255, 0, 0, 255);
	Label4->SetAlign(0.5f, 0.5f);
	Label4->SetSize(250.f, 30.f);

	m_AnimationName = CreateWidget<CEditorInput>("File Name");
	m_AnimationName->SetHintText("�ִϸ��̼� ���ϸ�");

	m_SelectedComponent = CreateWidget<CEditorInput>("Sprite Only");
	m_SelectedComponent->ReadOnly(true);
	m_SelectedComponent->SetHintText("������Ʈ ����");

	m_SelectAct = CreateWidget<CEditorInput>("Select Act");
	m_SelectAct->ReadOnly(true);
	m_SelectAct->SetHintText("�ൿ ����");

	m_SelectSqc = CreateWidget<CEditorInput>("Select Seq");
	m_SelectSqc->ReadOnly(true);
	m_SelectSqc->SetHintText("������ ����");

	m_PlayTime = CreateWidget<CEditorInput>("PlayTime ");
	m_PlayTime->SetInputType(EImGuiInputType::Float);
	m_PlayTime->SetFloat(1.f);

	Line = CreateWidget<CEditorSameLine>("Line");
	m_Loop = CreateWidget<CEditorCheckBox>("Loop");

	m_PlayScale = CreateWidget<CEditorInput>("PlayScale");
	m_PlayScale->SetInputType(EImGuiInputType::Float);
	m_PlayScale->SetFloat(1.f);

	Line = CreateWidget<CEditorSameLine>("Line");
	m_Reverse = CreateWidget<CEditorCheckBox>("Reverse");

	CEditorButton* NewActButton = CreateWidget<CEditorButton>("�ִϸ��̼� �߰�/����");
	NewActButton->SetSize(250.f, 30);
	NewActButton->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::AddActAnimationCallback);

	//
	LoadSqc();
	return true;
}

void CNMyAnimationWindow2::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
	//��������Ʈ �̹��� ������Ʈ
}

void CNMyAnimationWindow2::SetSelectComponent(const std::string& Item, CSceneComponent* Component)
{
	//m_SpriteComponent = (CSpriteComponent*)Component;
	if (Component && Component->GetComponentTypeName() == "SpriteComponent")
	{
		//m_SelectComponent = Component;
		//m_SpriteComponent
		m_SelectedComponent->SetText(Component->GetName().c_str());
	}
	else
		return;
}

void CNMyAnimationWindow2::LoadSqc()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Sequence/");

	//������ ���� �� �ִ� ��� ���� �ε�
	for (const auto& file : std::filesystem::directory_iterator(FullPath))
	{
		char FileName[64] = {};
		char MaxPath[MAX_PATH] = {};
		char Ext[_MAX_EXT] = {};

		strcpy_s(MaxPath, file.path().generic_string().c_str());
		_splitpath_s(MaxPath, nullptr, 0, nullptr, 0, FileName, 64, Ext, _MAX_EXT);

		m_SqcList->AddItem(FileName);
		m_vecSqc.push_back(FileName);
	}
}

void CNMyAnimationWindow2::ResetSetting()
{
	m_Animation = nullptr;
	m_SpriteComponent = nullptr;

	m_AniList->Clear();
	m_vecAct.clear();

	m_ActName->SetText("");
	m_SaveMessege->SetText("");

	m_AnimationName->SetText("");
	m_SelectedComponent->SetText("");
	m_SelectAct->SetText("");
	m_SelectSqc->SetText("");

	m_PlayTime->SetFloat(1.f);
	m_PlayScale->SetFloat(1.f);
	m_Loop->SetCheck(false);
	m_Reverse->SetCheck(false);
	//������ ����
}

void CNMyAnimationWindow2::LoadAnimationCallback()
{
	OutputDebugStringA("�ִϸ��̼� �ε�");

	OPENFILENAME	ofn = {};

	TCHAR	FullPath[256] = {};

	TCHAR	Filter[] = TEXT("��� ����\0*.*");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = 256;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(ROOT_PATH)->Path;
	//ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	if (0 != GetOpenFileName(&ofn))
	{
		ResetSetting(); //������ �ʱ�ȭ

		int len = 256;
		char temp[256];

		WideCharToMultiByte(CP_ACP, 0, FullPath, len, temp, len, 0, 0);
		printf("%s", temp);

		FILE* File = nullptr;
		fopen_s(&File, temp, "rb");

		if (!File)
			return;

		//CAnimation2D* ani = new CAnimation2D();
		m_Animation = m_Animation->FindCDO("Animation2D");
		m_Animation->Load(File);

		fclose(File);
		//##�ε� ����

		std::string s = m_Animation->GetName();
		//������ �ٽ� ä���ֱ�
		//m_SpriteComponent = m_Animation->GetOwner;
		//m_SelectedComponent->SetText("��");
		
		m_AnimationName->SetText(s.c_str());

		//m_PlayTime->SetFloat(1.f);
		//m_PlayScale->SetFloat(1.f);
		//m_Loop->SetCheck(false);
		//m_Reverse->SetCheck(false);
		

		//�ൿ��� �޾ƿ���
		std::vector<std::string> v;
		v = m_Animation->GetAnimationList();
		for(int i = 0; i<v.size(); i++)
		{
			m_AniList->AddItem(v[i]);
			m_vecAct.push_back(v[i]);
		}
	}
	m_SaveMessege->SetText("�ҷ����� ����");
}

void CNMyAnimationWindow2::AddActCallback()
{
	if (!m_Animation)
	{
		m_SaveMessege->SetText("! �ִϸ��̼��� �����ϰų� �ҷ����ּ���");
		return;
	}
	OutputDebugStringA("�ൿ�߰�");
	std::string Name = m_ActName->GetText();
	if (Name == "")
	{
		m_SaveMessege->SetText("! �ൿ �̸��� �����ּ���");
	}else{	
		for (int i = 0; i < m_vecAct.size(); i++)
		{
			if (Name == m_vecAct[i]) 
			{
				m_SaveMessege->SetText("! �ߺ����̸�");
				return;
			}				
		}
		m_AniList->AddItem(Name);
		m_vecAct.push_back(Name);
		m_SaveMessege->SetText("�߰� �Ϸ�!");
	}			
}

void CNMyAnimationWindow2::SaveAnimationCallback()
{
	OutputDebugStringA("�����ư");

	if (!m_Animation) 
	{
		m_SaveMessege->SetText("������ �ִϸ��̼��� �������� �ʽ��ϴ�.");
		return;
	}
	else
	{
		const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);
		std::string FileName = m_Animation->GetName();

		if (FileName == "")
			return;

		char FullPath[MAX_PATH] = {};

		if (Info)
			strcpy_s(FullPath, Info->PathMultibyte);

		strcat_s(FullPath, "AnimationData/");
		strcat_s(FullPath, FileName.c_str());
		strcat_s(FullPath, ".anm");

		FILE* File = nullptr;
		fopen_s(&File, FullPath, "wb");

		if (!File)
			return;

		m_Animation->Save(File);
		m_SaveMessege->SetText("���� �Ϸ�!");
		fclose(File);
	}
}

void CNMyAnimationWindow2::CreateAnimationCallback()
{
	OutputDebugStringA("�ִϸ��̼� ����");
	std::string s = m_AnimationName->GetText();
	if (s == "")
	{
		m_SaveMessege->SetText("! ���� �̸��� �����ּ���");
	}
	else if(!m_SpriteComponent)
	{
		m_SaveMessege->SetText("�ִϸ��̼ǿ� ����� ������Ʈ�� �ҷ��� �ּ���");
	}
	else if(m_Animation)
	{
		m_SaveMessege->SetText("�̹� �ִϸ��̼��� �����Ͽ����ϴ�.");
		
	}
	else
	{
		//�ִϸ��̼� ��ü ����
		m_SaveMessege->SetText("�ִϸ��̼� ����!");
		//(CSpriteComponent*)m_SelectComponent;
		m_Animation = m_SpriteComponent->SetAnimation<CAnimation2D>(s);
		m_AnimationName->ReadOnly(true);
	}
}

void CNMyAnimationWindow2::AddActAnimationCallback()
{

	OutputDebugStringA("�ִϸ��̼ǿ� �߰�");
	//Act�� ������ ������ �߰��ϰ� ������ ����
	//�߰�
	//�ൿ(�̸�), ����������, (�� �̸����� �˻�), ��Ž, �÷��̽�����, ����, ������
	std::string ActName = m_SelectAct->GetText();
	std::string SeqName = m_SelectSqc->GetText();
	float PlayTime = m_PlayTime->GetFloat();
	float PlayScale = m_PlayScale->GetFloat();
	bool Loop = m_Loop->GetCheck();
	bool Reverse = m_Reverse->GetCheck();
	
	if (ActName == "" || SeqName == "")
	{
		m_SaveMessege->SetText("������ ä���ּ���");
		return;
	}
	//CAnimation2DData* AnimData = FindAnimation(ActName);
	m_Animation->AddAnimation(ActName, SeqName, PlayTime, PlayScale, Loop, Reverse);
	m_Animation->SetCurrentAnimation(ActName);
	
	m_SaveMessege->SetText("�߰�/���� �Ϸ�");
}

void CNMyAnimationWindow2::SelectActCallback(int SelectIndex, const std::string& Item)
{
	OutputDebugStringA("�ൿ ����");
	m_SelectAct->SetText(Item.c_str());
	
	
	if (m_Animation)
	{
		m_Animation->SetCurrentAnimation(Item);
		//���� ������ ��ϵ� ������ ������ �����´�.
		CAnimationSequence2D* sqc = m_Animation->GetCurrentAnimationSequence(Item);
		
		if(sqc)
			m_SelectSqc->SetText(sqc->GetName().c_str());
	}
}

void CNMyAnimationWindow2::SelectSqcCallback(int SelectIndex, const std::string& Item)
{
	OutputDebugStringA("������ ����");
	m_SelectSqc->SetText(Item.c_str());
}
