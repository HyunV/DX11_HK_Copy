#pragma once
#include "Editor\EditorWindow.h"
//#include "Animation\Animation2DData.h"
class CMyAnimationWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;
    friend class CMySequenceWindow;

protected:
    CMyAnimationWindow();
    virtual ~CMyAnimationWindow();

private:
  //�������
    class CEditorText* m_Messege; //�޽��� â
    class CEditorComboBox* m_LoadAnimCombo;
    class CEditorListBox* m_EventList; //������Ʈ ������� ���ε� �Լ�
    //�̺�Ʈ ����Ʈ
    
    //�ִϸ��̼� ������ ��� �迭
    std::vector<class CAnimation2DData*> m_Animation2DData; //������ �ִϸ��̼� �����͸� ��� �迭

    //�׷�
    //class CEditorButton* Load Sequence button
    // class CEditorText* m_Messege; //������ �̺�Ʈ �̸�-> ������ ���� ����
    //class CEditorButton* delete event button //������ �̺�Ʈ�� ����

    class CEditorText* m_SelectedSqcText;
    class CEditorInput* m_PlayTimeInput; //float ��� �� ���� �����ϱ� ���� �ð�
    class CEditorInput* m_PlayScaleInput; //float ����
    class CEditorInput* m_FrameTime; //float �� �������� �����ϱ� ���� �ð�
    class CEditorCheckBox* m_Loop; // int count ������������ �ݺ� ����
    class CEditorCheckBox* m_Reverse; //����� ����

    //== end Group

    class CEditorInput* m_SaveAnimationInput;
    //����, ���� ��ư


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    //����Լ�
    void ClearSetting();
    void SetComboBox();
    void SetList();

    //�ݹ��Լ�
    void ComboBoxCallback(int SelectIndex, const std::string& Item);
    void ListCallback(int SelectIndex, const std::string& Item);
    void LoadSqcBtnCallback(); 
    void DeleteSqcBtnCallback();
    void SaveBtnCallback();

};

