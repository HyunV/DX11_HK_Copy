#pragma once
#include "Editor\EditorWindow.h"
#include "Editor/EditorTree.h"
#include "GameObject/GameObject.h"

//오브젝트 생성 클래스?
class CObjectWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CObjectWindow();
    virtual ~CObjectWindow();

private:
    CEditorTree<CGameObject*>* m_Tree;
    CSharedPtr<CGameObject> m_SelectObject;
    class CEditorInput* m_SelectObjectInput;

public:
    class CGameObject* GetSelectObject() const
    {
        return m_SelectObject;
    }

public:
    bool AddItem(class CGameObject* Object, const std::string& Name, const std::string& ParentName = "Root");

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void TreeCallback(CEditorTreeItem<CGameObject*>* Node, const std::string& Item);
    void DeleteButtonCallback();
};

