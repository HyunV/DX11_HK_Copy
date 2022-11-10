#include "DetailWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorComboBox.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Engine.h"
#include "PathManager.h"

#include "Component/ColliderBox2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderPixel.h"

#include "NMyAnimationWindow2.h"
#include "Editor/EditorGUIManager.h"

#include "DetailWindow/CameraWidgetList.h"
#include "DetailWindow/TargetArmWidgetList.h"
#include "DetailWindow/SpriteComponentWidgetList.h"
#include "DetailWindow/SceneComponentWidgetList.h"
#include "DetailWindow/PrimitiveWidgetList.h"
#include "DetailWindow/ColliderWidgetList.h"
#include "DetailWindow/ColliderBox2DWidgetList.h"
#include "DetailWindow/ColliderOBB2DWidgetList.h"
#include "DetailWindow/ColliderPixelWidgetList.h"
#include "DetailWindow/ColliderSphereWidgetList.h"

CDetailWindow::CDetailWindow()
{
}

CDetailWindow::~CDetailWindow()
{
	{
		ClearWidget();

		size_t	Size = m_vecComponentWidgetList.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecComponentWidgetList[i]);
		}
	}
}

CComponentWidgetList* CDetailWindow::GetComponentWidgetList(const std::string& Name)
{
	size_t	Size = m_vecComponentWidgetList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecComponentWidgetList[i]->GetName() == Name)
			return m_vecComponentWidgetList[i];
	}

	return nullptr;
}

void CDetailWindow::SetSelectComponent(CSceneComponent* Component)
{
	//if(m_SelectComponent && Component)
	//{
	//	if (m_SelectComponent != Component)
	//	{
	//		ClearWidget();

	//		// 타입에 맞는 GUI 추가
	//		ChangeWidget(Component);
	//	}
	//}
	//m_SelectComponent = Component;

	if (Component)
	{
		ClearWidget();
		ChangeWidget(Component);
		m_SelectComponent = Component;
	}
}

bool CDetailWindow::Init()
{
	for (int i = 0; i < (int)ESceneComponentType::Max; ++i)
	{
		CreateEditorWidgetList((ESceneComponentType)i);
	}

	// 위젯 한번 지워주기
	ClearWidget();

	return true;
}

void CDetailWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_SelectComponent)
	{
		if (!m_SelectComponent->GetActive())
		{
			m_SelectComponent = nullptr;
			ClearWidget();
		}
	}
}

//void CDetailWindow::CreateCollider2DComponentWidget()
//{
//	//콜라이더
//
//	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("ColliderComponent");
//	
//	Category->SetSize(400.f, 300.f);
//
//	Category->AddItem(nullptr, "Collider");
//
//	CEditorText* Text = Category->CreateWidget<CEditorText>("Collider", "ColliderName");
//	Text->SetColor(0, 255, 0, 255);
//	Text->SetText("");
//
//	CEditorInput* InputX = Category->CreateWidget<CEditorInput>("Collider", "InputX");
//	InputX->SetInputType(EImGuiInputType::Float);
//
//	Category->CreateWidget<CEditorSameLine>("Collider", "Line");
//
//	CEditorInput* InputY = Category->CreateWidget<CEditorInput>("Collider", "InputY");
//	InputY->SetInputType(EImGuiInputType::Float);
//
//	CEditorInput* InputR = Category->CreateWidget<CEditorInput>("Collider", "InputRadian");
//	InputR->SetInputType(EImGuiInputType::Float);
//
//	CEditorButton* ConfirmButton = Category->CreateWidget<CEditorButton>("Collider", "Confirm");
//
//	ConfirmButton->SetClickCallback<CDetailWindow>(this, &CDetailWindow::ColliderSettingClick);
//	ConfirmButton->SetSize(300, 30);
//	m_vecColliderComponent.push_back(Category);
//}


void CDetailWindow::ChangeWidget(CSceneComponent* Component)
{
	std::string s = Component->GetComponentTypeName();
	//=======씬 컴포넌트일때==========
	if (Component->GetComponentTypeName() == "SceneComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Scene]);
	}
	//=======스프라이트 컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "SpriteComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Sprite]);

		((CSpriteComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Sprite])->SetSpriteContent((CSpriteComponent*)Component);

	}
	//=======카메라 컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "CameraComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Camera]);

	}
	//=======타겟암 컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "TargetArmComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::TargetArm]);

	}
	//=======콜라이더(Box, OBB, 원, 픽셀)  컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "ColliderBox2D" ||
		Component->GetComponentTypeName() == "ColliderOBB2D" ||
		Component->GetComponentTypeName() == "ColliderSphere2D" ||
		Component->GetComponentTypeName() == "ColliderPixel")
	{
		OutputDebugStringA("콜라이더");
		//AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::OBB2D]);
		//((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::OBB2D])->SetColliderContent((CCollider2D*)Component);
	//	size_t	Size = m_vecColliderComponent.size();

	//	for (size_t i = 0; i < Size; ++i)
	//	{
	//		AddWidget(m_vecColliderComponent[i]);
	//	}

	//	std::string Name = Component->GetComponentTypeName();
	//	CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecColliderComponent[0];

	//	CEditorInput* InputX = Category->FindWidget<CEditorInput>("InputX");
	//	CEditorInput* InputY = Category->FindWidget<CEditorInput>("InputY");
	//	CEditorInput* InputR = Category->FindWidget<CEditorInput>("InputRadian");
	//	CEditorText* Text = Category->FindWidget<CEditorText>("ColliderName");

	//	if (Name == "ColliderBox2D")
	//	{
	//		Text->SetText("ColliderBox2D");
	//		Vector2 v = ((CColliderBox2D*)Component)->GetBoxSize();
	//		InputX->SetFloat(v.x);
	//		InputY->SetFloat(v.y);

	//		InputR->SetFloat(0.f);
	//		InputR->ReadOnly(true);

	//	}
	//	else if (Name == "ColliderOBB2D")
	//	{
	//		Text->SetText("ColliderOBB2D");
	//		Vector2 v = ((CColliderOBB2D*)Component)->GetBoxHalfSize();
	//		InputX->SetFloat(v.x * 2.f);
	//		InputY->SetFloat(v.x * 2.f);

	//		InputR->SetFloat(0.f);
	//		InputR->ReadOnly(true);
	//	}
	//	else if (Name == "ColliderSphere2D")
	//	{
	//		Text->SetText("ColliderSphere2D");
	//		float  Radian = ((CColliderSphere2D*)Component)->GetInfo().Radius;			
	//		InputR->SetFloat(Radian);

	//		InputX->SetFloat(0.f);
	//		InputX->ReadOnly(true);
	//		InputY->SetFloat(0.f);
	//		InputY->ReadOnly(true);
	//	}
	//	else if (Name == "ColliderPixel")
	//	{
	//		Text->SetText("ColliderPixel");
	//	}
	//	else 
	//		return;
	}
}

