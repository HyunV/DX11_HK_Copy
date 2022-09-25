#pragma once
#include "Editor\EditorWindow.h"
class CNMyAnimationWindow2 :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CNMyAnimationWindow2();
    virtual ~CNMyAnimationWindow2();

private:
    class CEditorInput* m_ActName;
    class CEditorText* m_SaveMessege;
    
    class CEditorListBox* m_AniList;
    std::vector<std::string> m_vecAct;

    class CEditorListBox* m_SqcList;
    std::vector<std::string> m_vecSqc;

    //�̹��� ����� ��ü�� ��������Ʈ ������Ʈ �����..?

    class CEditorInput* m_AnimationName; //�ִϸ��̼� ���ϸ�
    class CEditorInput* m_SelectedComponent; //������ ������Ʈ(������ ��������Ʈ)
    //CSharedPtr<class CSceneComponent> m_SelectComponent;

    class CEditorInput* m_SelectAct; //������ �ൿ
    class CEditorInput* m_SelectSqc; //������ ������

    class CEditorInput* m_PlayTime; //float
    class CEditorInput* m_PlayScale; //float
    class CEditorCheckBox* m_Loop;
    class CEditorCheckBox* m_Reverse;

    //CSharedPtr<class CAnimation2D> m_Animation;
    class CAnimation2D* m_Animation;
    class CSpriteComponent* m_SpriteComponent;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    void SetSelectComponent(const std::string& Item, CSceneComponent* Component);
private:
    void LoadSqc(); //������ ��� ������
    void ResetSetting(); //���� �� �ʱ�ȭ���ִ� �Լ�
    

private:
    //��ư �Լ���

    void LoadAnimationCallback();
    void AddActCallback(); //�ൿ �߰� ��ư
    void SaveAnimationCallback();
    void CreateAnimationCallback(); //�� �ִϸ��̼�
    void AddActAnimationCallback(); //�� �ִϸ��̼�

    void SelectActCallback(int SelectIndex, const std::string& Item);
    void SelectSqcCallback(int SelectIndex, const std::string& Item);
};

