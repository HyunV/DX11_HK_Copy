#include "SceneWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "PathManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Editor/EditorGUIManager.h"
#include "ObjectWindow.h"

#include "../Scene/EditorDefaultScene.h"
#include "../Scene/EditorTestScene.h"

CSceneWindow::CSceneWindow()
{
}

CSceneWindow::~CSceneWindow()
{
}

bool CSceneWindow::Init()
{
	CEditorButton* Button = CreateWidget<CEditorButton>("Scene ����", 150.f, 30.f);

	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneChange);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	m_SceneSaveName = CreateWidget<CEditorInput>("SceneSaveName");

	m_SceneSaveName->SetHideName("SceneSaveName");
	m_SceneSaveName->SetSize(150.f, 30.f);


	Line = CreateWidget<CEditorSameLine>("Line");

	Button = CreateWidget<CEditorButton>("Scene ����", 150.f, 30.f);

	Button->SetColor(29, 47, 73, 255);
	Button->SetClickCallback<CSceneWindow>(this, &CSceneWindow::SceneSave);

	CEditorLabel* Label = CreateWidget<CEditorLabel>("Scene");

	Label->SetColor(255, 0, 0, 255);
	Label->SetAlign(0.5f, 0.5f);
	Label->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_SceneList = CreateWidget<CEditorListBox>("SceneListBox");

	m_SceneList->SetHideName("SceneListBox");

	m_SceneList->SetSize(150.f, 300.f);
	m_SceneList->SetPageItemCount(6);

	m_SceneList->SetSelectCallback<CSceneWindow>(this, &CSceneWindow::SceneClickCallback);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_SceneSelectName = CreateWidget<CEditorInput>("SceneName");

	m_SceneSelectName->SetHideName("SceneName");
	m_SceneSelectName->SetSize(150.f, 30.f);
	m_SceneSelectName->ReadOnly(true);


	CEditorLabel* Label2 = CreateWidget<CEditorLabel>("SceneInfo");

	Label2->SetColor(255, 0, 0, 255);
	Label2->SetAlign(0.5f, 0.5f);
	Label2->SetSizeY(30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* m_NewSceneButton = CreateWidget<CEditorButton>("New Scene");
	m_NewSceneButton->SetClickCallback<CSceneWindow>(this, &CSceneWindow::NewSceneButtonCallback);

	m_SceneInfoName = CreateWidget<CEditorInput>("SceneInfoName");
	m_SceneInfoName->SetHideName("SceneInfoName");
	m_SceneInfoName->SetHintText("Scene Info");
	m_SceneInfoName->ReadOnly(true);
	m_SceneInfoName->SetSizeX(300.f);
	

	m_SceneInfoList = CreateWidget<CEditorListBox>("SceneInfoListBox");

	m_SceneInfoList->SetHideName("SceneInfoListBox");

	m_SceneInfoList->SetSize(150.f, 300.f);
	m_SceneInfoList->SetPageItemCount(6);

	m_SceneInfoList->SetSelectCallback<CSceneWindow>(this, &CSceneWindow::SceneInfoClickCallback);

	//�� ��� ������
	LoadSceneDirectory();
	LoadSceneInfoDirectory();



	return true;
}

void CSceneWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CSceneWindow::SceneChange()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	if (Scene->GetName() == m_SelectSceneItem && !m_SelectSceneItem.empty())
		return;

	CSceneManager::GetInst()->CreateNextScene();
	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Scene/");
	strcat_s(FullPath, m_SelectSceneItem.c_str());
	strcat_s(FullPath, ".scn");

	NextScene->Load(FullPath);

	//�Ϸ�� GameObject ����� ObjectWindow�� �߰��Ѵ�.
	CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

	std::vector<HierarchyObjectName> vecName;

	NextScene->GetAllGameObjectHierarchyName(vecName);

	size_t Size = vecName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		ObjectWindow->AddItem(vecName[i].Obj, vecName[i].Name);
	}
}

void CSceneWindow::SceneSave()
{
	std::string Name = m_SceneSaveName->GetText();

	if (Name.empty())
		return;

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Scene/");
	strcat_s(FullPath, Name.c_str());
	strcat_s(FullPath, ".scn");

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	Scene->SetName(Name);

	Scene->Save(FullPath);

	if (!m_SceneList->CheckItem(Name))
		m_SceneList->AddItem(Name);
}

void CSceneWindow::SceneClickCallback(int Index, const std::string& Item)
{
	m_SelectSceneItem = Item;
	m_SceneSelectName->SetText(Item.c_str());
}

void CSceneWindow::SceneInfoClickCallback(int Index, const std::string& Item)
{
	//OutputDebugStringA(Item.c_str());
	m_SceneInfoName->SetText(Item.c_str());
}

void CSceneWindow::LoadSceneDirectory()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);
	strcat_s(Path, "Scene/");

	for (const auto& file : std::filesystem::directory_iterator(Path))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		m_SceneList->AddItem(Name);
	}
}

void CSceneWindow::LoadSceneInfoDirectory()
{
	//��Ŭ����� �� ���� �����ٰ�

	//������...Bin/ �̰� ���ְ� Include/Scene �߰�
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};
	strcpy_s(Path, Info->PathMultibyte);

	int length = (int)strlen(Path);

	//Bin ����, "\\"�� "\0" �� �����ؼ� ���̿��� -2 ���� Bin�� "n"���� ����
	//���ȳ��� ������ؼ� ���
	for (int i = length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (length - i - 1));
			break;
		}
	}

	strcat_s(Path, "Include/Scene/");


	//����Ʈ�� ����ֱ�
	for (const auto& file : std::filesystem::directory_iterator(Path))
	{
		char Name[64] = {};
		char FullPath[MAX_PATH] = {};
		char Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());
		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);
		
		if (strcmp(Ext, ".h") == 0)
			continue;

		m_SceneInfoList->AddItem(Name);
	}
}

void CSceneWindow::NewSceneButtonCallback()
{
	//����: �������� �����ϰ� �־�ߵ�
	std::string s = m_SceneInfoName->GetText();
	//if (s == "")
	//	return;

	//�� �� �����
	CSceneManager::GetInst()->CreateNextScene();

	CScene* NextScene = CSceneManager::GetInst()->GetNextScene();


	if (s == "EditorDefaultScene")
	{
		NextScene->CreateSceneInfo<CEditorDefaultScene>();
	}
	else if (s == "EditorTestScene")
	{
		NextScene->CreateSceneInfo<CEditorTestScene>();
	}

	//�׽�Ʈ Ȯ�ο�
	//CSceneInfo* TestInfo = NextScene->GetSceneInfo();

	m_SceneInfoName->SetText("");

	OutputDebugStringA("Hi");
}
