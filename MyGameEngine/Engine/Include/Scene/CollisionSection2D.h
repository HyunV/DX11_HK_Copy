#pragma once

#include "../EngineInfo.h"

class CCollisionSection2D
{
	friend class CSceneCollision;
	friend class CScene; 	//³» Ãß°¡

private:
	CCollisionSection2D();
	~CCollisionSection2D();

private:
	Vector2		m_Min;
	Vector2		m_Max;
	int			m_IndexX;
	int			m_IndexY;
	int			m_Index;
	std::list<CSharedPtr<class CCollider2D>>	m_ColliderList;

public:
	void AddCollider(class CCollider2D* Collider);
	void Collision(float DeltaTime);

	Vector2 GetMin() 
	{
		return m_Min;
	}
	Vector2 GetMax()
	{
		return m_Max;
	}
};

