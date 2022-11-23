#pragma once
#include "SpriteComponent.h"
class CMapComponent :
    public CSpriteComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CMapComponent();
    CMapComponent(const CMapComponent& component);
    virtual ~CMapComponent();
};

