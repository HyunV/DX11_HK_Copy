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


CComponentWindow::CComponentWindow()
{
}

CComponentWindow::~CComponentWindow()
{
}

void CComponentWindow::AddItem(CComponent* Component, const std::string& Name, const std::string& ParentName)
{
	m_Tree->AddItem(Component, Name, ParentName);
}

void CComponentWindow::Clear()
{
	m_Tree->Clear();
}

bool CComponentWindow::Init()
{
	m_Tree = CreateWidget<CEditorTree<CComponent*>>("ComponentTree");

	m_Tree->SetHideName("ComponentTree");

	m_Tree->SetSelectCallback<CComponentWindow>(this, &CComponentWindow::TreeCallback);

	m_Tree->SetSize(400.f, 300.f);

	return true;
}

void CComponentWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CComponentWindow::TreeCallback(CEditorTreeItem<class CComponent*>* Node, const std::string& Item)
{
	char Text[256] = {};
	sprintf_s(Text, "%s\n", Item.c_str());
	OutputDebugStringA(Text);
}
