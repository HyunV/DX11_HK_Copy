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
	//�÷��̾� �ൿ���
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
		LookUp,
		RoarLock
	};

	//��ų ��ٿ�
	struct SkillCoolDownInfo
	{
		float	CoolDown;
		bool	CoolDownEnable;
	};


	CSharedPtr<class CColliderBox2D> m_Body; //��Ʈ
	CSharedPtr<class CSpriteComponent>	m_Sprite; //�ִϸ��̼�

	CSharedPtr<class CCameraComponent>	m_Camera; //�ޱ� ���� ���� �ø���
	CSharedPtr<class CTargetArm>	m_Arm;

	//����Ʈ ��������Ʈ
	CSharedPtr<class CSpriteComponent> m_DashSprite; // ��
	CSharedPtr<class CSpriteComponent> m_DoubleJumpSprite; //��
	CSharedPtr<class CSpriteComponent> m_AttackSprite; //��
	CSharedPtr<class CSpriteComponent> m_UpAttackSprite; //��
	CSharedPtr<class CSpriteComponent> m_DownAttackSprite;//��
	CSharedPtr<class CSpriteComponent> m_FireSprite; //��
	CSharedPtr<class CSpriteComponent> m_ChargeSprite; //��
	//��������, ���, 

	CSharedPtr<class CGravityAgent> m_GravityAgent; //�߷� ������Ʈ
	
	class CAnimation2D* m_Anim; //�ִϸ��̼�

public:
	PlayerInfo m_PlayerInfo;
	bool m_Advance;

public:
	//�̵�����
	Vector3 m_PrevPos; //Move �� �Ǻ��ϱ� ���� prevPos
	bool m_UpKey;
	bool m_DownKey;

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
	
	//���� ����
	bool m_ChargeStart;
	float m_ChargingTime; //ü��ȸ���Ҷ� ���� ���

	//���� ����
	bool m_InfiniteMod;
	bool m_Opacity;
	float m_InfiniteTime;
	bool m_flick; //������

	//�� �̵� ����
	bool m_CollisionDoor;
	class CDoor* m_Doorptr;
	std::string m_DoorName;

	bool m_Prostrate;

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
		 m_PlayerInfo.Gio += Count;
	 }
	 void SetProstrate();
	 void CheckProstrate();

private:
	std::vector<SkillCoolDownInfo> m_vecCoolDown;
	/*
		v[0] = Dash
		v[1] = Attack
		v[2] = DoubleAttack
		v[3] = Fire
	*/
	EPlayerStates m_CurState; //���� ����
	EPlayerStates m_PrevState;//���� ����

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

public:
	//�÷��̾� ����
	void UpKey();
	void DownKey();
	void UpKeyUp(); //�� ��
	void DownKeyUp();//�� ��

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
	

	//�ӽ��׽�Ʈ
	void Q();
	void InfiniteMod(float Time = 1.f, bool flick = true);
public:
	void ContactNPC(float posX);
	void PurchaseItem(int count);
	bool m_UsingGio;
	int m_UsedGio;
	void UpgradeMaxHeart();


public:
	//�ִϸ��̼� ����Ʈ �����Լ�
	void DashEffectEnd();
	void DoubleJumpEffectEnd();
	void AttackEffectEnd();
	void FireEffectEnd();

	void CheckDir(); //���� �Ǵ� �Լ�
	void SetReverse(bool Enable); //����� ��������
	bool GetReverse();
	
	//���� ����
	bool WallCheck(); //�÷��̾� ��ġ���� +-500�� ���� �ִ��� üũ
	int CheckPos(); //�÷��̾� ��, �� ��� �� ������� üũ
public:
	void SetNextState(); //���� ��� �Ǵ� �Լ�
private:
	void SetAttackMotion(EPlayerStates State); //���� ����Ʈ �Լ�

	void CreateHitCollider(EPlayerStates State);
	void CreateChargeEffect();

public:
	void importToGameManager();
	void ReturnToTown();
	void CameraCheck();
	void ResetCamera();

	void MoveCamera();
	bool m_CameraMove;

private:
	void CollisionBegin(const CollisionResult& Result);
	void CollisionEnd(const CollisionResult& Result);
};

