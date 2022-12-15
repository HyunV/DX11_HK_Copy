#pragma once
#include "GameObject\GameObject.h"
class CPlayerAttack :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayerAttack();
	CPlayerAttack(const CPlayerAttack& Obj);
	virtual ~CPlayerAttack();

private:
	CSharedPtr<class CColliderSphere2D> m_Body; //∑Á∆Æ
	int m_Damage;
public:
	void SetDamage(int Damage)
	{
		m_Damage = Damage;
	}
	int GetDamage()
	{
		return m_Damage;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CPlayerAttack* Clone()    const;


private:
	void CollisionBegin(const CollisionResult& Result);
};

