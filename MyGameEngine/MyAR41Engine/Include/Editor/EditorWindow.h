#pragma once

#include "EditorInfo.h"

//imgui는 툴을 원하는 곳에 마음대로 배치할 수가 없다.

class CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CEditorWindow();
	virtual ~CEditorWindow();

protected:
	std::string		m_Name;
	bool			m_Open;
	int				m_WindowFlag; //이걸 이용해서 위젯 생성
	std::vector<class CEditorWidget*> m_vecWidget; //창에 여러개의 위젯을 가질 수 있게

public:
	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	void AddWindowFlag(ImGuiWindowFlags_ Flag)
	{
		m_WindowFlag |= Flag;
	}

public:
	void Open();
	void Close();
	class CEditorWidget* FindWidget(const std::string& Name);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	template <typename T>
	T* CreateWidget(const std::string& Name, float Width = 100.f, float Height = 100.f)
	{
		T* Widget = new T;

		Widget->SetName(Name);
		Widget->m_Owner = this;
		Widget->SetSize(Width, Height);

		if (!Widget->Init())
		{
			SAFE_DELETE(Widget);
			return nullptr;
		}

		m_vecWidget.push_back(Widget);

		return Widget;
	}
};

