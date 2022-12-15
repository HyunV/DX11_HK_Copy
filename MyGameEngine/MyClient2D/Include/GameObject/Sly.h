#pragma once
#include "GameObject\GameObject.h"
class CSly :
    public CGameObject
{
    friend class CScene;

protected:
    CSly();
    CSly(const CSly& Obj);
    virtual ~CSly();

protected:
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CColliderBox2D>	m_Body;
    CSharedPtr<class CSpriteComponent>	m_HearBox;

    bool m_CollisionCheck;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CSly* Clone()    const;

private:
    void NPCUpKey();
    void CheckDir(float x);
    void CollisionBegin(const CollisionResult& Result);
    void CollisionEnd(const CollisionResult& Result);
};

