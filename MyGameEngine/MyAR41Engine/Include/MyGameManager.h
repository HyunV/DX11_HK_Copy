#pragma once

#include "EngineInfo.h"
#include "GameObject/GameObject.h"
#include "UI/UIWindow.h"

class CMyGameManager
{
private:
	class CSharedPtr<CGameObject> m_Player;
	class CSharedPtr<CUIWindow> m_HUDWindow;
	//�÷��̾� ����

	
	PlayerInfo m_PlayerInfo;

	//HUD ����

	//���� ���� ����
public:
	void SetPlayer(CGameObject* Player)
	{
		m_Player = Player;
	}
	class CGameObject* GetPlayer()
	{
		return m_Player;
	}

	void SetCUIWindow(CUIWindow* Window)
	{
		m_HUDWindow = Window;
	}

	class CUIWindow* GetHUD()
	{
		return m_HUDWindow;
	}
public:
	bool Init();
public:
	void SetPlayerInfo(int MaxHP, int HP, int Gio);

	PlayerInfo GetPlayerInfo()
	{
		return m_PlayerInfo;
	}

	void CreateFadeUI(EFade Fade);

	DECLARE_SINGLE(CMyGameManager)
};

