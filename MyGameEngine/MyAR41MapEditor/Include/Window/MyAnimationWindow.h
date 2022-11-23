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
    //리소스 매니저 애니메이션
    std::unordered_map<std::string, CSharedPtr<CAnimation2D>>* m_mapAnimation2D;
    class CAnimation2D* m_Animation;
    
    //애니메이션 데이터 담는 배열
    //std::list<class CAnimation2DData*> m_Animation2DData; //세팅한 애니메이션 데이터를 담는 배열
    
    //리스트로 만드는게 좋을듯

    //멤버변수
    class CEditorText* m_Messege; //메시지 창
    class CEditorComboBox* m_LoadAnimCombo; //애니메이션 선택할 수 있는 콤보박스
    class CEditorListBox* m_EventList; //이벤트 리스트
    
     
    //그룹
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
    void ClearList();

    //콜백함수
    void ComboBoxCallback(int SelectIndex, const std::string& Item);
    void ListCallback(int SelectIndex, const std::string& Item);
    void LoadSqcBtnCallback(); 
    void DeleteSqcBtnCallback();
    void SaveBtnCallback();

    const std::string TCHARToString(const TCHAR* ptsz);
};

