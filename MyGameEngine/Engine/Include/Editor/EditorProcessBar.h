#pragma once
#include "EditorWidget.h"
class CEditorProcessBar :
    public CEditorWidget
{
    friend class CEditorWindow;

protected:
    CEditorProcessBar();
    virtual ~CEditorProcessBar();

private:
    std::function<void()> m_ClickCallback;
    bool m_Set;
    int m_BarRange;

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

