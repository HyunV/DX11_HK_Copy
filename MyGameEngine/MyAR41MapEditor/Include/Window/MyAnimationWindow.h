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
    
    class CEditorInput* m_SequenceName;
    class CEditorInput* m_SequenceTextureName;
    class CEditorInput* m_FrameCount; //장 수
    class CEditorInput* m_InputLT[2];
    class CEditorInput* m_InputRB[2];

    class CEditorText* m_SaveMessege;

    TCHAR m_ImageFullPath[512];
    
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
};

