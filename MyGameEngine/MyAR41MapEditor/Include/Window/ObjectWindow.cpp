#include "ObjectWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorButton.h"
#include "ComponentWindow.h"
#include "TransformWindow.h"
#include "Editor/EditorGUIManager.h"

#include "Editor/EditorPopup.h"

CObjectWindow::CObjectWindow()
{
}

CObjectWindow::~CObjectWindow()
{
}

bool CObjectWindow::AddItem(CGameObject* Object, const std::string& Name, const std::string& ParentName)
{
	return m_Tree->AddItem(Object, Name, ParentName);
}

bool CObjectWindow::Init()
{
	CEditorButton* m_DeleteButton = CreateWidget<CEditorButton>("Delete Object");
	m_DeleteButton->SetSizeX(150.f);
	m_DeleteButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::DeleteButtonCallback);

	m_SelectObjectInput = CreateWidget<CEditorInput>("Selected Object");
	m_SelectObjectInput->ReadOnly(true);
	m_SelectObjectInput->SetHideName("Selected Object");
	m_SelectObjectInput->SetSizeX(150.f);

	m_Tree = CreateWidget<CEditorTree<CGameObject*>>("ObjectTree");

	m_Tree->SetHideName("ObjectTree");

	m_Tree->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::TreeCallback);

	m_Tree->SetSize(400.f, 300.f);

	m_Tree->AddItem(nullptr, "Root");

	return true;
}

void CObjectWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_SelectObject)
	{
		if (!m_SelectObject->GetActive())
			m_SelectObject = nullptr;
	}
}

void CObjectWindow::TreeCallback(CEditorTreeItem<CGameObject*>* Node, const std::string& Item)
{
	char	Text[256] = {};

	sprintf_s(Text, "%s\n", Item.c_str());

	OutputDebugStringA(Text); //콘솔에 누른 오브젝트 이름 출력

	m_SelectObjectInput->SetText(Text);
	
	//m_Tree->CreateWidget<CEditorPopup>(m_Tree->GetName(), "Popup");
	
	//CEditorPopup* popup = CreateWidget<CEditorPopup>("Popup");
	

	
	//ImGui::OpenPopup("ObjectWindow");

	//if (ImGui::BeginPopup("ObjectWindow"))
	//{
	//	ImGui::Text("Aquarium");
	//	ImGui::Selectable("Tst");
	//	ImGui::EndPopup();
	//}

	//컴포넌트 윈도우에 선택한 것들을 비운다.
	CComponentWindow* ComponentWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");

	ComponentWindow->ClearSelect();
	ComponentWindow->Clear();

	// 해당 게임오브젝트가 가지고 있는 모든 컴포넌트의 이름을 얻어온다. 
	// 그러기 위해선 이 게임오브젝트의 계층을 알아야 한다.(Engineinfo에 HierarchyName 구조체를 갖다 쓴다.)
	
	CGameObject* Obj = Node->GetCustomData();//트리 노드 자체가 게임오브젝트 들고있으니 넣어줌

	m_SelectObject = Obj;

	if (Obj)
	{
		//트랜스폼 윈도우 불러오기
		CTransformWindow* TransformWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CTransformWindow>("TransformWindow");

		//씬 루트 컴포 얻어오기, 루트 존재시 해당 컴포의 위치정보 얻어오기
		CSceneComponent* Root = Obj->GetRootComponent();

		if (Root)
		{
			TransformWindow->SetSelectComponent(Root);
			TransformWindow->SetPos(Root->GetWorldPos());
			TransformWindow->SetScale(Root->GetWorldScale());
			TransformWindow->SetRotation(Root->GetWorldRot());
		}

		std::vector<HierarchyName> vecName;

		Obj->GetAllComponentHierarchyName(vecName); //해당 오브젝트의 모든 부모 정보, 이름 받아옴

		//목록에 [몬스터(몬스터)] 식으로 컴포넌트에 이름 추가
		std::string Name = Obj->GetName() + "(" + Obj->GetObjectTypeName() + ")";

		ComponentWindow->AddItem(nullptr, Name); 

		//대충 컴포넌트에 계층구조로 목록 추가해주는 식
		if (!vecName.empty()) 
		{
			//[0]은 루트라 parent 기준으로 잡아서 작성
			std::string ParentName = Name;

			Name = vecName[0].Name + "(" + vecName[0].ClassName + ")";

			ComponentWindow->AddItem(vecName[0].Component, Name, ParentName);

			size_t	Size = vecName.size();

			std::vector<HierarchyName> vecName1;

			for (size_t i = 1; i < Size; ++i)
			{
				ParentName = vecName[i].ParentName + "(" + vecName[i].ParentClassName + ")";

				Name = vecName[i].Name + "(" + vecName[i].ClassName + ")";

				if (!ComponentWindow->AddItem(vecName[i].Component, Name, ParentName))
					vecName1.push_back(vecName[i]);				
			}

			Size = vecName1.size();

			for (size_t i = 0; i < Size; ++i)
			{
				ParentName = vecName1[i].ParentName + "(" + vecName1[i].ParentClassName + ")";

				Name = vecName1[i].Name + "(" + vecName1[i].ClassName + ")";

				ComponentWindow->AddItem(vecName1[i].Component, Name, ParentName);
			}
		}
	}
}

void CObjectWindow::DeleteButtonCallback()
{	
	//루트는 지울 수 없다, //선택되어야한다.
	std::string s = m_SelectObjectInput->GetText();

	if (s == "Root\n" || s == "")
		return;

	//목록 먼저 지운다. 오브젝트랑 컴포넌트 목록 갱신
	m_SelectObjectInput->SetText("");

	std::string Name = m_SelectObject->GetName();
	m_Tree->DeleteItem(Name);

	//선택한 오브젝트를 삭제한다.
	m_SelectObject->Destroy();

	//지우고 나면 선택창을 비운다.
	
}
