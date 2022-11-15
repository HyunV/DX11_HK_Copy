#pragma once
#include "UI\UIWindow.h"
class CMainTitleUI :
    public CUIWindow
{
    friend class CSceneViewport;
    friend class CScene;

protected:
    CMainTitleUI();
    CMainTitleUI(const CMainTitleUI& Window);
    virtual ~CMainTitleUI();

protected:
    CSharedPtr<class CUIImage>  m_Back; //뒷배경
    CSharedPtr<class CUIImage>  m_Logo; //로고
    CSharedPtr<class CUIImage>  m_Dev;  //개발사 로고

    //버튼
    CSharedPtr<class CUIText>	m_StartTitle; //게임 시작
    CSharedPtr<class CUIText>	m_ExitTitle;  //게임 종료

    CSharedPtr<class CUIButton>	m_StartButton;
    CSharedPtr<class CUIButton>	m_ExitButton;
    
    CSharedPtr<class CUIImage> m_Cursor[4]; //커서 아이콘
    
    //CSharedPtr<class CUIImage> m_Test;


public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMainTitleUI* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

private:
    void StartButtonClick();
    void ExitButtonClick();
};

