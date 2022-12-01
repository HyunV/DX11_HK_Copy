#pragma once
#include "ObjectComponent.h"

class CGravityAgent :
	public CObjectComponent
{
	friend class CGameObject;
	friend class CScene;

protected:
	CGravityAgent();
	CGravityAgent(const CGravityAgent& Obj);
	virtual ~CGravityAgent();

private:
	CSharedPtr<class CSceneComponent> m_UpdateComponent; //중력 적용할 컴포넌트 (오브젝트는 플레이어랑 몬스터만 쓸듯)

	CSharedPtr<class CCollider2D> m_Body; //벽과 부딫히는 콜라이더
	CSharedPtr<class CCollider2D> m_Wall; //현재 씬에서 충돌할 Box 콜라이더를 받음
	
	//=====================
	Vector2     m_Pos;	// 물체의 현재 좌표
	Vector2     m_PrevPos;// 물체의 이전 좌표
	Vector2     m_Move;	//m_Pos - m_PrevPos 뺀 이동벡터

	Vector2     m_BodySize;// 떨어지는 물체의 Size;
	Box2DInfo	m_BodyInfo;  //떨어지는 물체의 LTRB좌표

	Vector2		m_WallSize; // 벽 Size
	Box2DInfo	m_WallInfo; //벽 LTRB좌표
	//========================
public:
	//[중력 소스] 중력 관련 
	bool		m_PhysicsSimulate; //물리시뮬레이션 작동 시킬것인지 여부

	bool		m_Ground;	// 땅을 밟고 있는 상태인지 아닌지
	float		m_GravityAccel; //떨어지는 가속도
	float		m_FallTime; //물체가 떨어지는 시간(몇 초동안 떨어지냐)
	float		m_FallStartY; //어느 지점에서 y축으 로 떨어지고 있냐
	bool		m_Jump;		//점프 여부
	float		m_JumpVelocity; //점프 속도
	bool		m_SideWallCheck; //좌우 벽 체크 할 것인지의 여부		
	int			m_JumpCount; //점프 횟수

	bool		m_FallingStart; //물체가 떨어지기 시작할때 true
	bool		m_SideWallCollision;//벽 체크,

public:
	//[내비 소스]
	class CSceneComponent* GetUpdateComponent() const
	{
		return m_UpdateComponent;
	}

public:
	//[내비 소스]
	void SetUpdateComponent(class CSceneComponent* Component);

	//[중력 소스]
	void SetFallStartY(float y)
	{
		m_FallStartY = y;
	}

	void SetSideWallCheck(bool Check)
	{
		m_SideWallCheck = Check;
	}

	void SetPhysicsSimulate(bool Physics)
	{
		m_PhysicsSimulate = Physics;
	}

	void SetGravityAccel(float Accel)
	{
		m_GravityAccel = Accel;
	}

	void SetJumpVelocity(float JumpVelocity)
	{
		m_JumpVelocity = JumpVelocity;
	}
	void SetFallTime(float FallTime)
	{
		m_FallTime = FallTime;
	}

	bool GetJump()
	{
		return m_Jump;
	}

	bool GetFalling()
	{
		return m_FallingStart;
	}

	bool GetSideWallCheck()
	{
		return m_SideWallCollision;
	}
	void SetPosY(float PosY)
	{
		m_Pos = PosY;
		m_PrevPos = PosY;
	}

public:
	//플레이어 점프
	void Jump()
	{
		if (m_JumpCount == 2)
			return;
			
		else if (m_JumpCount == 1)
		{
			SetJumpVelocity(60.f);
			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;
			
		}

		++m_JumpCount;

		if (!m_Jump)
		{
			SetJumpVelocity(80.f);
			m_Jump = true;
			m_Ground = false;
			m_PhysicsSimulate = true;

			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;		
		}
	}

	//플레이어 점프
	void MiniJump()
	{
		SetJumpVelocity(40.f);
		m_JumpCount = 1;
		m_FallTime = 0.f;
		m_FallStartY = m_Pos.y;
	}

	void ObjectJump()
	{
		m_Jump = true;
		m_Ground = false;
		m_PhysicsSimulate = true;

		m_FallTime = 0.f;
		m_FallStartY = m_Pos.y;
	}

	//강제로 추락
	void FallingStartOn(float PosY)
	{
		m_FallingStart = true;
		m_FallStartY = PosY;
		m_JumpVelocity = 0.f;
	}

private:
	void CheckMoveRight();
	void CheckMoveLeft();

public:
	virtual void Destroy();
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CGravityAgent* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

