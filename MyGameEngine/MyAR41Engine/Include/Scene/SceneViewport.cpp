#include "SceneViewport.h"

CSceneViewport::CSceneViewport()
{
}

CSceneViewport::~CSceneViewport()
{
}

void CSceneViewport::LoadComplete()
{
}

void CSceneViewport::Start()
{
	size_t	Size = m_vecWindow.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWindow[i]->Start();
	}

	// ZOrder 순서에 따라 정렬한다.
}

bool CSceneViewport::Init()
{
	return true;
}

void CSceneViewport::Update(float DeltaTime)
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
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

void CSceneViewport::PostUpdate(float DeltaTime)
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
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

void CSceneViewport::Render()
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWindow.erase(iter);
			iterEnd = m_vecWindow.end();
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

void CSceneViewport::Save(FILE* File)
{
	int	Count = (int)m_vecWindow.size();

	fwrite(&Count, sizeof(int), 1, File);

	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		std::string	TypeName = (*iter)->GetWindowTypeName();

		int	Length = (int)TypeName.length();
		fwrite(&Length, sizeof(int), 1, File);
		fwrite(TypeName.c_str(), 1, Length, File);

		(*iter)->Save(File);
	}
}

void CSceneViewport::Load(FILE* File)
{
	int	Count = 0;

	fread(&Count, sizeof(int), 1, File);

	for (int i = 0; i < Count; ++i)
	{
		char	TypeName[256] = {};
		int	Length = 0;

		fread(&Length, sizeof(int), 1, File);
		fread(TypeName, 1, Length, File);

		CUIWindow* CDO = CUIWindow::FindCDO(TypeName);

		CUIWindow* Window = CDO->Clone();

		Window->m_Owner = this;
		Window->m_Scene = m_Owner;

		Window->Load(File);

		m_vecWindow.push_back(Window);
	}
}
