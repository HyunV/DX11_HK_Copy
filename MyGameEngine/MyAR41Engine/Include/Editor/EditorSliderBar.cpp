#include "EditorSliderBar.h"

CEditorSliderBar::CEditorSliderBar() :
    m_BarRange(0)
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
    m_Set = ImGui::SliderInt(m_NameUTF8.c_str(), &m_BarRange, 0, 100);

    if (m_Set && m_ClickCallback)
        m_ClickCallback();

}
