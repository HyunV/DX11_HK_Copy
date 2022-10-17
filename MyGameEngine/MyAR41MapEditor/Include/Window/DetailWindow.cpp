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

CDetailWindow::CDetailWindow()
{
}

CDetailWindow::~CDetailWindow()
{
	ClearWidget();

	{
		size_t	Size = m_vecSceneComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSceneComponent[i]);
		}

		m_vecSceneComponent.clear();
	}

	{
		size_t	Size = m_vecSpriteComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSpriteComponent[i]);
		}

		m_vecSpriteComponent.clear();
	}

	{
		size_t	Size = m_vecCameraComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecCameraComponent[i]);
		}

		m_vecCameraComponent.clear();
	}

	{
		size_t	Size = m_vecTargetArmComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecTargetArmComponent[i]);
		}

		m_vecTargetArmComponent.clear();
	}

	{
		size_t	Size = m_vecColliderComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecColliderComponent[i]);
		}

		m_vecColliderComponent.clear();
	}
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
	CreateSceneComponentWidget();
	CreateSpriteComponentWidget();
	CreateCameraComponentWidget();
	CreateTargetArmComponentWidget();
	CreateCollider2DComponentWidget();

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

void CDetailWindow::CreateSceneComponentWidget()
{
	//TODO 씬 컴포넌트
}

void CDetailWindow::CreateSpriteComponentWidget()
{
	//TODO 스프라이트 컴포넌트
	//머테리얼, 이미지 체인지, 애니메이션
	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("SpriteComponent");

	Category->SetHideName("SpriteComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "Sprite");

	Category->CreateWidget<CEditorImage>("Sprite", "SpriteImage");

	Category->CreateWidget<CEditorSameLine>("Sprite", "Line");

	CEditorButton* LoadButton = Category->CreateWidget<CEditorButton>("Sprite", "Load");

	LoadButton->SetClickCallback<CDetailWindow>(this, &CDetailWindow::LoadButtonClick);

	CEditorButton* CreateAnimationButton = Category->CreateWidget<CEditorButton>("Sprite", "CreateAnimation");
	CreateAnimationButton->SetSize(200, 30);
	CreateAnimationButton->SetClickCallback<CDetailWindow>(this, &CDetailWindow::AnimationButtonClick);

	m_vecSpriteComponent.push_back(Category);
}

void CDetailWindow::CreateCameraComponentWidget()
{
	//TODO 카메라 컴포넌트
}

void CDetailWindow::CreateTargetArmComponentWidget()
{
	//TODO 타겟암
}

void CDetailWindow::CreateCollider2DComponentWidget()
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

	ConfirmButton->SetClickCallback<CDetailWindow>(this, &CDetailWindow::ColliderSettingClick);
	ConfirmButton->SetSize(300, 30);
	m_vecColliderComponent.push_back(Category);
}

void CDetailWindow::CreateColliderPixelComponentWidget()
{
}

