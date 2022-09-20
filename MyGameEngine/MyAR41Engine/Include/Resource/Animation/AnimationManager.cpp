#include "AnimationManager.h"

CAnimationManager::CAnimationManager()
{
}

CAnimationManager::~CAnimationManager()
{
}

bool CAnimationManager::Init()
{
	return true;
}

bool CAnimationManager::CreateAnimationSequence2D(const std::string& Name, 
	const std::string& TextureName, const TCHAR* FileName, const std::string& PathName)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (Sequence)
		return true;

	Sequence = new CAnimationSequence2D;

	Sequence->SetName(Name);

	if (!Sequence->Init(TextureName, FileName, PathName))
	{
		SAFE_DELETE(Sequence);
		return false;
	}

	m_mapSequence2D.insert(std::make_pair(Name, Sequence));

	return true;
}

bool CAnimationManager::CreateAnimationSequence2D(const std::string& Name, 
	CTexture* Texture)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (Sequence)
		return true;

	Sequence = new CAnimationSequence2D;

	Sequence->SetName(Name);

	if (!Sequence->Init(Texture))
	{
		SAFE_DELETE(Sequence);
		return false;
	}

	m_mapSequence2D.insert(std::make_pair(Name, Sequence));

	return true;
}

bool CAnimationManager::AddSequence2DFrame(const std::string& Name, const Vector2& Start, const Vector2& End)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (!Sequence)
		return false;

	Sequence->AddFrame(Start, End);

	return true;
}

bool CAnimationManager::AddSequence2DFrame(const std::string& Name, float StartX, 
	float StartY, float EndX, float EndY)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (!Sequence)
		return false;

	Sequence->AddFrame(StartX, StartY, EndX, EndY);

	return true;
}

bool CAnimationManager::SaveSequence2D(const std::string& Name, const char* FullPath)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (!Sequence)
		return false;

	return Sequence->Save(FullPath);
}

bool CAnimationManager::LoadSequence2D(const std::string& Name, const char* FullPath)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (!Sequence)
		return false;

	return Sequence->Load(FullPath);
}

bool CAnimationManager::SaveSequence2D(const std::string& Name, const char* FileName, 
	const std::string& PathName)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (!Sequence)
		return false;

	return Sequence->Save(FileName, PathName);
}

bool CAnimationManager::LoadSequence2D(const std::string& Name, const char* FileName, 
	const std::string& PathName)
{
	CAnimationSequence2D* Sequence = FindAnimationSequence2D(Name);

	if (!Sequence)
		return false;

	return Sequence->Load(FileName, PathName);
}

CAnimationSequence2D* CAnimationManager::FindAnimationSequence2D(const std::string& Name)
{
	auto	iter = m_mapSequence2D.find(Name);

	if (iter == m_mapSequence2D.end())
		return nullptr;

	return iter->second;
}

void CAnimationManager::ReleaseAnimationSequence2D(const std::string& Name)
{
	auto	iter = m_mapSequence2D.find(Name);

	if (iter != m_mapSequence2D.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapSequence2D.erase(iter);
	}
}
