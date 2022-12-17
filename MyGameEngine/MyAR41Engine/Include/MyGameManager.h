#pragma once

#include "EngineInfo.h"
#include "GameObject/GameObject.h"
#include "UI/UIWindow.h"

class CMyGameManager
{
private:
	class CSharedPtr<CGameObject> m_Player;
	class CSharedPtr<CUIWindow> m_HUDWindow;
	//플레이어 저장

	
	PlayerInfo m_PlayerInfo;

	//HUD 저장

	//상인 물건 저장
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
	void SetPlayerInfo(PlayerInfo Info);

	PlayerInfo GetPlayerInfo()
	{
		return m_PlayerInfo;
	}

	void ClearPlayerInfo();

	void CreateFadeUI(EFade Fade);

	DECLARE_SINGLE(CMyGameManager)
};

