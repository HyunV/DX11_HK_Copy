#pragma once
#include "UI\UIWindow.h"
class CShopUI :
	public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CShopUI();
	CShopUI(const CShopUI& Window);
	virtual ~CShopUI();
private:
	class CUIText* m_SlyText;
	class CUIButton* m_HPUpButton;
	class CUIButton* m_AtkUpButton;
	class CUIButton* m_ShadowDashButton;
	class CUIButton* m_ShadowBallButton;
	class CUIButton* m_EndingButton;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render();
private:
	struct Products
	{
		bool HPUp;
		bool AtkUp;
		bool ShadowDash;
		bool ShadowBall;
		bool Ending;
	};

	Products m_Product;
	class CPlayer2D* m_Player;
	int m_PlayerGio;

public:
	void SetShop();
	void CloseShop();
private:
	void HPUpButton();
	void AtkUpButton();
	void ShadowDashButton();
	void ShadowBallButton();
	void EndingButton();
private:
	void LoadEnding();

};
