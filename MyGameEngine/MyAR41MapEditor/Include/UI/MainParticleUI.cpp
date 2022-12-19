#include "MainParticleUI.h"
#include "UI/MainDot.h"
#include "UI/MainSmoke.h"

CMainParticleUI::CMainParticleUI()
{
}

CMainParticleUI::CMainParticleUI(const CMainParticleUI& Window)
{
    m_WindowTypeName = "MainParticleUI";
}

CMainParticleUI::~CMainParticleUI()
{
}

void CMainParticleUI::Start()
{
    CUIWindow::Start();
}

bool CMainParticleUI::Init()
{
    CUIWindow::Init();

    return true;
}

void CMainParticleUI::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    for (int i = 0; i < 20; i++)
    {
        std::string name = "MainDot" + std::to_string(i + 1);
        CMainDot* dot = CreateWidget<CMainDot>(name);
    }
}

void CMainParticleUI::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);

    for (int i = 0; i < 10; i++)
    {
        std::string name = "MainSmoke" + std::to_string(i + 1);
        CMainSmoke* smoke = CreateWidget<CMainSmoke>(name);
    }
}

void CMainParticleUI::Render()
{
    CUIWindow::Render();
}
