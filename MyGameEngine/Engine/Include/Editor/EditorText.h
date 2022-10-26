#pragma once
#include "EditorWidget.h"
class CEditorText :
    public CEditorWidget
{
    friend class CEditorWindow;
	friend class CEditorGroup;

	template <typename T>
	friend class CEditorTreeItem;

protected:
    CEditorText();
    virtual ~CEditorText();

private:
    std::string     m_Text;
    std::wstring    m_wText;
    std::string     m_TextUTF8;
	ImVec2 m_Align;

public:
	const std::string& GetText()	const
	{
		return m_Text;
	}

	const std::wstring& GetWText()	const
	{
		return m_wText;
	}

	const std::string& GetTextUTF8()	const
	{
		return m_TextUTF8;
	}
	void SetAlign(float x, float y)
	{
		m_Align.x = x;
		m_Align.y = y;
	}

public:
	void SetText(const std::string& Text);
	void AddText(const std::string& Text);

public:
	virtual bool Init();
	virtual void Render();
};

