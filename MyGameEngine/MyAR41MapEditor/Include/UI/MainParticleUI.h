#pragma once
#include "UI\UIWindow.h"
class CMainParticleUI :
    public CUIWindow
{
    friend class CSceneViewport;
    friend class CScene;

protected:
    CMainParticleUI();
    CMainParticleUI(const CMainParticleUI& Window);
    virtual ~CMainParticleUI();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();

};

