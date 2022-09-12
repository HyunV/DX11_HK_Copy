#pragma once
#include "EditorWidget.h"
class CEditorSliderBar :
    public CEditorWidget
{
    friend class CEditorWindow;

protected:
    CEditorSliderBar();
    virtual ~CEditorSliderBar();

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



