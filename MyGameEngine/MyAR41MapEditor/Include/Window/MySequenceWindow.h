#pragma once
#include "Editor\EditorWindow.h"
class CMySequenceWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CMySequenceWindow();
    virtual ~CMySequenceWindow();

private:
    class CAnimationSequence2D* m_Sequence;

    //필요한 변수들
    EImageType m_ImageType;
    class CEditorListBox* m_List; //이미지 리스트
    std::vector<const TCHAR*> m_vecFullPathFileName; //풀경로 저장 벡터(동적할당)
    //class CTexture* m_Texture;

    std::vector<Animation2DFrameData> m_vecFrame; //해당인덱스에 들어갈 Start End 포인트

    class CEditorInput* m_SequenceName; //인풋_파일명 string
    class CEditorInput* m_FrameCount; //인풋_장 수 int
    class CEditorInput* m_LoopCount; //인풋_루프 시작점 int
    class CEditorInput* m_InputStartEnd[2]; //시작지점 x, y float
    class CEditorInput* m_InputWidthHeight[2]; // 이미지 너비, 높이 float

    //미리보기 변수
    class CEditorText* m_Messege; //미리보기 메시지

    class CEditorImage* m_PreviewImage; //미리보기 이미지
    class CEditorSliderBar* m_Slide;

    class CEditorInput* m_PlayScale; //배율
    bool m_Play;
    float m_Time;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void SelectLoadImageButtonCallback(); //이미지 로드 버튼
    void SelectLoadSequenceCallback(); //시퀀스 로드 버튼
    const std::string TCHARToString(const TCHAR* ptsz);

    void SetList(); //리스트 정렬 함수
    void SetSlide(EImageType Type); //슬라이드 세팅 함수

    void AddFullPath(const TCHAR* FullPath); //동적할당

    void SelectListCallback(int SelectIndex, const std::string& Item);
    void CreateSequence(EImageType type);
    void SaveSequence(); //에디터 값들로 시퀀스 만드는 함수
    void LoadSequence(class CAnimationSequence2D* Sequence); //받은 시퀀스로 에디터 값 세팅하는 함수

    void PlayButton();
    void PauseButton();
    void StopButton();
    void ClearSetting(); //모두 초기화

    void SliderCallback();
    void SetAtlasFrame(int FrameCount);

};

