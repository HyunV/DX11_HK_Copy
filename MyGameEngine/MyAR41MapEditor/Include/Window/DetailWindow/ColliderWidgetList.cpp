#include "ColliderWidgetList.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorText.h"
#include "Component/Collider2D.h"

CColliderWidgetList::CColliderWidgetList()
{
}

CColliderWidgetList::~CColliderWidgetList()
{
}

void CColliderWidgetList::SetColliderContent(CCollider2D* Collider2D)
{
	m_Collider = Collider2D;
	m_Collider2DType = m_Collider->GetCollider2DType();


}

bool CColliderWidgetList::Init()
{
	//콜라이더

	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("ColliderComponent");
	
	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "Collider");

	CEditorText* Text = Category->CreateWidget<CEditorText>("Collider", "ColliderName");
	Text->SetColor(0, 255, 0, 255);
	Text->SetText("");

	CEditorInput* InputX = Category->CreateWidget<CEditorInput>("Collider", "InputX");
	InputX->SetInputType(EImGuiInputType::Float);

	Category->CreateWidget<CEditorSameLine>("Collider", "Line");

	CEditorInput* InputY = Category->CreateWidget<CEditorInput>("Collider", "InputY");
	InputY->SetInputType(EImGuiInputType::Float);

	CEditorInput* InputR = Category->CreateWidget<CEditorInput>("Collider", "InputRadian");
	InputR->SetInputType(EImGuiInputType::Float);

	CEditorButton* ConfirmButton = Category->CreateWidget<CEditorButton>("Collider", "Confirm");

	ConfirmButton->SetClickCallback<CColliderWidgetList>(this, &CColliderWidgetList::SetConfirmButtonCallback);
	ConfirmButton->SetSize(300, 30);

	return true;
}

void CColliderWidgetList::SetConfirmButtonCallback()
{

}
