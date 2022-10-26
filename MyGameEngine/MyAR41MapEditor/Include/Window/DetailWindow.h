#pragma once

#include "Editor\EditorWindow.h"

class CDetailWindow :
	public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CDetailWindow();
	virtual ~CDetailWindow();

protected:
	std::vector<class CComponentWidgetList*>	m_vecComponentWidgetList;
	//std::vector<class CEditorWidget*>	m_vecSceneComponent;
	//std::vector<class CEditorWidget*>	m_vecSpriteComponent;
	//std::vector<class CEditorWidget*>	m_vecCameraComponent;
	//std::vector<class CEditorWidget*>	m_vecTargetArmComponent;
	//std::vector<class CEditorWidget*>	m_vecColliderComponent;
	
	CSharedPtr<class CSceneComponent> m_SelectComponent;

public:
	class CSceneComponent* GetSelectComponent()	const
	{
		return m_SelectComponent;
	}

	class CComponentWidgetList* GetComponentWidgetList(const std::string& Name);

public:
	void SetSelectComponent(class CSceneComponent* Component);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	//void CreateSceneComponentWidget();
	//void CreateSpriteComponentWidget();
	//void CreateCameraComponentWidget();
	//void CreateTargetArmComponentWidget();
	
	//collider
	//void CreateCollider2DComponentWidget();
	//void CreateColliderPixelComponentWidget();
	

	void ChangeWidget(class CSceneComponent* Component);

private:
	void LoadButtonClick();
	//void ColliderSettingClick();
	//void AnimationButtonClick();

	void CreateEditorWidgetList(ESceneComponentType Type);
};

