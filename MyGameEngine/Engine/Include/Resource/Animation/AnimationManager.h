#pragma once

#include "AnimationSequence2D.h"
#include "../../Animation/Animation2D.h"

class CAnimationManager
{
	friend class CResourceManager;

private:
	CAnimationManager();
	~CAnimationManager();

private:
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence2D>>	m_mapSequence2D;
	class CAnimation2DConstantBuffer* m_Anim2DBuffer;

	//내 코드
	std::unordered_map<std::string, CSharedPtr<CAnimation2D>> m_mapAnimation2D;

public:
	class CAnimation2DConstantBuffer* GetAnim2DConstantBuffer()	const
	{
		return m_Anim2DBuffer;
	}

public:
	bool Init();
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName,
		const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	bool CreateAnimationSequence2D(const std::string& Name, class CTexture* Texture);
	bool CreateAnimationSequence2DFullPath(const std::string& Name, const std::string& TextureName, const TCHAR* FullPath);
	bool CreateAnimationSequence2D(const std::string& Name, const std::string& TextureName, const std::vector<const TCHAR*>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool CreateAnimationSequence2DFullPath(const std::string& Name, const std::string& TextureName, const std::vector<const TCHAR*>& vecFullPath, int LoopCount = 0);
	bool AddSequence2DFrame(const std::string& Name, const Vector2& Start, const Vector2& End);
	bool AddSequence2DFrame(const std::string& Name, float StartX, float StartY, float EndX,
		float EndY);
	bool AddSequence2DFrameAll(const std::string& Name, int Count, const Vector2& Start, const Vector2& End);
	bool AddSequence2DFrameAll(const std::string& Name, int Count, float StartX, float StartY, float EndX,		
		float EndY);
	bool SaveSequence2D(const std::string& Name, const char* FullPath);
	bool LoadSequence2D(const std::string& Name, const char* FullPath);
	bool SaveSequence2D(const std::string& Name, const char* FileName, const std::string& PathName);
	bool LoadSequence2D(const std::string& Name, const char* FileName, const std::string& PathName);

	CAnimationSequence2D* FindAnimationSequence2D(const std::string& Name);
	void ReleaseAnimationSequence2D(const std::string& Name);

	//내 코드
	bool CreateAnimation2D(const std::string& Name);
	CAnimation2D* FindAnimation2D(const std::string& Name);
	void ReleaseAnimation2D(const std::string& Name);
	std::unordered_map<std::string, CSharedPtr<CAnimation2D>>* GetMapAnimation2D()
	{
		return &m_mapAnimation2D;
	}

};

