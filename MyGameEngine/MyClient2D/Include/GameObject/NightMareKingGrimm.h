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
	CSharedPtr<class CGravityAgent> m_GravityAgent; //중력 컴포넌트
	CSharedPtr<class CAnimation2D> m_Anim; //애니메이션

	enum class EBossState {
		Idle, //위치 고정, 불기둥 패턴(4)
		TeleIn,// 나타남
		TeleOut, //사라짐
		AirDashDown,
		AirDashStart, //위치 조건부 고정, 에어대시(3)
		AirDashFall,
		GroundDashStart,
		GroundDashing,
		FireBat,//위치 고정, 파이어뱃 패턴 (2)
		FireBatEnd,
		SlashStart, //플레이어 고정, 슬래시 패턴(1)
		Slash,
		Uppercut,
		UppercutEnd,
		BallonAnticOn, //무적, 쿨 30초, 풍선패턴(6)
		BallonOn,
		BallonEndOn,
		SpikeStart, //은신, 스파이크 객체 
		Death
	};

	EBossState m_CurState; //현재 상태
	EBossState m_PrevState;//이전 상태
	EBossState m_NextState;

	int m_HP;

	//방향
	float m_Dir;
	std::string m_strDir;

	float m_Time;
	float m_MaterialChangeTime; //피격시 색 변하는 시간

	float m_SkillUseTime;
	bool m_NextSkillDelay;

	//파이어뱃 관련 변수
	int m_FireBatCount;
	float m_FireBatDelay;

	//불기둥 관련 변수
	bool m_FirePillarStart;
	int m_FirePillarCount;

	//스파이크 관련
	bool m_SpikeStart;
	bool m_Spiking;
	bool m_SpikeEnd;

	//풍선 관련
	float m_BalloonCool;
	int m_FireBallCount;

	//사망
	bool m_Death;

private:
	void SetSounds();
	void SetAnimation(); //애니메이션 스케일, 펑션
	void SetCurAnim(EBossState State); //애니메이션, 사운드, 시간 세팅 함수

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CNightMareKingGrimm* Clone()    const;

private:
	//방향 세팅 관련 함수
	//void CheckDir(); 
	//void ChangeDir();
	void SetDir(std::string LeftRight);
	
	//모션들
private:
	void SetNextPattern(); //난수돌리고 다음 패턴 세팅
	void NextPatternStart();//다음 패턴 시작
	void TeleportIn(); //텔포 나타나기
	void TeleportOut(); //텔포 사라지기
	void FireBatEnd(); //박쥐패턴 끝(노티파이)
	void Slash();
	void AirDashStart();
	void FallStart();
	void BalloonAnticEnd();
private:
	//탄 생성
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

