#pragma once

#include "EditorWidget.h"

class CEditorButton :
    public CEditorWidget
{
    friend class CEditorWindow;

protected:
    CEditorButton();
    virtual ~CEditorButton();

private:
    std::function<void()>   m_ClickCallback;
    bool                    m_Click;

public:
    virtual bool Init();
    virtual void Render();

public:
    template <typename T>
    void SetClickCallback(T* Obj, void(T::* Func)())
    {
        m_ClickCallback = std::bind(Func, Obj);
    }
};

