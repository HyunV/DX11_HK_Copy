#pragma once
#include "Editor\EditorWindow.h"
class CMyAnimationWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CMyAnimationWindow();
    virtual ~CMyAnimationWindow();

private:
    //필요한 변수들
    EImageType m_ImageType;
    class CEditorComboBox* m_Combo;
    class CEditorText* m_HintText;
    class CEditorListBox* m_List;
    std::vector<const TCHAR*> m_vecFullPathFileName;
    std::vector<Animation2DFrameData> m_vecFrame;
    
    class CEditorInput* m_SequenceName;
    class CEditorInput* m_SequenceTextureName;
    class CEditorInput* m_FrameCount; //장 수
    class CEditorInput* m_InputStartPoint[2]; //시작지점 x, y
    class CEditorInput* m_InputWidthHeight[2]; // 이미지 너비, 높이
    class CEditorImage* m_PreviewImage; //미리보기 이미지

    class CEditorText* m_Messege;
    class CEditorSliderBar* m_Slide;
    class CEditorInput* m_PlayScale;

    TCHAR m_ImageFullPath[512];

    bool m_Play;
    float m_Time;
    
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void SelectComboCallback(int SelectIndex, const std::string& Item);
    void SelectLoadImageButtonCallback();
    const std::string TCHARToString(const TCHAR* ptsz);
    void HideEditorText(bool enable);
    void SelectListCallback(int SelectIndex, const std::string& Item);
    void CreateSequence(EImageType type);
    void SaveSequence();

    void PlayButton();
    void PauseButton();
    void StopButton();

    void SliderCallback();
    void SetAtlasFrame();

};

