#include "ComponentWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Component/Component.h"
#include "TransformWindow.h"
#include "Editor/EditorGUIManager.h"
#include "Component/SceneComponent.h"
#include "DetailWindow.h"

//#include "MyImageWindow.h"
//#include "NMyAnimationWindow2.h"


CComponentWindow::CComponentWindow()
{
}

CComponentWindow::~CComponentWindow()
{
}

//어떤형태의 컴포넌트인지 동반되어야 한다.(CComponent* Component)
bool CComponentWindow::AddItem(CComponent* Component, const std::string& Name, const std::string& ParentName)
{
	return m_Tree->AddItem(Component, Name, ParentName);
}

void CComponentWindow::Clear()
{
	m_Tree->Clear();
}

void CComponentWindow::ClearSelect()
{
	m_SelectComponent = nullptr;
}

bool CComponentWindow::Init()
{
	m_Text = CreateWidget<CEditorText>("Text");

	m_Text->SetColor(0, 255, 0, 255);
	m_Text->SetText("* 선택한 컴포넌트");

	m_Tree = CreateWidget<CEditorTree<CComponent*>>("ComponentTree");

	m_Tree->SetHideName("ComponentTree");

	m_Tree->SetSelectCallback<CComponentWindow>(this, &CComponentWindow::TreeCallback);

	m_Tree->SetSize(400.f, 300.f);

	return true;
}

void CComponentWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_SelectComponent)
	{
		if (!m_SelectComponent->GetActive())
			m_SelectComponent = nullptr;
	}
}

void CComponentWindow::TreeCallback(CEditorTreeItem<class CComponent*>* Node, const std::string& Item)
{
	char Text[256] = {};
	sprintf_s(Text, "%s\n", Item.c_str());
	OutputDebugStringA(Text);
	m_Text->SetText(Text);

	m_SelectComponent = Node->GetCustomData();

	CTransformWindow* TransformWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CTransformWindow>("TransformWindow");
	CDetailWindow* DetailWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("DetailWindow");

	DetailWindow->SetSelectComponent((CSceneComponent*)m_SelectComponent.Get());

	//##과제 내 윈도우에 추가
	//CMyImageWindow* MyImageWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CMyImageWindow>("MyImageWindow");

	//MyImageWindow->SetSelectComponent(Item, (CSceneComponent*)m_SelectComponent.Get());

	//애니메이션 윈도우에도 추가
	/*CNMyAnimationWindow2* AnimationWindow = CEditorGUIManager::GetInst()->
		FindEditorWindow<CNMyAnimationWindow2>("NMyAnimationWindow2");
	AnimationWindow->SetSelectComponent((CSceneComponent*)m_SelectComponent.Get());*/

	

	if (m_SelectComponent)
	{

		CSceneComponent* Component = (CSceneComponent*)m_SelectComponent.Get();

		TransformWindow->SetSelectComponent(Component);

		//if (Component->GetParent())
		//{
			//부모에 세팅된 값을 띄워줌
			TransformWindow->SetRelativePos(Component->GetRelativePos());
			TransformWindow->SetRelativeScale(Component->GetRelativeScale());
			TransformWindow->SetRelativeRotation(Component->GetRelativeRot());
		//}

		//else
		//{
			//자식의 세팅된 값?
			TransformWindow->SetPos(Component->GetWorldPos());
			TransformWindow->SetScale(Component->GetWorldScale());
			TransformWindow->SetRotation(Component->GetWorldRot());


		//}

			//피봇
			TransformWindow->SetPivot(Component->GetPivot());
	}
}
