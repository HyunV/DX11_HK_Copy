#pragma once
#include "Editor\EditorWindow.h"

//오브젝트 생성 클래스?
class CObjectWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CObjectWindow();
    virtual ~CObjectWindow();

private:
    class CEditorTree* m_Tree;

public:
    void AddItem(const std::string& Name, const std::string& ParentName = "Root");

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void TreeCallback(const std::string& Item);
};

