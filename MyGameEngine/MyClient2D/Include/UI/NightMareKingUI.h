#pragma once
#include "UI\UIWindow.h"

class CNightMareKingUI :
    public CUIWindow
{
    friend class CSceneViewport;
    friend class CScene;

protected:
    CNightMareKingUI();
    CNightMareKingUI(const CNightMareKingUI& Window);
    virtual ~CNightMareKingUI();

private:
    std::vector<class CUIText*> m_vecText;
    float m_Time;


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
    
};

