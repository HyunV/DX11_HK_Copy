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
	bool m_BallMod;
	Vector2 NormalBallPivot; //우, 좌 일때
	Vector2 DarkBallPivot;
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderSphere2D>	m_Body;
	CSharedPtr<class CGravityAgent> m_Gravity;
	CSharedPtr<class CAnimation2D> m_Anim; //애니메이션

	float m_Dir;

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
	void SetDirection(float Dir);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMyBullet* Clone() const;

public:
	void DarkBallMod();
	void NormalBallMod();
	void HitBall();

private:
	void CollisionBullet(const CollisionResult& result);
};

