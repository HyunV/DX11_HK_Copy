#pragma once
#include "GameObject\GameObject.h"
class CFlameParticle :
    public CGameObject
{
public:
    CFlameParticle();
    CFlameParticle(const CFlameParticle& Obj);
    virtual ~CFlameParticle();

private:
    
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CColliderSphere2D>	m_Body;

    float m_Angle;
    float m_Speed;
    float m_Dir;

    bool m_FallFlame;
    bool m_MineFlame;

    bool m_flick;
    bool m_Opacity;

public:
    void EnableCollider(bool Enable);
    void SetSpeed(float Speed)
    {
        m_Speed = Speed;
    }
    void EnableFallFlame()
    {
        m_FallFlame = true;
    }
    void EnableMineFlame()
    {
        m_MineFlame = true;
    }
    void SetDir(float dir)
    {
        m_Dir = dir;
    }

    void SetFlick(bool Enable);

    void SetOpacity(float opacity);
    void SetDepthDisable();
    void SetBoxSize(float x, float y);
    void SetImageSize(float x, float y);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CFlameParticle* Clone() const;

private:
    void CollisionBullet(const CollisionResult& result);

};

