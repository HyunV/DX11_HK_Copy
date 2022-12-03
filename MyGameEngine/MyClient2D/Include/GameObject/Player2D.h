#pragma once

#include "GameObject/GameObject.h"

class CPlayer2D :
	public CGameObject
{
	friend class CScene;
	friend class CPlayerHUD;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& Obj);
	virtual ~CPlayer2D();

private:
	//플레이어 행동모션
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
		DeathEnd,
		Prostrate,
		ProstrateRise,
		WallSlide,
		DashEndGround,
	};

	//스킬 쿨다운
	struct SkillCoolDownInfo
	{
		float	CoolDown;
		bool	CoolDownEnable;
	};


	CSharedPtr<class CColliderBox2D> m_Body; //루트
	CSharedPtr<class CSpriteComponent>	m_Sprite; //애니메이션

	CSharedPtr<class CCameraComponent>	m_Camera; //앵글 위로 좀만 올리기
	CSharedPtr<class CTargetArm>	m_Arm;

	//이펙트 스프라이트
	CSharedPtr<class CSpriteComponent> m_DashSprite; // 뒤
	CSharedPtr<class CSpriteComponent> m_DoubleJumpSprite; //뒤
	CSharedPtr<class CSpriteComponent> m_AttackSprite; //앞
	CSharedPtr<class CSpriteComponent> m_UpAttackSprite; //앞
	CSharedPtr<class CSpriteComponent> m_DownAttackSprite;//앞
	CSharedPtr<class CSpriteComponent> m_FireSprite; //앞
	CSharedPtr<class CSpriteComponent> m_ChargeSprite; //앞
	//더블점프, 대시, 

	CSharedPtr<class CGravityAgent> m_GravityAgent; //중력 컴포넌트
	
	class CAnimation2D* m_Anim; //애니메이션

public:
	int m_HP;
	int m_MaxHP;
	int m_Gio;

public:
	//이동관련
	Vector3 m_PrevPos; //Move 값 판별하기 위한 prevPos
	bool m_UpKey;
	bool m_DownKey;

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
	
	//충전 관련
	bool m_ChargeStart;
	float m_ChargingTime; //체력회복할때 쓰는 계수

	//무적 관련
	bool m_InfiniteMod;
	bool m_Opacity;
	float m_InfiniteTime;
	bool m_flick; //깜빡이

	//문 이동 관련
	bool m_CollisionDoor;
	class CDoor* m_Doorptr;
	std::string m_DoorName;

	struct AdvanceSkill
	{
		bool AdvAttack;
		bool AdvFire;
		bool AdvDash;
		bool AdvHP;
	};

	bool m_Prostrate;

	bool m_Advance; //스킬강화(임시)
public:
	bool GetDownAttackEnable()
	{
		return m_DownAttack;
	}
	void SetDownAttackEnable(bool Enable)
	{
		m_DownAttack = Enable;
	}
	 CGravityAgent* GetGravityAgent()
	{
		 return m_GravityAgent;
	}
	 void ResetDoubleJumping()
	 {
		 m_Jumping = 1;
	 }
	 void AddGio(int Count)
	 {
		 m_Gio += Count;
	 }
	 void SetProstrate();
	 void CheckProstrate();
	 void ProstrateEnd();

private:
	std::vector<SkillCoolDownInfo> m_vecCoolDown;
	/*
		v[0] = Dash
		v[1] = Attack
		v[2] = DoubleAttack
		v[3] = Fire
	*/
	EPlayerStates m_CurState; //현재 상태
	EPlayerStates m_PrevState;//이전 상태

private:
	void SetInputKey();
	void SetAnimation();
	void SetSounds();
	void SpriteAnimationSetting();
	void SetCurAnim(EPlayerStates State);

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
	void UpKey();
	void DownKey();
	void UpKeyUp(); //뗄 때
	void DownKeyUp();//뗄 때

	void Move();
	void LeftMove();
	void RightMove();
	void Jump();
	void Fire();
	void Dash();
	void DashEnd();
	void Attack();
	void Charge();
	void Charging();
	void ChargeOff();

	void Death();
	void DeathEnd();

	void EnterRoomStart();
	void EnterRoomEnd();
	//임시테스트
	void Q();
	void InfiniteMod(float Time = 1.f, bool flick = true);

private:
	//애니메이션 이펙트 관련함수
	void DashEffectEnd();
	void DoubleJumpEffectEnd();
	void AttackEffectEnd();
	void FireEffectEnd();

	void CheckDir(); //방향 판단 함수
	void SetReverse(bool Enable); //멤버들 반전여부
	void SetNextState(); //다음 모션 판단 함수
	void SetAttackMotion(EPlayerStates State); //공격 이펙트 함수

	void CreateHitCollider(EPlayerStates State);
	void CreateChargeEffect();
private:
	void CollisionBegin(const CollisionResult& Result);
	void CollisionEnd(const CollisionResult& Result);
};

