#pragma once
#include "GameObject\GameObject.h"
class CFlameFall :
    public CGameObject
{
    friend class CScene;
    friend class CNigthMareKingGrimm;

protected:
	CFlameFall();
	CFlameFall(const CFlameFall& Obj);
	virtual ~CFlameFall();

private:
	CSharedPtr<class CSceneComponent> m_Main;
};

