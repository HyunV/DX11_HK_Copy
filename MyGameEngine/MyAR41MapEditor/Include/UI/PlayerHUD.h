#pragma once
#include "UI\UIWindow.h"
class CPlayerHUD :
    public CUIWindow
{
    friend class CSceneViewport;
    friend class CScene;

protected:
    CPlayerHUD();
    CPlayerHUD(const CPlayerHUD& Window);
    virtual ~CPlayerHUD();

protected:
    //NPC 대화상자
    CSharedPtr<class CUIImage> m_Mask;    
    CSharedPtr<class CUIText> m_GioCount;
    
    std::stack<class CUIImage*> m_LifeStack;
    std::vector<class CUIImage*> m_EmptyLife;
    class CUIImage* m_LifeEffect;
    int m_LifeCount;
    
    class CPlayer2D* m_Player;

    float m_Time;
    bool m_Enable;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerHUD* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

public:
    void CreateHeart(int count);
    
    void CreateEmptyHeart();

    void CreateBreakHeart();

    void CreateRefillHeart();

    void CreateChargeOnEffect();

    void DeleteHeart();
    void UpgradeMaxHeart();

    void CreateFadeUI(EFade Fade, float PlayTime);
};

