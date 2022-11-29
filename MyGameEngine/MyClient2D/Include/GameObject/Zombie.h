#pragma once
#include "GameObject\GameObject.h"
class CZombie :
    public CGameObject
{
	friend class CScene;

protected:
	CZombie();
	CZombie(const CZombie& Obj);
	virtual ~CZombie();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CColliderBox2D>	m_Sight;
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CGravityAgent> m_GravityAgent; //�߷� ������Ʈ
	CSharedPtr<class CAnimation2D> m_Anim; //�ִϸ��̼�

	//SightCollider
	struct SkillCoolDownInfo
	{
		float	CoolDown;
		bool	CoolDownEnable;
	};

	enum class EMonsterState {
		Idle,
		Walk,
		TurnOn,
		Attack,
		Attacking,
		Death
	};

	std::vector<SkillCoolDownInfo> m_vecCoolDown;
	EMonsterState m_CurState; //���� ����
	EMonsterState m_PrevState;//���� ����

	//����
	float m_Dir;
	float m_Angle;

	//
	float m_Time;

	float MaterialChangeTime; //�ǰݽ� �� ���ϴ� �ð�

public:
	//ü��
	int m_HP;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CZombie* Clone()    const;
private:
	//��ǵ�
	void Attack();
private:
	void SetSounds();
	void SpriteAnimationSetting();
	void SetAnimation(); //�ִϸ��̼� ������, ���

	void CheckDir();
	void SetNextState();
	void SetCurAnim(EMonsterState State);

	void ChangeDir();

	void CreateGio();
private:
	void CollisionBegin(const CollisionResult& Result);
	void CollisionEnd(const CollisionResult& Result);
	void SightCollisionBegin(const CollisionResult& Result);
};

