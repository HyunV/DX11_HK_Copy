#pragma once

#include "EditorInfo.h"

class CEditorTreeItem
{
	friend class CEditorTree;

private:
	CEditorTreeItem();
	~CEditorTreeItem();

private:
	ImGuiTreeNodeFlags m_Flag;
	CEditorTreeItem* m_Parent; //ºÎ¸ð
	std::vector<CEditorTreeItem*>	m_vecChild;
	std::string		m_Item;
	std::string		m_ItemUTF8;
	std::function<void(const std::string&)> m_SelectCallback;

public:
	void AddFlag(ImGuiTreeNodeFlags_ Flag);
	void AddItem(const std::string& Item);
	void AddItem(CEditorTreeItem* Item);
	CEditorTreeItem* FindItem(const std::string& Item);
	void Render();

public:
	template <typename T>
	void SetSelectCallback(T* Obj, void (T::* Func)(const std::string&))
	{
		m_SelectCallback = std::bind(Func, Obj, std::placeholders::_1);
	}
};

