#pragma once
#include "EditorWidget.h"
class CEditorCheckBox :
    public CEditorWidget
{
    friend class CEditorWindow;

protected:
    CEditorCheckBox();
    virtual ~CEditorCheckBox();

private:
    std::function<void()> m_CheckCallback;
    bool m_checked;

public:
    virtual bool Init();
    virtual void Render();

public:
    bool SetCheck(bool Enable)
    {
        m_checked = Enable;
    }
    bool GetCheck()
    {
        return m_checked;
    }

//public:
//    template <typename T>
//    void SetClickCallback(T* Obj, void(T::* Func)())
//    {
//        m_CheckCallback = std::bind(Func, Obj);
//    }
};

