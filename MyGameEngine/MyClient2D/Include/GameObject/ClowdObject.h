#pragma once
#include "GameObject\GameObject.h"
class CClowdObject :
    public CGameObject
{
    friend class CScene;

protected:
	CClowdObject();
	CClowdObject(const CClowdObject& Obj);
	virtual ~CClowdObject();
public:
	CSharedPtr<class CSceneComponent> m_Component;
	CSharedPtr<class CSpriteComponent> m_Sprite[20];
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CClowdObject* Clone()    const;
};

