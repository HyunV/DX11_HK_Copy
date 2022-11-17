#include "ColliderBox2DWidgetList.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorComboBox.h"

#include "Component/ColliderBox2D.h"

#include "CollisionManager.h"

CColliderBox2DWidgetList::CColliderBox2DWidgetList()
{
}

CColliderBox2DWidgetList::~CColliderBox2DWidgetList()
{

}

void CColliderBox2DWidgetList::SetColliderBox2D(CColliderBox2D* ColliderComponent)
{
	m_Collider = ColliderComponent;

	std::string ChannelName = m_Collider->GetCollisionProfile()->Name;
	m_Name->SetText("Box2D Profile: " + ChannelName);

	//std::vector<CollisionChannel*> v = CCollisionManager::GetInst()->m_vecChannel;
	//for (int i = 0; i < v.size(); i++)
	//{
	//	if (v[i]->Name == ChannelName)
	//		m_Combo->SetSelect(i);
	//}
	//CEditorInput* InputR = Category->FindWidget<CEditorInput>("InputRadian");
	
	m_InputX->SetFloat(m_Collider->GetBoxSize().x);
	m_InputY->SetFloat(m_Collider->GetBoxSize().y);
	//CSceneComponent* component = m_SelectComponent;

	//if (s == "ColliderBox2D")
	//{
	//	Vector2 v(InputX->GetFloat(), InputY->GetFloat());
	//	((CColliderBox2D*)component)->SetBoxSize(v);
	//}
	//else if (s == "ColliderOBB2D")
	//{
	//	Vector2 v(InputX->GetFloat(), InputY->GetFloat());
	//	((CColliderOBB2D*)component)->SetBoxHalfSize(v.x / 2.f, v.y / 2.f);
	//}
	//else if (s == "ColliderSphere2D")
	//{
	//	float radian = InputR->GetFloat();
	//	((CColliderSphere2D*)component)->SetRadius(radian);
	//}
	//else if (s == "ColliderPixel")
	//{

	//}
	//else
	//	return;

	//return true;
	

}

bool CColliderBox2DWidgetList::Init()
{
	//	//콜라이더
	m_Name = CreateWidget<CEditorText>("Name");
	m_Name->SetText("Collider Box2D");

	m_Combo = CreateWidget<CEditorComboBox>("Profile");
	m_Combo->SetHideName("Profile");
	m_Combo->SetPrevViewName("Profiles");
	m_Combo->SetSelectPrevViewName(true);
	m_Combo->SetSizeX(150.f);
	//m_Combo->SetSelectCallback(this, &CColliderBox2DWidgetList::ComboBoxCallback);
	
	std::vector<CollisionChannel*> v = CCollisionManager::GetInst()->m_vecChannel;
	for (int i = 0; i < v.size(); i++)
		m_Combo->AddItem(v[i]->Name);

	m_InputX = CreateWidget<CEditorInput>("InputX");
	m_InputX->SetInputType(EImGuiInputType::Float);

	m_InputY = CreateWidget<CEditorInput>("InputY");
	m_InputY->SetInputType(EImGuiInputType::Float);

	CEditorButton* ConfirmButton = CreateWidget<CEditorButton>("Confirm");
	ConfirmButton->SetClickCallback<CColliderBox2DWidgetList>(this, &CColliderBox2DWidgetList::ColliderSettingClick);
	ConfirmButton->SetSize(100, 30);

	return true;
}

void CColliderBox2DWidgetList::ColliderSettingClick()
{
	m_Collider->SetBoxSize(m_InputX->GetFloat(), m_InputY->GetFloat());

	std::string Profile = m_Combo->GetSelectItem();
	m_Collider->SetCollisionProfile(Profile);
	m_Name->SetText("Box2D Profile: " + Profile);

}


//void CColliderBox2DWidgetList::ComboBoxCallback(int SelectIndex, const std::string& Item)
//{
//	OutputDebugStringA(Item.c_str());
//}
