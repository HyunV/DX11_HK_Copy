#pragma once
#include "ComponentWidgetList.h"
class CColliderWidgetList :
    public CComponentWidgetList
{
    friend class CEditorWindow;

    template <typename T>
    friend class CEditorTreeItem;

protected:
    CColliderWidgetList();
    ~CColliderWidgetList();

public:
    class CCollider2D* m_Collider;
    ECollider2D_Type        m_Collider2DType;

public:
    void SetColliderContent(class CCollider2D* Collider2D);
public:
    virtual bool Init();

private:
    void SetConfirmButtonCallback();
    //콤보박스로 프로파일 지정
};

