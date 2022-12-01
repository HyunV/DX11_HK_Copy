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

	CSharedPtr<class CCollider2D> m_Body; //���� �΋H���� �ݶ��̴�
	CSharedPtr<class CCollider2D> m_Wall; //���� ������ �浹�� Box �ݶ��̴��� ����
	
	//=====================
	Vector2     m_Pos;	// ��ü�� ���� ��ǥ
	Vector2     m_PrevPos;// ��ü�� ���� ��ǥ
	Vector2     m_Move;	//m_Pos - m_PrevPos �� �̵�����

	Vector2     m_BodySize;// �������� ��ü�� Size;
	Box2DInfo	m_BodyInfo;  //�������� ��ü�� LTRB��ǥ

	Vector2		m_WallSize; // �� Size
	Box2DInfo	m_WallInfo; //�� LTRB��ǥ
	//========================
public:
	//[�߷� �ҽ�] �߷� ���� 
	bool		m_PhysicsSimulate; //�����ùķ��̼� �۵� ��ų������ ����

	bool		m_Ground;	// ���� ��� �ִ� �������� �ƴ���
	float		m_GravityAccel; //�������� ���ӵ�
	float		m_FallTime; //��ü�� �������� �ð�(�� �ʵ��� ��������)
	float		m_FallStartY; //��� �������� y���� �� �������� �ֳ�
	bool		m_Jump;		//���� ����
	float		m_JumpVelocity; //���� �ӵ�
	bool		m_SideWallCheck; //�¿� �� üũ �� �������� ����		
	int			m_JumpCount; //���� Ƚ��

	bool		m_FallingStart; //��ü�� �������� �����Ҷ� true
	bool		m_SideWallCollision;//�� üũ,

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
	//�÷��̾� ����
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

	//�÷��̾� ����
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

	//������ �߶�
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

