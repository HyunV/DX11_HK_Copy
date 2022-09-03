#pragma once
#include "EditorWidget.h"
#include "EditorTreeItem.h"

class CEditorTree :
    public CEditorWidget
{
    friend class CEditorWindow;

protected:
    CEditorTree();
    virtual ~CEditorTree();

private:
    CEditorTreeItem* m_Root;
    std::function<void(const std::string&)> m_SelectCallback;

public:
    void AddItem(const std::string& Item, const std::string& ParentItem = "");
    void DeleteItem(const std::string& Item);

public:
    virtual bool Init();
    virtual void Render();

private:
    void NodeSelect(const std::string& Item);

public:
    template <typename T>
    void SetSelectCallback(T* Obj, void(T::* Func)(const std::string&))
    {
        m_SelectCallback = std::bind(Func, Obj, std::placeholders::_1);
    }
};

