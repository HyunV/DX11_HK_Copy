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
	CSharedPtr<class CSceneComponent> m_UpdateComponent; //�߷� ������ ������Ʈ (������Ʈ�� �÷��̾�� ���͸� ����)

	CSharedPtr<class CCollider2D> m_Wall; //���� ������ �浹�� Box �ݶ��̴��� ����
	CSharedPtr<class CCollider2D> m_Body; //���� �΋H���� �ݶ��̴�

	//=====================
	Vector2     m_Pos;
	Vector2     m_PrevPos;
	Vector2     m_Move;
	Vector2     m_BodySize;// �浹ü�� Size;
	Vector2     m_BodyPivot;// �浹ü�� Pivot;
	//========================

	//[�߷� �ҽ�] �߷� ���� 
	bool		m_PhysicsSimulate; //�����ùķ��̼� �۵� ��ų������ ����
	bool		m_Ground;	// ���� ��� �ִ� �������� �ƴ���
	float		m_GravityAccel;
	float		m_FallTime; //��ü�� �������� �ð�(�� �ʵ��� ��������)
	float		m_FallStartY; //��� �������� y���� �� �������� �ֳ�
	bool		m_Jump;
	float		m_JumpVelocity; //���� �ӵ�
	bool		m_SideWallCheck;
	bool		m_Start;
	int			m_JumpCount;

public:
	//[���� �ҽ�]
	class CSceneComponent* GetUpdateComponent() const
	{
		return m_UpdateComponent;
	}

public:
	//[���� �ҽ�]
	void SetUpdateComponent(class CSceneComponent* Component);

	//[�߷� �ҽ�]
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

