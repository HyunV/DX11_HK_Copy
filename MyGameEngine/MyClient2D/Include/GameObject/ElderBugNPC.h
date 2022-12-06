#pragma once
#include "GameObject\GameObject.h"
class CElderBugNPC :
    public CGameObject
{
    friend class CScene;

protected:
    CElderBugNPC();
    CElderBugNPC(const CElderBugNPC& Obj);
    virtual ~CElderBugNPC();

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
    virtual CElderBugNPC* Clone()    const;

private:
    void NPCUpKey();
    void CheckDir(float x);
    void CollisionBegin(const CollisionResult& Result);
    void CollisionEnd(const CollisionResult& Result);
};

