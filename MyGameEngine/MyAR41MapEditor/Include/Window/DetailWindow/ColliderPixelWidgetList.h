#pragma once
#include "ComponentWidgetList.h"
class CColliderPixelWidgetList :
    public CComponentWidgetList
{
    friend class CEditorWindow;

    template <typename T>
    friend class CEditorTreeItem;

protected:
    CColliderPixelWidgetList();
    ~CColliderPixelWidgetList();
};

