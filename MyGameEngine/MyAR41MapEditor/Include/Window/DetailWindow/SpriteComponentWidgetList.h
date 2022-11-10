#pragma once
#include "ComponentWidgetList.h"
class CSpriteComponentWidgetList :
	public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

protected:
	CSpriteComponentWidgetList();
	~CSpriteComponentWidgetList();
public:
	class CSpriteComponent* m_Sprite;

	//�ִϸ��̼�
	class CEditorInput* m_PlayTime;
	class CEditorInput* m_PlayScale;
	class CEditorInput* m_AnimationClass;
	class CEditorListBox* m_AnimationList;
	
	//���׸���
	class CEditorInput* m_BaseColor[4];
	class CEditorInput* m_Opacity;

public:
	void SetSpriteContent(class CSpriteComponent* Sprite);

public:
	virtual bool Init();

private:
	void SelectTextureButtonClick();
	void CreateAnimationButtonClick();
	void AnimationSelectCallback(int Index, const std::string& Item);

	void BaseColorCallback();
	void OpacityCallback();
};

