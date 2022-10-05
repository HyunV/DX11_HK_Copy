#include "UIWindow.h"

CUIWindow::CUIWindow() :
	m_ZOrder(0),
	m_Start(false)
{
}

CUIWindow::CUIWindow(const CUIWindow& Window) :
	CRef(Window)
{
	m_ZOrder = Window.m_ZOrder;
	m_vecWidget = Window.m_vecWidget;
	m_Size = Window.m_Size;
	m_Start = false;
}

CUIWindow::~CUIWindow()
{
}

void CUIWindow::Start()
{
	size_t	Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Start();
	}

	// ZOrder 순서에 따라 정렬한다.
}

bool CUIWindow::Init()
{
	return true;
}

void CUIWindow::Update(float DeltaTime)
{
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CUIWindow::PostUpdate(float DeltaTime)
{
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CUIWindow::Render()
{
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();
		++iter;
	}
}

CUIWindow* CUIWindow::Clone()
{
	return new CUIWindow(*this);
}

void CUIWindow::Save(FILE* File)
{
}

void CUIWindow::Load(FILE* File)
{
}
