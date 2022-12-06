#pragma once
#include "UI\UIWindow.h"
#include "EngineInfo.h"
class CMessageBoxUI :
    public CUIWindow
{
    friend class CSceneViewport;
    friend class CScene;

protected:
    CMessageBoxUI();
    CMessageBoxUI(const CMessageBoxUI& Window);
    virtual ~CMessageBoxUI();

protected:
    class CUIText* m_NPCName;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
public:
    void ElderBugMessage();
    void HonnetMessage();
    void BrumMessage();
public:
    void CloseBox();
};

