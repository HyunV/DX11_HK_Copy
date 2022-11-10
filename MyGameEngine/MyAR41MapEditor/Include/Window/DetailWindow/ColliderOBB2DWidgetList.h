#pragma once
#include "ComponentWidgetList.h"
class CColliderOBB2DWidgetList :
    public CComponentWidgetList
{
    friend class CEditorWindow;

    template <typename T>
    friend class CEditorTreeItem;

protected:
    CColliderOBB2DWidgetList();
    ~CColliderOBB2DWidgetList();
};

