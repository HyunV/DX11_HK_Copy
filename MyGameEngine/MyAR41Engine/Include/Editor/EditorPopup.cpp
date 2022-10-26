#include "EditorPopup.h"

CEditorPopup::CEditorPopup()
{
}

CEditorPopup::~CEditorPopup()
{
}

bool CEditorPopup::Init()
{
	return true;
}

void CEditorPopup::Render()
{
	ImGui::OpenPopup(m_NameUTF8.c_str());
	if (ImGui::BeginPopup(m_NameUTF8.c_str()))
	{
		ImGui::Text("tq");
		ImGui::Selectable("rr");
		ImGui::EndPopup();
	}
}
