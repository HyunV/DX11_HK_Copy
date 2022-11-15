#pragma once

#include "UI\UIWindow.h"

class CMyLoadingUI :
	public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CMyLoadingUI();
	CMyLoadingUI(const CMyLoadingUI& Window);
	virtual ~CMyLoadingUI();

protected:
	//CSharedPtr<class CUIImage>	m_Back;
	//CSharedPtr<class CUIProgressBar>	m_LoadingBar;
	CSharedPtr<class CUINumber>	m_LoadingAnim;
	float m_count;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMyLoadingUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

