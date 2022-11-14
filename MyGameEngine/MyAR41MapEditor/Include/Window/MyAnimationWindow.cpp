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

#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Engine.h"
#include "MySequenceWindow.h"
#include "Editor/EditorGUIManager.h"

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
	m_LoadAnimCombo->AddItem("New Animation");
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

	m_SelectedSqcText = Group->CreateWidget<CEditorText>("SelectedSequence");
	m_SelectedSqcText->SetText("");
	m_SelectedSqcText->SetColor(0, 255, 0, 255);
	//m_SelectedSqcText->SetSize(250.f, 30.f);

	CEditorButton* LoadSqcBtn = Group->CreateWidget<CEditorButton>("시퀀스 추가", 100.f, 30.f);
	LoadSqcBtn->SetClickCallback<CMyAnimationWindow>
		(this, &CMyAnimationWindow::LoadSqcBtnCallback);

	CEditorButton* DeleteSqcBtn = Group->CreateWidget<CEditorButton>("시퀀스 제거", 100.f, 30.f);
	DeleteSqcBtn->SetClickCallback<CMyAnimationWindow>
		(this, &CMyAnimationWindow::DeleteSqcBtnCallback);

	m_PlayTimeInput = CreateWidget<CEditorInput>("PlayTime");
	m_PlayTimeInput->SetInputType(EImGuiInputType::Float);
	m_PlayTimeInput->SetFloat(1.f);

	m_PlayScaleInput = CreateWidget<CEditorInput>("PlayScale");
	m_PlayScaleInput->SetInputType(EImGuiInputType::Float);
	m_PlayScaleInput->SetFloat(1.f);

	m_FrameTime = CreateWidget<CEditorInput>("FrameTime");
	m_FrameTime->SetInputType(EImGuiInputType::Float);

	m_Loop = CreateWidget<CEditorCheckBox>("                  Loop");
	m_Reverse = CreateWidget<CEditorCheckBox>("                  Reverse");

	Label = CreateWidget<CEditorLabel>("Label");
	Label->SetHideName("Label");
	Label->SetColor(0, 0, 0, 0);

	m_SaveAnimationInput = CreateWidget<CEditorInput>("SaveAnimation");
	m_SaveAnimationInput->SetHideName("SaveAnimation");
	m_SaveAnimationInput->SetText("");
	m_SaveAnimationInput->SetSizeX(150.f);
	m_SaveAnimationInput->SetHintText("애니메이션 파일명");

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* SaveAnimBtn = CreateWidget<CEditorButton>("변경 및 저장");
	SaveAnimBtn->SetClickCallback<CMyAnimationWindow>(this, &CMyAnimationWindow::SaveBtnCallback);

	//====================세팅
	m_mapAnimation2D = CResourceManager::GetInst()->GetMapAnimation2D();
	
	m_SeqWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CMySequenceWindow>("MySequenceWindow");

	SetComboBox();

	return true;
}

void CMyAnimationWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
	
	if (m_EventList->GetSelectIndex() > -1)
	{
		int index = m_EventList->GetSelectIndex();
		std::string Item = m_EventList->GetItem(index);
		CAnimation2DData* Data = m_Animation->FindAnimation(Item);

		if (Data)
		{
			//OutputDebugStringA(Item.c_str());
			Data->m_PlayTime = m_PlayTimeInput->GetFloat();
			Data->m_FrameTime = m_FrameTime->GetFloat();
			Data->m_PlayScale = m_PlayScaleInput->GetFloat();
			Data->m_Loop = m_Loop->GetCheck();
			Data->m_Reverse = m_Reverse->GetCheck();
		}
	}
	
}

void CMyAnimationWindow::ClearSetting()
{
	m_Messege->SetText("");
	//m_LoadAnimCombo->ResetSelectIndex();
	//m_LoadAnimCombo->SetSelectPrevViewName(true);
	//m_EventList->ClearSelectIndex();
	m_PlayTimeInput->SetFloat(1.f);
	m_PlayScaleInput->SetFloat(1.f);
	m_FrameTime->SetFloat(0.f);
	m_Loop->SetCheck(false);
	m_Reverse->SetCheck(false);

	//m_SaveAnimationInput->SetText("");

}

void CMyAnimationWindow::SetComboBox()
{
	//맵 애니메이션 불러와주기

	//CResourceManager::GetInst()->CreateAnimation2D("test");

	auto iter = m_mapAnimation2D->begin();
	auto iterEnd = m_mapAnimation2D->end();

	for (; iter != iterEnd; iter++)
	{
		m_LoadAnimCombo->AddItem(iter->first);
	}


}

void CMyAnimationWindow::ClearList()
{

}

