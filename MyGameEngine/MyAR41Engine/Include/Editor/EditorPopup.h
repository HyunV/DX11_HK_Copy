#pragma once
#include "EditorWidget.h"
class CEditorPopup :
    public CEditorWidget
{
    friend class CEditorWindow;

public:
    CEditorPopup();
    virtual ~CEditorPopup();

private:
    std::function<void()> m_ClickCallback;


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



