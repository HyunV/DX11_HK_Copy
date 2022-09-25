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

    //이미지 모니터 대체할 스프라이트 컴포넌트 모니터..?

    class CEditorInput* m_AnimationName; //애니메이션 파일명
    class CEditorInput* m_SelectedComponent; //선택한 컴포넌트(무조건 스프라이트)
    //CSharedPtr<class CSceneComponent> m_SelectComponent;

    class CEditorInput* m_SelectAct; //선택한 행동
    class CEditorInput* m_SelectSqc; //선택한 시퀀스

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
    void LoadSqc(); //시퀀스 목록 가져옴
    void ResetSetting(); //값들 다 초기화해주는 함수
    

private:
    //버튼 함수들

    void LoadAnimationCallback();
    void AddActCallback(); //행동 추가 버튼
    void SaveAnimationCallback();
    void CreateAnimationCallback(); //새 애니메이션
    void AddActAnimationCallback(); //새 애니메이션

    void SelectActCallback(int SelectIndex, const std::string& Item);
    void SelectSqcCallback(int SelectIndex, const std::string& Item);
};

