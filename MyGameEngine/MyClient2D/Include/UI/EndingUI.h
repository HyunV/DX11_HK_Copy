#pragma once
#include "UI\UIWindow.h"
class CEndingUI :
    public CUIWindow
{
    friend class CSceneViewport;
    friend class CScene;

protected:
    CEndingUI();
    CEndingUI(const CEndingUI& Window);
    virtual ~CEndingUI();

protected:
    CSharedPtr<class CUIImage> m_Back;
    CSharedPtr<class CUIImage> m_ClearText;
    CSharedPtr<class CUIImage> m_UpFrame;
    CSharedPtr<class CUIImage> m_DownFrame;

    CSharedPtr<class CUIImage> m_ButtonBack;    
    CSharedPtr<class CUIButton>	m_MainButton;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CEndingUI* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

private:
    void MainButtonClick();

};