void CDetailWindow::CreateEditorWidgetList(ESceneComponentType Type)
{
	CComponentWidgetList* WidgetList = nullptr;

	switch (Type)
	{
	case ESceneComponentType::Scene:
		WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("SceneComponent");
		break;
	case ESceneComponentType::Primitive:
		WidgetList = CreateWidgetEmpty<CPrimitiveWidgetList>("PrimitiveComponent");
		break;
	case ESceneComponentType::Sprite:
		WidgetList = CreateWidgetEmpty<CSpriteComponentWidgetList>("SpriteComponent");
		break;
	case ESceneComponentType::Camera:
		WidgetList = CreateWidgetEmpty<CCameraWidgetList>("CameraComponent");
		break;
	case ESceneComponentType::TargetArm:
		WidgetList = CreateWidgetEmpty<CTargetArmWidgetList>("TargetArmComponent");
		break;
	case ESceneComponentType::Collider:
		//WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("Notuse");
		break;
	case ESceneComponentType::Collider2D:
		//WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("Notuse2");
		break;
	case ESceneComponentType::Box2D:
		//WidgetList = CreateWidgetEmpty<CColliderBox2DWidgetList>("ColliderBox2DComponent");
		break;
	case ESceneComponentType::OBB2D:
		//WidgetList = CreateWidgetEmpty<CColliderOBB2DWidgetList>("ColliderOBB2DComponent");
		break;
	case ESceneComponentType::Sphere2D:
		//WidgetList = CreateWidgetEmpty<CColliderSphereWidgetList>("ColliderSphere2DComponent");
		break;
	case ESceneComponentType::Pixel:
		//WidgetList = CreateWidgetEmpty<CColliderPixelWidgetList>("ColliderPixelComponent");
		break;
	case ESceneComponentType::Collider3D:
		//WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("SceneComponent");
		break;
	}

	if (!WidgetList)
		return;

	WidgetList->m_DetailWindow = this;

	m_vecComponentWidgetList.push_back(WidgetList);

}

//void CDetailWindow::ColliderSettingClick()
//{
//	CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecColliderComponent[0];
//
//	CEditorText* Text = Category->FindWidget<CEditorText>("ColliderName");
//
//	CEditorInput* InputX = Category->FindWidget<CEditorInput>("InputX");
//	CEditorInput* InputY = Category->FindWidget<CEditorInput>("InputY");
//	CEditorInput* InputR = Category->FindWidget<CEditorInput>("InputRadian");
//
//	std::string s = Text->GetTextUTF8();
//
//	CSceneComponent* component = m_SelectComponent;
//
//	if (s == "ColliderBox2D")
//	{
//		Vector2 v(InputX->GetFloat(), InputY->GetFloat());
//		((CColliderBox2D*)component)->SetBoxSize(v);
//	}
//	else if (s == "ColliderOBB2D")
//	{
//		Vector2 v(InputX->GetFloat(), InputY->GetFloat());
//		((CColliderOBB2D*)component)->SetBoxHalfSize(v.x / 2.f, v.y / 2.f);
//	}
//	else if (s == "ColliderSphere2D")
//	{
//		float radian = InputR->GetFloat();
//		((CColliderSphere2D*)component)->SetRadius(radian);
//	}
//	else if (s == "ColliderPixel")
//	{
//
//	}
//	else
//		return;
//
//
//}

//void CDetailWindow::AnimationButtonClick()
//{
//	//애니메이션 윈도우에 해당 컴포넌트 추가
//
//	CNMyAnimationWindow2* AnimationWindow = CEditorGUIManager::GetInst()
//		->FindEditorWindow<CNMyAnimationWindow2>("NMyAnimationWindow2");
//		
//	AnimationWindow->SetSelectComponent(m_SelectComponent);
//
//	CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("NMyAnimationWindow2");
//	if (Window)
//		Window->Open();
//}
