#include "ObjectWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "ComponentWindow.h"
#include "Editor/EditorGUIManager.h"

CObjectWindow::CObjectWindow()
{
}

CObjectWindow::~CObjectWindow()
{
}

void CObjectWindow::AddItem(CGameObject* Object, const std::string& Name, const std::string& ParentName)
{
	m_Tree->AddItem(Object, Name, ParentName);
}

bool CObjectWindow::Init()
{
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
}

void CObjectWindow::TreeCallback(CEditorTreeItem<CGameObject*>* Node, const std::string& Item)
{
	char	Text[256] = {};

	sprintf_s(Text, "%s\n", Item.c_str());

	OutputDebugStringA(Text); //콘솔에 누른 오브젝트 이름 출력

	// 해당 게임오브젝트가 가지고 있는 모든 컴포넌트의 이름을 얻어온다. 
	// 그러기 위해선 이 게임오브젝트의 계층을 알아야 한다.(Engineinfo에 HierarchyName 구조체를 갖다 쓴다.)
	
	CGameObject* Obj = Node->GetCustomData();//트리 노드 자체가 게임오브젝트 들고있으니 넣어줌

	if (Obj)
	{
		std::vector<HierarchyName> vecName;

		Obj->GetAllComponentHierarchyName(vecName); //해당 오브젝트의 모든 부모 정보, 이름 받아옴

		//에디터 GUI매니저에 있는 컴포넌트 윈도우를 데려와서
		CComponentWindow* ComponentWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");

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

			for (size_t i = 1; i < Size; ++i)
			{
				ParentName = vecName[i].ParentName + "(" + vecName[i].ParentClassName + ")";

				Name = vecName[i].Name + "(" + vecName[i].ClassName + ")";

				ComponentWindow->AddItem(vecName[i].Component, Name, ParentName);
			}
		}
	}
}
