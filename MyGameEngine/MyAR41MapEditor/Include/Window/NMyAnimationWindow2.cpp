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
	//CDO 제거?
}

bool CNMyAnimationWindow2::Init()
{
	CEditorLabel* Label = CreateWidget<CEditorLabel>("애니메이션 툴");
	Label->SetColor(255, 0, 0, 255);
	Label->SetSize(250.f, 30.f);	

	//CEditorLabel* HiddenLabel = CreateWidget<CEditorLabel>("메시지 라벨");
	//HiddenLabel->SetColor(1, 1, 1, 1);
	//HiddenLabel->SetHideName("메시지 라벨");
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

	CEditorButton* SaveAnimationButton = CreateWidget<CEditorButton>("저장");
	SaveAnimationButton->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::SaveAnimationCallback);

	
	m_ActName = CreateWidget<CEditorInput>("ActName");
	m_ActName->SetHideName("ActName");
	m_ActName->SetHintText("행동명");

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* AddAnimationActButton = CreateWidget<CEditorButton>("행동 추가");
	AddAnimationActButton->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::AddActCallback);
	


	CEditorLabel* Label2 = CreateWidget<CEditorLabel>("행동 목록");
	Label2->SetColor(255, 0, 0, 255);
	Label2->SetAlign(0.5f, 0.5f);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorLabel* Label3 = CreateWidget<CEditorLabel>("시퀀스 파일");
	Label3->SetColor(255, 0, 0, 255);
	Label3->SetAlign(0.5f, 0.5f);
	
	m_AniList = CreateWidget<CEditorListBox>("애니메이션 행동");
	m_AniList->SetHideName("애니메이션 행동");
	m_AniList->SetPageItemCount(5);
	m_AniList->SetSelectCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::SelectActCallback);

	Line = CreateWidget<CEditorSameLine>("Line");
	m_SqcList = CreateWidget<CEditorListBox>("시퀀스 목록");
	m_SqcList->SetHideName("시퀀스 목록");
	m_SqcList->SetPageItemCount(5);
	m_SqcList->SetSelectCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::SelectSqcCallback);

	CEditorButton* NewAnimation = CreateWidget<CEditorButton>("애니메이션 생성(컴포넌트 받아오기)");
	NewAnimation->SetSize(250.f, 30);
	NewAnimation->SetClickCallback<CNMyAnimationWindow2>
		(this, &CNMyAnimationWindow2::CreateAnimationCallback);

	CEditorLabel* Label4 = CreateWidget<CEditorLabel>("편집");
	Label4->SetColor(255, 0, 0, 255);
	Label4->SetAlign(0.5f, 0.5f);
	Label4->SetSize(250.f, 30.f);

	m_AnimationName = CreateWidget<CEditorInput>("File Name");
	m_AnimationName->SetHintText("애니메이션 파일명");

	m_SelectedComponent = CreateWidget<CEditorInput>("Sprite Only");
	m_SelectedComponent->ReadOnly(true);
	m_SelectedComponent->SetHintText("컴포넌트 선택");

	m_SelectAct = CreateWidget<CEditorInput>("Select Act");
	m_SelectAct->ReadOnly(true);
	m_SelectAct->SetHintText("행동 선택");

	m_SelectSqc = CreateWidget<CEditorInput>("Select Seq");
	m_SelectSqc->ReadOnly(true);
	m_SelectSqc->SetHintText("시퀀스 선택");

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

	CEditorButton* NewActButton = CreateWidget<CEditorButton>("애니메이션 추가/변경");
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
	//스프라이트 이미지 업데이트
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

	//시퀀스 폴더 내 있는 모든 파일 로드
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
	//설정들 리셋
}

void CNMyAnimationWindow2::LoadAnimationCallback()
{
	OutputDebugStringA("애니메이션 로드");

	OPENFILENAME	ofn = {};

	TCHAR	FullPath[256] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = 256;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(ROOT_PATH)->Path;
	//ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	if (0 != GetOpenFileName(&ofn))
	{
		ResetSetting(); //에디터 초기화

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
		//##로딩 성공

		std::string s = m_Animation->GetName();
		//에디터 다시 채워넣기
		//m_SpriteComponent = m_Animation->GetOwner;
		//m_SelectedComponent->SetText("컴");
		
		m_AnimationName->SetText(s.c_str());

		//m_PlayTime->SetFloat(1.f);
		//m_PlayScale->SetFloat(1.f);
		//m_Loop->SetCheck(false);
		//m_Reverse->SetCheck(false);
		

		//행동목록 받아오기
		std::vector<std::string> v;
		v = m_Animation->GetAnimationList();
		for(int i = 0; i<v.size(); i++)
		{
			m_AniList->AddItem(v[i]);
			m_vecAct.push_back(v[i]);
		}
	}
	m_SaveMessege->SetText("불러오기 성공");
}

