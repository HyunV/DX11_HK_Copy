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
    //체력바
    //NPC 대화상자
    //CSharedPtr<class CUIImage> m_Frame;
    //CSharedPtr<class CUIProgressBar> m_Bar;
    
    CSharedPtr<class CUIText> m_GioCount;
    //CSharedPtr<class CUIImage> m_GioImage;
    //CSharedPtr<class CUIImage> TitleShade;
    //CSharedPtr<class CUIImage> m_Life[8];
    //std::vector<CSharedPtr<class CUIImage>> m_vecLife;
    class CPlayer2D* m_Player;
    float m_Count;
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
    void SetHealth();
    void HealthMaxUp();
    void HealthBreak();
    void SetEmptyHealth();
    void HealthRefill();
};

