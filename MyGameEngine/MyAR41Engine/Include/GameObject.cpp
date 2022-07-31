#include "GameObject.h"

CGameObject::CGameObject()
{
}

CGameObject::CGameObject(const CGameObject& Obj)	:
	CRef(Obj)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Start()
{
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
}

void CGameObject::PostUpdate(float DeltaTime)
{
}

CGameObject* CGameObject::Clone() const
{
	return new CGameObject(*this);
}
