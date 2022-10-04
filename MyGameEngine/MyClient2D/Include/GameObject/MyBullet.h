#pragma once
#include "GameObject/GameObject.h"
class CMyBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CMyBullet();
    CMyBullet(const CMyBullet& Obj);
    virtual ~CMyBullet();

private:
    float m_Angle;
    float m_Distance;
    float m_Damage;
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSceneComponent>	m_RightChild;

public:
	void SetCollisionProfileName(const std::string& Name);

public:
	void SetDamage(float Damage)
	{
		m_Damage = Damage;
	}

	void SetDistance(float Dist)
	{
		m_Distance = Dist;
	}

	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMyBullet* Clone() const;

private:
	void CollisionBullet(const CollisionResult& result);
};

