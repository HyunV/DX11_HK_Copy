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
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSceneComponent>	m_RightChild;
	CSharedPtr<class CSpriteComponent>	m_SpriteChild;
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>	m_Arm;
	//CSharedPtr<class CColliderOBB2D>	m_Body;
	CSharedPtr<class CColliderBox2D> m_Body;
	CSharedPtr<class CGravityAgent> m_GravityAgent;
	CSharedPtr<class CAnimation2D> m_Anim;

	
private:
	bool m_Jumping;
	float m_TimeTest;
	
	Vector3 m_PrevPos;

private:
	//struct PlayerState 
	//{
	//	bool m_Idle;
	//	bool m_Walk;
	//	int m_Jump;
	//	bool m_Fall;
	//	bool m_Dash;
	//	int m_Slash;
	//	bool m_UpSlash;
	//	bool m_DownSlash;
	//	bool m_FireBall;
	//	bool m_Charge;
	//	bool m_Enter;
	//	bool m_Stun;
	//	bool m_Death;
	//	bool m_Prostrate;
	//	bool m_ProstrateRise;
	//};

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
	void MoveUp();
	void MoveDown();
	void Rotation();
	void RotationInv();
	void LeftMove();
	void RightMove();
	void Jump();
	void JumpEnd();
	void LandOff();
	void Fire();
	void Dash();

	
private:
	void SetInputKey();
	void SetAnimation();
	void SetCurAnim(EPlayerStates State);

	void SetIdle();


private:
	void CollisionBegin(const CollisionResult& Result);
};

