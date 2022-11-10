#pragma once
#include "Editor\EditorWindow.h"

//컴포넌트 생성 클래스?
class CClassWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CClassWindow();
    virtual ~CClassWindow();

private:
    class CEditorListBox* m_ObjectList;
    class CEditorListBox* m_ComponentList;
    std::string         m_SelectObjectItem;
    std::string         m_SelectComponentItem;

    class CEditorInput* m_ObjectSelectName;
    class CEditorInput* m_ComponentSelectName;
    class CEditorInput* m_NumberingCount;

public:
    const std::string& GetSelectObjectItem() const
    {
        return m_SelectObjectItem;
    }
    
    const std::string& GetSelectComponentItem() const
    {
        return m_SelectComponentItem;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void ObjectClickCallback(int Index, const std::string& Item);
    void ComponentClickCallback(int Index, const std::string& Item);
    void ObjectCreateCallback();
    void ComponentCreateCallback();

private:
    void LoadGameObjectName();
    void LoadComponentName();

    //테스트
    void MakeObject();
};

