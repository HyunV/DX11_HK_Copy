#include "EditorSliderBar.h"

CEditorSliderBar::CEditorSliderBar() :
    m_CurrentValue(0),
    m_MaxBarRange(100),
    m_MinBarRange(0)
{
}

CEditorSliderBar::~CEditorSliderBar()
{
}

bool CEditorSliderBar::Init()
{
    return true;
}

void CEditorSliderBar::Render()
{
    m_Set = ImGui::SliderInt(m_NameUTF8.c_str(), &m_CurrentValue, m_MinBarRange, m_MaxBarRange);

    //if (m_Set && m_ClickCallback)
    //    m_ClickCallback();

}
