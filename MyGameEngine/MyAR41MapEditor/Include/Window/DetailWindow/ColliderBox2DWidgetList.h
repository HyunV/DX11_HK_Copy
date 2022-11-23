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

    class CColliderBox2D* m_Collider;
    
    class CEditorText* m_Name;
    class CEditorComboBox* m_Combo;
    class CEditorInput* m_InputX;
    class CEditorInput* m_InputY;
    class CEditorInput* m_ComponentName;
    //¹öÆ°

public:
    void SetColliderBox2D(class CColliderBox2D* ColliderComponent);

public:
    virtual bool Init();

private:
    void ColliderSettingClick();

    //void ComboBoxCallback(int SelectIndex, const std::string& Item);
};

