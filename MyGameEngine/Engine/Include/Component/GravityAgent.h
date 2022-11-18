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

	CSharedPtr<class CCollider2D> m_Wall; //현재 씬에서 충돌할 Box 콜라이더를 받음
	CSharedPtr<class CCollider2D> m_Body; //벽과 부딫히는 콜라이더

	//=====================
	Vector2     m_Pos;
	Vector2     m_PrevPos;
	Vector2     m_Move;
	Vector2     m_BodySize;// 충돌체의 Size;
	Vector2     m_BodyPivot;// 충돌체의 Pivot;
	//========================

	//[중력 소스] 중력 관련 
	bool		m_PhysicsSimulate; //물리시뮬레이션 작동 시킬것인지 여부
	bool		m_Ground;	// 땅을 밟고 있는 상태인지 아닌지
	float		m_GravityAccel;
	float		m_FallTime; //물체가 떨어지는 시간(몇 초동안 떨어지냐)
	float		m_FallStartY; //어느 지점에서 y축으 로 떨어지고 있냐
	bool		m_Jump;
	float		m_JumpVelocity; //점프 속도
	bool		m_SideWallCheck;
	bool		m_Start;
	int			m_JumpCount;

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

public:
	void Jump()
	{
		if (!m_Jump)
		{
			m_Jump = true;
			m_Ground = false;
			m_PhysicsSimulate = true;

			m_FallTime = 0.f;
			m_FallStartY = m_UpdateComponent->GetWorldPos().y;
		}
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

