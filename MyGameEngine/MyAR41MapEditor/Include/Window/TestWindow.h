#pragma once

//하나의 팝업인가?
#include "Editor/EditorWindow.h"

class CTestWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
	CTestWindow();
	virtual ~CTestWindow();

private:
	//텍스트 입출력 관련 변수
	class CEditorText* m_Text;
	char	m_AddText[1024];
	int		m_AddIndex;
	int		m_AddCount;
	float	m_AddTime;

	class CEditorInput* m_Input;
	class CEditorListBox* m_List;
	class CEditorComboBox* m_Combo;
	class CEditorTree* m_Tree;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void TestButtonCallback();
	void InputCallback();
	void ListCallback(int SelectIndex, const std::string& Item);
	void TreeCallback(const std::string& Item);
};

