#pragma once
#include "Editor\EditorWindow.h"
#include "Editor/EditorTree.h"

class CComponentWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CComponentWindow();
    virtual ~CComponentWindow();

private:
    CEditorTree<class CComponent*>* m_Tree;

public:
    void AddItem(class CComponent* Component, const std::string& Name, const std::string& ParentName = "Root");
    void Clear();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void TreeCallback(CEditorTreeItem<class CComponent*>* Node, const std::string& Item);
};

