#include "ClassWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"

CClassWindow::CClassWindow()
{
}

CClassWindow::~CClassWindow()
{
}

bool CClassWindow::Init()
{
    m_ObjectList = CreateWidget<CEditorListBox>("ObjectListBox");
    
    m_ObjectList->SetHideName("ObjectListBox");

    m_ObjectList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ObjectClickCallback);
    
    m_ComponentList = CreateWidget<CEditorListBox>("ComponentListBox");

    m_ComponentList->SetHideName("ComponentListBox");

    m_ComponentList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ComponentClickCallback);

    return true;
}

void CClassWindow::Update(float DeltaTime)
{
    CEditorWindow::Update(DeltaTime);
}

void CClassWindow::ObjectClickCallback(int Index, const std::string& Item)
{
}

void CClassWindow::ComponentClickCallback(int Index, const std::string& Item)
{
}