void CMyAnimationWindow::ComboBoxCallback(int SelectIndex, const std::string& Item)
{
	//OutputDebugStringA(Item.c_str());
	//m_Messege->SetText(Item);

	ClearSetting();

	// if 새로 만들기
	if (!m_Animation && Item == "New Animation")
	{
		m_Animation = m_Animation->FindCDO("Animation2D");
		m_Animation->SetName("Animation2D");
	}
		
	else //기존에 있는 애니메이션들
	{
		m_Animation = CResourceManager::GetInst()->FindAnimation2D(Item);
		m_SaveAnimationInput->SetText(Item.c_str());

	}
		
	//리스트 클리어
	m_EventList->Clear();

	//리스트 세팅
	if (!(m_Animation->GetName() == "Animation2D"))
	{
		//m_Animation2DData = m_Animation->GetAnimationList();
		auto iter = m_Animation->m_mapAnimation.begin();
		auto iterEnd = m_Animation->m_mapAnimation.end();

		for(; iter != iterEnd; ++iter)
		{
			m_EventList->AddItem((*iter).first);
		}
	}
		
	
}

void CMyAnimationWindow::ListCallback(int SelectIndex, const std::string& Item)
{
	
	//OutputDebugStringA(Item.c_str());
	
	//시퀀스 재생하기,
	CAnimationSequence2D* seq = CResourceManager::GetInst()->FindAnimationSequence2D(Item);
	if (seq)
	{
		m_SelectedSqcText->SetText(Item);
		m_SeqWindow->LoadSequence(seq);
		m_SeqWindow->PlayButton();
	}

	//에니메이션 데이터 값 세팅하기
	ClearSetting();
	CAnimation2DData* Data = m_Animation->FindAnimation(Item);

	m_PlayTimeInput->SetFloat(Data->m_PlayTime);
	m_FrameTime->SetFloat(Data->m_FrameTime);
	m_PlayScaleInput->SetFloat(Data->m_PlayScale);
	m_Loop->SetCheck(Data->m_Loop);
	m_Reverse->SetCheck(Data->m_Reverse);
	

}

void CMyAnimationWindow::LoadSqcBtnCallback()
{
	if (m_LoadAnimCombo->GetSelectIndex() == -1)
	{
		m_Messege->SetText("애니메이션을 선택해주세요");
		return;
	}

	OPENFILENAME    ofn = {};

	TCHAR	FullPath[2048] = {}; //파일 풀경로

	TCHAR	Filter[] = TEXT("모든 파일\0*.*");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = 2048;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(SEQUENCE2D_PATH)->Path;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	//파일 열기
	if (0 != GetOpenFileName(&ofn))
	{
		int i = (int)wcslen(ofn.lpstrFile) + 1;

		//파일 하나일때
		if (ofn.lpstrFile[i] == NULL)
		{
			TCHAR FileName[256] = {};
			TCHAR Ext[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, FileName, 256, Ext, 256);

			std::string s = TCHARToString(FileName);
			if (!m_EventList->CheckItem(s))
			{
				m_EventList->AddItem(s);
				m_Animation->AddAnimation(s, s);
			}
				
		}
		else
		{
			for (i; NULL != ofn.lpstrFile[i]; i += (int)(wcslen(ofn.lpstrFile + i) + 1))
			{
				TCHAR FileName[512] = {};
				memset(FileName, 0, sizeof(TCHAR) * 512);
				wcscpy_s(FileName, ofn.lpstrFile + i);

				//imgui.ini 예외
				std::string s = TCHARToString(FileName);
				if (s == "imgui.ini")
					continue;

				TCHAR FileName2[256] = {};
				_wsplitpath_s(FileName, 0, 0, 0, 0, FileName2, 256, 0, 0);

				//=============
				std::string s2 = TCHARToString(FileName2);
				if (!m_EventList->CheckItem(s2))
				{
					m_EventList->AddItem(s2);
					m_Animation->AddAnimation(s2, s2);
				}
					
			}
		}
	}
}

void CMyAnimationWindow::DeleteSqcBtnCallback()
{
	int index = m_EventList->GetSelectIndex();
	std::string Item = m_EventList->GetSelectItem();
	if (index == -1)
	{
		m_Messege->SetText("* 아이템이 선택되지 않았습니다.");
		return;
	}
	m_EventList->DeleteItem(index);
	m_SeqWindow->ClearSetting();
	m_SelectedSqcText->SetText("");
	
	//애니메이션 데이터 리스트도 삭제
	m_Animation->DeleteAnimation2DData(Item);
}

void CMyAnimationWindow::SaveBtnCallback()
{
	std::string s = m_SaveAnimationInput->GetTextUTF8();
	if (s == "")
	{
		m_Messege->SetText("* 애니메이션 파일 이름을 지어주세요");
		return;
	}

	FILE* file;
	char c[256] = {};
	strcat_s(c, CPathManager::GetInst()->FindPath(ROOT_PATH)->PathMultibyte);
	strcat_s(c, "Animation2D\\");
	strcat_s(c, m_SaveAnimationInput->GetText());

	fopen_s(&file, c, "wb");

	m_Animation->Save(file);

	if (file)
	{
		m_Messege->SetText("저장 완료!");
	}

	fclose(file);
}

const std::string CMyAnimationWindow::TCHARToString(const TCHAR* ptsz)
{
	size_t tcnt = wcslen((wchar_t*)ptsz);

	char psz[256];

	//wc sqc to multibyte sqc
	wcstombs_s(&tcnt, psz, sizeof(psz), ptsz, 256);

	std::string s = psz;

	return s;
}
