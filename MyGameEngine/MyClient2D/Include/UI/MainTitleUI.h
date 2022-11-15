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
    CSharedPtr<class CUIImage>  m_Back; //�޹��
    CSharedPtr<class CUIImage>  m_Logo; //�ΰ�
    CSharedPtr<class CUIImage>  m_Dev;  //���߻� �ΰ�

    //��ư
    CSharedPtr<class CUIText>	m_StartTitle; //���� ����
    CSharedPtr<class CUIText>	m_ExitTitle;  //���� ����

    CSharedPtr<class CUIButton>	m_StartButton;
    CSharedPtr<class CUIButton>	m_ExitButton;
    
    CSharedPtr<class CUIImage> m_Cursor[4]; //Ŀ�� ������
    
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

