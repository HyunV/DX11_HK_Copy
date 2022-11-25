#pragma once

#include "GameObject/GameObject.h"

class CPlayer2D :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& Obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<class CColliderBox2D> m_Body; //루트
	CSharedPtr<class CSpriteComponent>	m_Sprite; //애니메이션

	CSharedPtr<class CCameraComponent>	m_Camera; //앵글 위로 좀만 올리기
	CSharedPtr<class CTargetArm>	m_Arm;

	//이펙트 스프라이트
	CSharedPtr<class CSpriteComponent> m_DashSprite; // 뒤
	CSharedPtr<class CSpriteComponent> m_DoubleJumpSprite; //뒤
	CSharedPtr<class CSpriteComponent> m_AttackSprite; //앞
	CSharedPtr<class CSpriteComponent> m_FireSprite; //앞
	//더블점프, 대시, 

	CSharedPtr<class CGravityAgent> m_GravityAgent; //중력 컴포넌트
	
	CSharedPtr<class CAnimation2D> m_Anim; //애니메이션
	
private:
	//이동관련
	Vector3 m_PrevPos; //Move 값 판별하기 위한 prevPos

	//점프관련
	int m_Jumping; //점프여부, 횟수
	
	//대시
	float m_DashEndPos; //대시할때 최종으로 이동하는 지점
	int m_DashCount; //공중대시는 1번만 가능
	bool m_KeyLock; //대시 시 키 잠금

	//이동관련 방향
	float m_Dir; //Left시 -1, Right시 1
	float m_Angle; //Left시 180, Right시 0;
	
	//공격관련
	float m_DoubleAttack;
	bool m_UpAttack;
	bool m_DownAttack;
	//float m_Attack;


private:
	//스킬 쿨다운
	struct SkillCoolDownInfo
	{
		float	CoolDown;
		bool	CoolDownEnable;
	};

	std::vector<SkillCoolDownInfo> m_vecCoolDown;
	/*
		v[0] = Dash
		v[1] = Attack
		v[2] = DoubleAttack
		v[3] = Fire
	*/

	enum class EPlayerStates
	{
		Idle,
		Walk,
		Jump,
		DoubleJump,
		Fall,
		LandOn,
		Dash,
		Slash,
		DoubleSlash,
		UpSlash,
		DownSlash,
		FireBall,
		Charge,
		Enter,
		Stun,
		Death,
		Prostrate,
		ProstrateRise,
		WallSlide,
	};

	EPlayerStates m_CurState;
	EPlayerStates m_PrevState;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer2D* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	//플레이어 관련
	void MoveUp();
	void MoveDown();
	void Move();
	void Rotation();
	void RotationInv();

	void LeftMove();
	void RightMove();
	void Jump();
	void JumpEnd();
	void LandOff();
	void Fire();
	void FireEnd();
	void Dash();
	void DashEnd();
	void Attack();
	void AttackEnd();
	void Charge();

private:
	//애니메이션 이펙트 관련함수
	void DashEffectEnd();
	void DoubleJumpEffectEnd();
	void AttackEffectEnd();
	void FireEffectEnd();
	
private:
	void SetInputKey();
	void SetAnimation();
	void SetCurAnim(EPlayerStates State);

	void SetIdle();
	void CheckDir();
	void SetReverse(bool Enable);

private:
	void CollisionBegin(const CollisionResult& Result);
};

