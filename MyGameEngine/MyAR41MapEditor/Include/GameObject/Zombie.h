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

	float m_Time; //행동 변화 확인 용 변수(사망 시 멈추고 200으로 고정)
	float MaterialChangeTime; //피격시 색 변하는 시간

public:
	//체력
	int m_HP; //init에서 세팅
private:
	//Init 혹은 Start에서 수행하는 리소스 세팅 함수
	void SetSounds();
	void SpriteAnimationSetting();
	void SetAnimation(); //애니메이션 스케일, 펑션
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
	//업데이트 관련 함수
	void CheckDir(); //방향 세팅 함수
	void SetCurAnim(EMonsterState State); //애니메이션, 사운드, 시간 세팅 함수

	void ChangeDir(); //애니메이션 방향전환 end함수

	void CreateGio(); //사망시 돈 생성하는 함수
private:
	void CollisionBegin(const CollisionResult& Result);
	void SightCollisionBegin(const CollisionResult& Result);
};

