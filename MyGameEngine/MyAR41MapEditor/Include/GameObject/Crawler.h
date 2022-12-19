#pragma once
#include "GameObject\GameObject.h"
class CCrawler :
    public CGameObject
{
	friend class CScene;

protected:
	CCrawler();
	CCrawler(const CCrawler& Obj);
	virtual ~CCrawler();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CGravityAgent> m_GravityAgent; //중력 컴포넌트
	CSharedPtr<class CAnimation2D> m_Anim; //애니메이션

	enum class EMonsterState
	{
		Fall,
		Walk,
		TurnOn,
		Death,
	};

	EMonsterState m_CurState; //현재 상태
	EMonsterState m_PrevState;//이전 상태

	float m_Dir;

	float m_Time; //행동 변화 확인 용 변수(사망 시 멈추고 200으로 고정)
	float m_MaterialChangeTime; //피격시 색 변하는 시간

	float m_Accel;

private:
	int m_HP;

private:
	void SpriteAnimationSetting();
	void SetAnimation(); //애니메이션 스케일, 펑션
	void SetCurAnim(EMonsterState State); //애니메이션, 사운드, 시간 세팅 함수
	

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CCrawler* Clone()    const;

public:
	void ChangeDir(); //애니메이션 방향전환 end함수
	void CheckDir(); //방향 세팅 함수
	void CreateGio(); //사망시 돈 생성하는 함수

private:
	void CollisionBegin(const CollisionResult& Result);
};

