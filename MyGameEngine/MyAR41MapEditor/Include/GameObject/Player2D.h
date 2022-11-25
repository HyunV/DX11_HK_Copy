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
	CSharedPtr<class CColliderBox2D> m_Body; //��Ʈ
	CSharedPtr<class CSpriteComponent>	m_Sprite; //�ִϸ��̼�

	CSharedPtr<class CCameraComponent>	m_Camera; //�ޱ� ���� ���� �ø���
	CSharedPtr<class CTargetArm>	m_Arm;

	//����Ʈ ��������Ʈ
	CSharedPtr<class CSpriteComponent> m_DashSprite; // ��
	CSharedPtr<class CSpriteComponent> m_DoubleJumpSprite; //��
	CSharedPtr<class CSpriteComponent> m_AttackSprite; //��
	CSharedPtr<class CSpriteComponent> m_FireSprite; //��
	//��������, ���, 

	CSharedPtr<class CGravityAgent> m_GravityAgent; //�߷� ������Ʈ
	
	CSharedPtr<class CAnimation2D> m_Anim; //�ִϸ��̼�
	
private:
	//�̵�����
	Vector3 m_PrevPos; //Move �� �Ǻ��ϱ� ���� prevPos

	//��������
	int m_Jumping; //��������, Ƚ��
	
	//���
	float m_DashEndPos; //����Ҷ� �������� �̵��ϴ� ����
	int m_DashCount; //���ߴ�ô� 1���� ����
	bool m_KeyLock; //��� �� Ű ���

	//�̵����� ����
	float m_Dir; //Left�� -1, Right�� 1
	float m_Angle; //Left�� 180, Right�� 0;
	
	//���ݰ���
	float m_DoubleAttack;
	bool m_UpAttack;
	bool m_DownAttack;
	//float m_Attack;


private:
	//��ų ��ٿ�
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
	//�÷��̾� ����
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
	//�ִϸ��̼� ����Ʈ �����Լ�
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

