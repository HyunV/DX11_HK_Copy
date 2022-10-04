#pragma once
#include "Editor\EditorWindow.h"
class CSectionWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CSectionWindow();
    virtual ~CSectionWindow();

private:
    class CEditorInput* m_SelectScene;
    class CEditorInput* m_InputX;
    class CEditorInput* m_InputY;
    class CEditorInput* m_IndexCount;
    class CEditorCheckBox* m_isPreview;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
private:
    void CreatePreviewObject(int x, int y);
private:
    void ConfirmBtnCallback();
    void isCheckCallback();


};

