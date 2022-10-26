#pragma once

#include "../EngineInfo.h"

struct Section2D
{
	//아래서부터 위가 Y+
	/*
	만약 6x3 으로 섹션을 나눈다면
	12 13 14 15 16 17
	 6  7  8  9 19 11
	 0  1  2  3  4  5

	 이런식으로 섹션마다 인덱스가 만들어질것이다.
	*/

	std::vector<class CCollisionSection2D*>	vecSection;
	int		CountX; // 가로 칸 개수
	int		CountY; // 세로 칸 개수
	int		Count;	
	Vector2	WorldStart;	//섹션의 월드 스타트지점?(좌하단 0,0)
	Vector2	SectionSize;
	Vector2	WorldSize;
};

struct Section3D
{
	std::vector<class CCollisionSection3D*>	vecSection;
	int		CountX;
	int		CountY;
	int		CountZ;
	int		Count;
	Vector3	WorldStart;
	Vector3	SectionSize;
	Vector3	WorldSize;
};

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CScene* m_Owner;
	Section2D	m_Section2D;
	Section3D	m_Section3D;
	std::list <CSharedPtr<class CCollider>>	m_ColliderList;
	std::unordered_map<std::string, PixelInfo*>	m_mapPixelCollision;
	CSharedPtr<class CCollider> m_MouseCollision;
	bool		m_CollisionWidget;

public:
	void AddCollider(class CCollider* Collider);
	bool CollisionWidget();

public:
	bool Init();
	void Update(float DeltaTime);
	void CreateSection2D(int CountX, int CountY, const Vector2& WorldStart,
		const Vector2& SectionSize);
	void CreateSection3D(int CountX, int CountY, int CountZ, const Vector3& WorldStart,
		const Vector3& SectionSize);
	void Save(FILE* File);
	void Load(FILE* File);

private:
	void CollisionMouse(float DeltaTime);
	void CheckSection(class CCollider* Collider);

public:
	bool CreatePixelCollision(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
	bool CreatePixelCollisionFullPath(const std::string& Name, const TCHAR* FullPath);
	bool CreatePixelCollisionMultibyte(const std::string& Name, const char* FileName, const std::string& PathName = TEXTURE_PATH);
	bool CreatePixelCollisionMultibyteFullPath(const std::string& Name, const char* FullPath);
	PixelInfo* FindPixelCollision(const std::string& Name);
};

