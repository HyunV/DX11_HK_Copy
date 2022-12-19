#pragma once
#include "UI\UIWindow.h"
class CMainBackUI :
    public CUIWindow
{
    friend class CSceneViewport;
    friend class CScene;

protected:
    CMainBackUI();
    CMainBackUI(const CMainBackUI& Window);
    virtual ~CMainBackUI();

protected:
    CSharedPtr<class CUIImage>  m_Back; //µÞ¹è°æ

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMainBackUI* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

