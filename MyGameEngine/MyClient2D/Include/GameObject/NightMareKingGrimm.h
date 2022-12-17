#pragma once
#include "GameObject\GameObject.h"
class CNightMareKingGrimm :
    public CGameObject
{
    friend class CScene;

protected:
	CNightMareKingGrimm();
	CNightMareKingGrimm(const CNightMareKingGrimm& Obj);
	virtual ~CNightMareKingGrimm();

private:
	CSharedPtr<class CSceneComponent> m_Main;
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CGravityAgent> m_GravityAgent; //�߷� ������Ʈ
	CSharedPtr<class CAnimation2D> m_Anim; //�ִϸ��̼�

	enum class EBossState {
		Idle, //��ġ ����, �ұ�� ����(4)
		TeleIn,// ��Ÿ��
		TeleOut, //�����
		AirDashDown,
		AirDashStart, //��ġ ���Ǻ� ����, ������(3)
		AirDashFall,
		GroundDashStart,
		GroundDashing,
		FireBat,//��ġ ����, ���̾�� ���� (2)
		FireBatEnd,
		SlashStart, //�÷��̾� ����, ������ ����(1)
		Slash,
		Uppercut,
		UppercutEnd,
		BallonAnticOn, //����, �� 30��, ǳ������(6)
		BallonOn,
		BallonEndOn,
		SpikeStart, //����, ������ũ ��ü 
		Death
	};

	EBossState m_CurState; //���� ����
	EBossState m_PrevState;//���� ����
	EBossState m_NextState;

	int m_HP;

	//����
	float m_Dir;
	std::string m_strDir;

	float m_Time;
	float m_MaterialChangeTime; //�ǰݽ� �� ���ϴ� �ð�

	float m_SkillUseTime;
	bool m_NextSkillDelay;

	//���̾�� ���� ����
	int m_FireBatCount;
	float m_FireBatDelay;

	//�ұ�� ���� ����
	bool m_FirePillarStart;
	int m_FirePillarCount;

	//������ũ ����
	bool m_SpikeStart;
	bool m_Spiking;
	bool m_SpikeEnd;

	//ǳ�� ����
	float m_BalloonCool;
	int m_FireBallCount;

	//���
	bool m_Death;

private:
	void SetSounds();
	void SetAnimation(); //�ִϸ��̼� ������, ���
	void SetCurAnim(EBossState State); //�ִϸ��̼�, ����, �ð� ���� �Լ�

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNightMareKingGrimm* Clone()    const;

private:
	//���� ���� ���� �Լ�
	//void CheckDir(); 
	//void ChangeDir();
	void SetDir(std::string LeftRight);
	
	//��ǵ�
private:
	void SetNextPattern(); //���������� ���� ���� ����
	void NextPatternStart();//���� ���� ����
	void TeleportIn(); //���� ��Ÿ����
	void TeleportOut(); //���� �������
	void FireBatEnd(); //�������� ��(��Ƽ����)
	void Slash();
	void AirDashStart();
	void FallStart();
	void BalloonAnticEnd();
private:
	//ź ����
	void CreateFireBat(int count, float Dir);
	void CreateFlame();
	void CreateAfterFlame(float x, float y);
	void CreateFirePillar();
	void CreateSpike();
	void CreateFlameBall();

public:
	bool GetDeath()
	{
		return m_Death;
	}
private:
	void CollisionBegin(const CollisionResult& Result);
};

