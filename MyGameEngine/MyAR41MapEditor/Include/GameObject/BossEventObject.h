#pragma once
#include "GameObject\GameObject.h"
class CBossEventObject :
    public CGameObject
{
	friend class CScene;

protected:
	CBossEventObject();
	CBossEventObject(const CBossEventObject& Obj);
	virtual ~CBossEventObject();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CSpriteComponent>	m_GrimmSprite;
	CSharedPtr<class CColliderBox2D> m_Body;

	bool m_EventStart;
	enum class EEventState
	{
		None,
		Event1,
		Event2,
		Event3,
		Finish
	};

	EEventState m_CurEvent;
	float m_Time;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBossEventObject* Clone()    const;
private:
	void CollisionBegin(const CollisionResult& Result);
	void CreateFireEffect(float z);
};

