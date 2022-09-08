#include "ObjectWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"

CObjectWindow::CObjectWindow()
{
}

CObjectWindow::~CObjectWindow()
{
}

void CObjectWindow::AddItem(const std::string& Name, const std::string& ParentName)
{
	m_Tree->AddItem(Name, ParentName);
}

bool CObjectWindow::Init()
{
	m_Tree = CreateWidget<CEditorTree>("ObjectTree");

	m_Tree->SetHideName("ObjectTree");

	m_Tree->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::TreeCallback);

	m_Tree->SetSize(400.f, 300.f);

	m_Tree->AddItem("Root");

	return true;
}

void CObjectWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);
}

void CObjectWindow::TreeCallback(const std::string& Item)
{
	char	Text[256] = {};

	sprintf_s(Text, "%s\n", Item.c_str());

	OutputDebugStringA(Text);
}
