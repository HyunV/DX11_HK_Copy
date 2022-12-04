#pragma once
#include "GameObject\GameObject.h"
class CBackLayerObject :
    public CGameObject
{

public:
	CBackLayerObject();
	CBackLayerObject(const CBackLayerObject& Obj);
	virtual ~CBackLayerObject();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBackLayerObject* Clone()    const;
};

