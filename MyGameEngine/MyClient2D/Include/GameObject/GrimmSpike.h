#pragma once
#include "GameObject\GameObject.h"
class CGrimmSpike :
    public CGameObject
{
    friend class CScene;

protected:
    CGrimmSpike();
    CGrimmSpike(const CGrimmSpike& Obj);
    virtual ~CGrimmSpike();

    CSharedPtr<class CColliderBox2D> m_Body;
    CSharedPtr<class CSpriteComponent> m_Sprite;
    class CAnimation2D* m_Anim;

    float m_Time;

    bool m_SpikeStart;
    bool m_Spiking;
    bool m_SpikeDown;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void SpikeEndFunc();
};

