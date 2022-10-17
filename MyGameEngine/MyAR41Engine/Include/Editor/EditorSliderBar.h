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
    int m_CurrentValue;
    int m_MaxBarRange;
    int m_MinBarRange;

public:
    virtual bool Init();
    virtual void Render();

    void SetBarMaxRange(int Max)
    {
        m_MaxBarRange = Max;
    }
    void SetBarMinRange(int Min)
    {
        m_MinBarRange = Min;
    }
    int GetBarMaxRange()
    {
        return m_MaxBarRange;
    }

    int GetCurrentValue()
    {
        return m_CurrentValue;
    }

    void AddCurrentValue()
    {
        m_CurrentValue++;
    }
    void ResetCurrentValue()
    {
        m_CurrentValue = m_MinBarRange;
    }

public:
    template <typename T>
    void SetClickCallback(T* Obj, void(T::* Func)())
    {
        m_ClickCallback = std::bind(Func, Obj);
    }
};



