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

	OutputDebugStringA(Text);

	// 해당 게임오브젝트가 가지고 있는 모든 컴포넌트의 이름을 얻어온다.
	CGameObject* Obj = Node->GetCustomData();

	if (Obj)
	{
		std::vector<HierarchyName> vecName;

		Obj->GetAllComponentHierarchyName(vecName);

		CComponentWindow* ComponentWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");
		std::string Name = Obj->GetName() + "(" + Obj->GetObjectTypeName() + ")";
		ComponentWindow->AddItem(nullptr, Name);
		if (!vecName.empty())
		{
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
