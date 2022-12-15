#pragma once
#include "GameObject\GameObject.h"
class CFireBatBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CFireBatBullet();
    CFireBatBullet(const CFireBatBullet& Obj);
    virtual ~CFireBatBullet();

    CSharedPtr<class CColliderBox2D> m_Body;
    CSharedPtr<class CSpriteComponent> m_Sprite;
    

    float m_Dir;

public:
    void SetDirection(float Dir);
    void SetTextureReverse(bool Enable);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
   
};

