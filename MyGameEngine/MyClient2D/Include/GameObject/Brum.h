#pragma once
#include "GameObject\GameObject.h"
class CBrum :
    public CGameObject
{
    friend class CScene;

protected:
    CBrum();
    CBrum(const CBrum& Obj);
    virtual ~CBrum();

protected:
    CSharedPtr<class CColliderBox2D>	m_Body;
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CSpriteComponent>	m_HearBox;
private:
    bool m_Check;
    bool m_CollisionCheck;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBrum* Clone()    const;

private:
    void NPCUpKey();
    void CollisionBegin(const CollisionResult& Result);
    void CollisionEnd(const CollisionResult& Result);
};

