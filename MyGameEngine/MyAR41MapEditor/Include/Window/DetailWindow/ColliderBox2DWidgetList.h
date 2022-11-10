#pragma once
#include "ComponentWidgetList.h"
class CColliderBox2DWidgetList :
    public CComponentWidgetList
{
    friend class CEditorWindow;

    template <typename T>
    friend class CEditorTreeItem;

protected:
    CColliderBox2DWidgetList();
    ~CColliderBox2DWidgetList();
};

