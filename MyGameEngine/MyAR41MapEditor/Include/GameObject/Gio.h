#pragma once
#include "GameObject\GameObject.h"
class CGio :
    public CGameObject
{
    friend class CScene;

protected:
    CGio();
    CGio(const CGio& Obj);
    virtual ~CGio();

private:
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CColliderBox2D>	m_Body;
    CSharedPtr<class CGravityAgent> m_Gravity;

    bool m_Jump;
    float m_Dir;
    float m_Range;
    float m_Time;
public:
    CGravityAgent* GetGravity()
    {
        return m_Gravity;
    }

    void SetDir(float Dir)
    {
        m_Dir = Dir;
    }

    void SetRange(float Range)
    {
        m_Range = Range;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CGio* Clone() const;

public:
    void CollisionCoin(const CollisionResult& result);
};

