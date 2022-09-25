#include "EditorCheckBox.h"

CEditorCheckBox::CEditorCheckBox()	:
	m_checked(false)
{
}

CEditorCheckBox::~CEditorCheckBox()
{
}

bool CEditorCheckBox::Init()
{
	
	return true;
}

void CEditorCheckBox::Render()
{
	ImGui::Checkbox(m_NameUTF8.c_str(), &m_checked);

	//부울값만 받아서 쓸거라 필요없을듯
//	if (m_checked && m_CheckCallback)
//		m_CheckCallback();
}
