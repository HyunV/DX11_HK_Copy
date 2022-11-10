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
  //멤버변수
    class CEditorText* m_Messege; //메시지 창
    class CEditorComboBox* m_LoadAnimCombo;
    class CEditorListBox* m_EventList; //오브젝트 집어넣은 바인딩 함수
    //이벤트 리스트
    
    //애니메이션 데이터 담는 배열
    std::vector<class CAnimation2DData*> m_Animation2DData; //세팅한 애니메이션 데이터를 담는 배열

    //그룹
    //class CEditorButton* Load Sequence button
    // class CEditorText* m_Messege; //선택한 이벤트 이름-> 시퀀스 명을 따름
    //class CEditorButton* delete event button //선택한 이벤트를 제거

    class CEditorText* m_SelectedSqcText;
    class CEditorInput* m_PlayTimeInput; //float 모션 한 번이 동작하기 위한 시간
    class CEditorInput* m_PlayScaleInput; //float 배율
    class CEditorInput* m_FrameTime; //float 한 프레임이 증가하기 위한 시간
    class CEditorCheckBox* m_Loop; // int count 프레임으로의 반복 여부
    class CEditorCheckBox* m_Reverse; //역재생 여부

    //== end Group

    class CEditorInput* m_SaveAnimationInput;
    //수정, 저장 버튼


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    //멤버함수
    void ClearSetting();
    void SetComboBox();
    void SetList();

    //콜백함수
    void ComboBoxCallback(int SelectIndex, const std::string& Item);
    void ListCallback(int SelectIndex, const std::string& Item);
    void LoadSqcBtnCallback(); 
    void DeleteSqcBtnCallback();
    void SaveBtnCallback();

};

