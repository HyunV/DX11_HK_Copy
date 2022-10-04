#pragma once

#include "../EngineInfo.h"

struct Section2D
{
	//�Ʒ������� ���� Y+
	/*
	���� 6x3 ���� ������ �����ٸ�
	12 13 14 15 16 17
	 6  7  8  9 19 11
	 0  1  2  3  4  5

	 �̷������� ���Ǹ��� �ε����� ����������̴�.
	*/

	std::vector<class CCollisionSection2D*>	vecSection;
	int		CountX; // ���� ĭ ����
	int		CountY; // ���� ĭ ����
	int		Count;	
	Vector2	WorldStart;	//������ ���� ��ŸƮ����?(���ϴ� 0,0)
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

public:
	void AddCollider(class CCollider* Collider);
	
	Section2D* GetSection()
	{
		return &m_Section2D;
	}

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
	void CheckSection(class CCollider* Collider);
};