void CDetailWindow::ChangeWidget(CSceneComponent* Component)
{
	std::string s = Component->GetComponentTypeName();
	//=======씬 컴포넌트일때==========
	if (Component->GetComponentTypeName() == "SceneComponent")
	{
		size_t	Size = m_vecSceneComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSceneComponent[i]);
		}
	}
	//=======스프라이트 컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "SpriteComponent")
	{
		size_t	Size = m_vecSpriteComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSpriteComponent[i]);
		}

		if (Component)
		{
			CTexture* Texture = ((CSpriteComponent*)Component)->GetTexture();

			CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecSpriteComponent[0];

			CEditorImage* ImageWidget = Category->FindWidget<CEditorImage>("SpriteImage");

			ImageWidget->SetTexture(Texture);
		}
	}
	//=======카메라 컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "CameraComponent")
	{
		size_t	Size = m_vecCameraComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecCameraComponent[i]);
		}
	}
	//=======타겟암 컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "TargetArmComponent")
	{
		size_t	Size = m_vecTargetArmComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecTargetArmComponent[i]);
		}
	}
	//=======콜라이더(Box, OBB, 원, 픽셀)  컴포넌트일때==========
	else if (Component->GetComponentTypeName() == "ColliderBox2D" ||
		Component->GetComponentTypeName() == "ColliderOBB2D" || 
		Component->GetComponentTypeName() == "ColliderSphere2D" || 
		Component->GetComponentTypeName() == "ColliderPixel")
	{
		OutputDebugStringA("콜라이더");
		size_t	Size = m_vecColliderComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecColliderComponent[i]);
		}

		std::string Name = Component->GetComponentTypeName();
		CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecColliderComponent[0];

		CEditorInput* InputX = Category->FindWidget<CEditorInput>("InputX");
		CEditorInput* InputY = Category->FindWidget<CEditorInput>("InputY");
		CEditorInput* InputR = Category->FindWidget<CEditorInput>("InputRadian");
		CEditorText* Text = Category->FindWidget<CEditorText>("ColliderName");

		if (Name == "ColliderBox2D")
		{
			Text->SetText("ColliderBox2D");
			Vector2 v = ((CColliderBox2D*)Component)->GetBoxSize();
			InputX->SetFloat(v.x);
			InputY->SetFloat(v.y);

			InputR->SetFloat(0.f);
			InputR->ReadOnly(true);

		}
		else if (Name == "ColliderOBB2D")
		{
			Text->SetText("ColliderOBB2D");
			Vector2 v = ((CColliderOBB2D*)Component)->GetBoxHalfSize();
			InputX->SetFloat(v.x * 2.f);
			InputY->SetFloat(v.x * 2.f);

			InputR->SetFloat(0.f);
			InputR->ReadOnly(true);
		}
		else if (Name == "ColliderSphere2D")
		{
			Text->SetText("ColliderSphere2D");
			float  Radian = ((CColliderSphere2D*)Component)->GetInfo().Radius;			
			InputR->SetFloat(Radian);

			InputX->SetFloat(0.f);
			InputX->ReadOnly(true);
			InputY->SetFloat(0.f);
			InputY->ReadOnly(true);
		}
		else if (Name == "ColliderPixel")
		{
			Text->SetText("ColliderPixel");
		}
		else 
			return;
	}
}

void CDetailWindow::LoadButtonClick()
{
	OPENFILENAME	ofn = {};

	TCHAR	FullPath[MAX_PATH] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&ofn) != 0)
	{
		CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecSpriteComponent[0];

		CEditorImage* ImageWidget = Category->FindWidget<CEditorImage>("SpriteImage");

		if (ImageWidget)
		{
			TCHAR	wTexName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

			char	TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

			ImageWidget->SetTextureFullPath(TexName, FullPath);

			// 선택한 SpriteComponent의 Texture를 교체한다.
			if (m_SelectComponent)
			{
				((CSpriteComponent*)m_SelectComponent.Get())->SetTextureFullPath(TexName, FullPath);

			}
		}
	}
}

void CDetailWindow::ColliderSettingClick()
{
	CEditorTree<void*>* Category = (CEditorTree<void*>*)m_vecColliderComponent[0];

	CEditorText* Text = Category->FindWidget<CEditorText>("ColliderName");

	CEditorInput* InputX = Category->FindWidget<CEditorInput>("InputX");
	CEditorInput* InputY = Category->FindWidget<CEditorInput>("InputY");
	CEditorInput* InputR = Category->FindWidget<CEditorInput>("InputRadian");

	std::string s = Text->GetTextUTF8();

	CSceneComponent* component = m_SelectComponent;

	if (s == "ColliderBox2D")
	{
		Vector2 v(InputX->GetFloat(), InputY->GetFloat());
		((CColliderBox2D*)component)->SetBoxSize(v);
	}
	else if (s == "ColliderOBB2D")
	{
		Vector2 v(InputX->GetFloat(), InputY->GetFloat());
		((CColliderOBB2D*)component)->SetBoxHalfSize(v.x / 2.f, v.y / 2.f);
	}
	else if (s == "ColliderSphere2D")
	{
		float radian = InputR->GetFloat();
		((CColliderSphere2D*)component)->SetRadius(radian);
	}
	else if (s == "ColliderPixel")
	{

	}
	else
		return;


}

void CDetailWindow::AnimationButtonClick()
{
	//애니메이션 윈도우에 해당 컴포넌트 추가

	CNMyAnimationWindow2* AnimationWindow = CEditorGUIManager::GetInst()
		->FindEditorWindow<CNMyAnimationWindow2>("NMyAnimationWindow2");
		
	AnimationWindow->SetSelectComponent(m_SelectComponent);

	CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("NMyAnimationWindow2");
	if (Window)
		Window->Open();
}
