#pragma once
#include "GameObject\GameObject.h"
class CFirePillarBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CFirePillarBullet();
    CFirePillarBullet(const CFirePillarBullet& Obj);
    virtual ~CFirePillarBullet();

    CSharedPtr<class CColliderBox2D> m_Body;
    CSharedPtr<class CSpriteComponent> m_Sprite;


    bool m_flick;
    bool m_Opacity;
    float m_Time;
    bool m_FireStart;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

