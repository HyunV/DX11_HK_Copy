#include "DetailWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Component/SceneComponent.h"

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
}

void CDetailWindow::SetSelectComponent(CSceneComponent* Component)
{
	if (m_SelectComponent->GetComponentTypeName() !=
		Component->GetComponentTypeName())
	{
		ClearWidget();

		// 타입에 맞는 GUI 추가
		ChangeWidget(Component);
	}

	m_SelectComponent = Component;
}

bool CDetailWindow::Init()
{
	CreateSceneComponentWidget();
	CreateSpriteComponentWidget();
	CreateCameraComponentWidget();
	CreateTargetArmComponentWidget();

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
}

void CDetailWindow::CreateSpriteComponentWidget()
{
}

void CDetailWindow::CreateCameraComponentWidget()
{
}

void CDetailWindow::CreateTargetArmComponentWidget()
{
}

void CDetailWindow::ChangeWidget(CSceneComponent* Component)
{
	if (Component->GetComponentTypeName() == "SceneComponent")
	{
		size_t	Size = m_vecSceneComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSceneComponent[i]);
		}
	}

	else if (Component->GetComponentTypeName() == "SpriteComponent")
	{
		size_t	Size = m_vecSpriteComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecSpriteComponent[i]);
		}
	}

	else if (Component->GetComponentTypeName() == "CameraComponent")
	{
		size_t	Size = m_vecCameraComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecCameraComponent[i]);
		}
	}

	else if (Component->GetComponentTypeName() == "TargetArmComponent")
	{
		size_t	Size = m_vecTargetArmComponent.size();

		for (size_t i = 0; i < Size; ++i)
		{
			AddWidget(m_vecTargetArmComponent[i]);
		}
	}
}
