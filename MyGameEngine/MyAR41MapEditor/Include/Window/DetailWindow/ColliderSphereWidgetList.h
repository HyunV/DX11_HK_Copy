#pragma once
#include "ComponentWidgetList.h"
class CColliderSphereWidgetList :
    public CComponentWidgetList
{
    friend class CEditorWindow;

    template <typename T>
    friend class CEditorTreeItem;

protected:
    CColliderSphereWidgetList();
    ~CColliderSphereWidgetList();
};