void CNMyAnimationWindow2::AddActCallback()
{
	if (!m_Animation)
	{
		m_SaveMessege->SetText("! 애니메이션을 생성하거나 불러와주세요");
		return;
	}
	OutputDebugStringA("행동추가");
	std::string Name = m_ActName->GetText();
	if (Name == "")
	{
		m_SaveMessege->SetText("! 행동 이름을 지어주세요");
	}else{	
		for (int i = 0; i < m_vecAct.size(); i++)
		{
			if (Name == m_vecAct[i]) 
			{
				m_SaveMessege->SetText("! 중복된이름");
				return;
			}				
		}
		m_AniList->AddItem(Name);
		m_vecAct.push_back(Name);
		m_SaveMessege->SetText("추가 완료!");
	}			
}

void CNMyAnimationWindow2::SaveAnimationCallback()
{
	OutputDebugStringA("저장버튼");

	if (!m_Animation) 
	{
		m_SaveMessege->SetText("저장할 애니메이션이 존재하지 않습니다.");
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
		m_SaveMessege->SetText("저장 완료!");
		fclose(File);
	}
}

void CNMyAnimationWindow2::CreateAnimationCallback()
{
	OutputDebugStringA("애니메이션 생성");
	std::string s = m_AnimationName->GetText();
	if (s == "")
	{
		m_SaveMessege->SetText("! 파일 이름을 지어주세요");
	}
	else if(!m_SpriteComponent)
	{
		m_SaveMessege->SetText("애니메이션에 사용할 컴포넌트를 불러와 주세요");
	}
	else if(m_Animation)
	{
		m_SaveMessege->SetText("이미 애니메이션을 생성하였습니다.");
		
	}
	else
	{
		//애니메이션 객체 생성
		m_SaveMessege->SetText("애니메이션 생성!");
		//(CSpriteComponent*)m_SelectComponent;
		m_Animation = m_SpriteComponent->SetAnimation<CAnimation2D>(s);
		m_AnimationName->ReadOnly(true);
	}
}

void CNMyAnimationWindow2::AddActAnimationCallback()
{

	OutputDebugStringA("애니메이션에 추가");
	//Act에 내용이 없으면 추가하고 있으면 수정
	//추가
	//행동(이름), 시퀀스네임, (이 이름으로 검색), 플탐, 플레이스케일, 루프, 리버스
	std::string ActName = m_SelectAct->GetText();
	std::string SeqName = m_SelectSqc->GetText();
	float PlayTime = m_PlayTime->GetFloat();
	float PlayScale = m_PlayScale->GetFloat();
	bool Loop = m_Loop->GetCheck();
	bool Reverse = m_Reverse->GetCheck();
	
	if (ActName == "" || SeqName == "")
	{
		m_SaveMessege->SetText("공란을 채워주세요");
		return;
	}
	//CAnimation2DData* AnimData = FindAnimation(ActName);
	m_Animation->AddAnimation(ActName, SeqName, PlayTime, PlayScale, Loop, Reverse);
	m_Animation->SetCurrentAnimation(ActName);
	
	m_SaveMessege->SetText("추가/변경 완료");
}

void CNMyAnimationWindow2::SelectActCallback(int SelectIndex, const std::string& Item)
{
	OutputDebugStringA("행동 선택");
	m_SelectAct->SetText(Item.c_str());
	
	
	if (m_Animation)
	{
		m_Animation->SetCurrentAnimation(Item);
		//이후 얘한테 등록된 시퀀스 정보도 가져온다.
		CAnimationSequence2D* sqc = m_Animation->GetCurrentAnimationSequence(Item);
		
		if(sqc)
			m_SelectSqc->SetText(sqc->GetName().c_str());
	}
}

void CNMyAnimationWindow2::SelectSqcCallback(int SelectIndex, const std::string& Item)
{
	OutputDebugStringA("시퀀스 선택");
	m_SelectSqc->SetText(Item.c_str());
}
