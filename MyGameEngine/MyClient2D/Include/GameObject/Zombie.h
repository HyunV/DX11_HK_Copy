#pragma once
#include "GameObject\GameObject.h"
class CZombie :
    public CGameObject
{
	friend class CScene;

protected:
	CZombie();
	CZombie(const CZombie& Obj);
	virtual ~CZombie();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CColliderBox2D>	m_Sight;
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CGravityAgent> m_GravityAgent; //중력 컴포넌트
	CSharedPtr<class CAnimation2D> m_Anim; //애니메이션

	//SightCollider
	struct SkillCoolDownInfo
	{
		float	CoolDown;
		bool	CoolDownEnable;
	};

	enum class EMonsterState {
		Idle,
		Walk,
		TurnOn,
		Attack,
		Attacking,
		Death
	};

	std::vector<SkillCoolDownInfo> m_vecCoolDown;
	EMonsterState m_CurState; //현재 상태
	EMonsterState m_PrevState;//이전 상태

	//방향
	float m_Dir;
	float m_Angle;

	//
	float m_Time;

	float MaterialChangeTime; //피격시 색 변하는 시간

public:
	//체력
	int m_HP;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CZombie* Clone()    const;
private:
	//모션들
	void Attack();
private:
	void SetSounds();
	void SpriteAnimationSetting();
	void SetAnimation(); //애니메이션 스케일, 펑션

	void CheckDir();
	void SetNextState();
	void SetCurAnim(EMonsterState State);

	void ChangeDir();

	void CreateGio();
private:
	void CollisionBegin(const CollisionResult& Result);
	void CollisionEnd(const CollisionResult& Result);
	void SightCollisionBegin(const CollisionResult& Result);
};

