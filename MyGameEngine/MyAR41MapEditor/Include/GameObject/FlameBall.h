#pragma once
#include "GameObject\GameObject.h"
class CFlameBall :
    public CGameObject
{
    friend class CScene;

protected:
    CFlameBall();
    CFlameBall(const CFlameBall& Obj);
    virtual ~CFlameBall();

    CSharedPtr<class CColliderSphere2D> m_Body;
    CSharedPtr<class CSpriteComponent> m_Sprite;

    Vector2 m_Speed;
    float m_Dir;
    float m_Height;
    EFireBallDirection m_BallDir;

public:
    void SetTextureReverse(bool Enable);
    
    void SetDirection(float Dir)
    {
        m_Dir = Dir;
    }
    void SetBallDir(EFireBallDirection BallDir)
    {
        m_BallDir = BallDir;
    }
    void SetHeight(float Height)
    {
        m_Height = Height;
    }
    float GetHeight()
    {
        return m_Height;
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

