#pragma once
#include "Editor\EditorWindow.h"
#include "Animation\Animation2D.h"
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
    class CMySequenceWindow* m_SeqWindow;
    //���ҽ� �Ŵ��� �ִϸ��̼�
    std::unordered_map<std::string, CSharedPtr<CAnimation2D>>* m_mapAnimation2D;
    class CAnimation2D* m_Animation;
    
    //�ִϸ��̼� ������ ��� �迭
    //std::list<class CAnimation2DData*> m_Animation2DData; //������ �ִϸ��̼� �����͸� ��� �迭
    
    //����Ʈ�� ����°� ������

    //�������
    class CEditorText* m_Messege; //�޽��� â
    class CEditorComboBox* m_LoadAnimCombo; //�ִϸ��̼� ������ �� �ִ� �޺��ڽ�
    class CEditorListBox* m_EventList; //�̺�Ʈ ����Ʈ
    
     
    //�׷�
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
    void ClearList();

    //�ݹ��Լ�
    void ComboBoxCallback(int SelectIndex, const std::string& Item);
    void ListCallback(int SelectIndex, const std::string& Item);
    void LoadSqcBtnCallback(); 
    void DeleteSqcBtnCallback();
    void SaveBtnCallback();

    const std::string TCHARToString(const TCHAR* ptsz);
};

