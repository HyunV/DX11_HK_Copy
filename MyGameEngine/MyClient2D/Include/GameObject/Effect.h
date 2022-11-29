#pragma once
#include "GameObject\GameObject.h"
class CEffect :
    //이펙트 출력용 오브젝트
    public CGameObject
{
    friend class CScene;

protected:
    CEffect();
    CEffect(const CEffect& Obj);
    virtual ~CEffect();

public:
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual CEffect* Clone()    const;

public:
    void SetCurAnimation(std::string& AnimationName, float PlayScale = 1.f);
};

