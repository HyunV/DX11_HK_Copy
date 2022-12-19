#pragma once
#include "GameObject\GameObject.h"
class CCrawler :
    public CGameObject
{
	friend class CScene;

protected:
	CCrawler();
	CCrawler(const CCrawler& Obj);
	virtual ~CCrawler();

private:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CGravityAgent> m_GravityAgent; //�߷� ������Ʈ
	CSharedPtr<class CAnimation2D> m_Anim; //�ִϸ��̼�

	enum class EMonsterState
	{
		Fall,
		Walk,
		TurnOn,
		Death,
	};

	EMonsterState m_CurState; //���� ����
	EMonsterState m_PrevState;//���� ����

	float m_Dir;

	float m_Time; //�ൿ ��ȭ Ȯ�� �� ����(��� �� ���߰� 200���� ����)
	float m_MaterialChangeTime; //�ǰݽ� �� ���ϴ� �ð�

	float m_Accel;

private:
	int m_HP;

private:
	void SpriteAnimationSetting();
	void SetAnimation(); //�ִϸ��̼� ������, ���
	void SetCurAnim(EMonsterState State); //�ִϸ��̼�, ����, �ð� ���� �Լ�
	

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CCrawler* Clone()    const;

public:
	void ChangeDir(); //�ִϸ��̼� ������ȯ end�Լ�
	void CheckDir(); //���� ���� �Լ�
	void CreateGio(); //����� �� �����ϴ� �Լ�

private:
	void CollisionBegin(const CollisionResult& Result);
};

