#pragma once
#include "GameObject\GameObject.h"
class CGrimmSmoke :
    public CGameObject
{
    friend class CScene;

protected:
    CGrimmSmoke();
    CGrimmSmoke(const CGrimmSmoke& Obj);
    virtual ~CGrimmSmoke();

public:
    CSharedPtr<class CSpriteComponent>	m_Sprite;

    float m_Opacity;
    bool m_OpaReverse;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CGrimmSmoke* Clone()    const;
};

