#pragma once
#include "GameObject/GameObject.h"

class CMonGenerator :
    public CGameObject
{
	friend class CScene;

protected:
	CMonGenerator();
	CMonGenerator(const CMonGenerator& Obj);
	virtual ~CMonGenerator();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;
	float m_Time;
	bool m_Start;
	float m_Delay;
	float m_FallX;
	float m_FallY;
	int m_CollisionCount;

public:
	void SetDelayTime(float Time)
	{
		m_Delay = Time;
	}
	float GetDelayTime()
	{
		return m_Delay;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CMonGenerator* Clone()    const;

public:
	void StartGenerate(bool Enable);
	void MonsterGenerate();
private:
	void CollisionStart(const CollisionResult& Result);
};

