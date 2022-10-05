#include "UIButton.h"

CUIButton::CUIButton()
{
}

CUIButton::CUIButton(const CUIButton& Button) :
    CUIWidget(Button)
{
}

CUIButton::~CUIButton()
{
}

void CUIButton::Start()
{
    CUIWidget::Start();
}

bool CUIButton::Init()
{
    if (!CUIWidget::Init())
        return false;

    return true;
}

void CUIButton::Update(float DeltaTime)
{
    CUIWidget::Update(DeltaTime);
}

void CUIButton::PostUpdate(float DeltaTime)
{
    CUIWidget::PostUpdate(DeltaTime);
}

void CUIButton::Render()
{
    // 상수버퍼를 채워준다.
    m_CBuffer->SetTextureEnable(false);

    CUIWidget::Render();
}

CUIButton* CUIButton::Clone()
{
    return new CUIButton(*this);
}

void CUIButton::Save(FILE* File)
{
}

void CUIButton::Load(FILE* File)
{
}
