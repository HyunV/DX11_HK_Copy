#pragma once
#include "UIImage.h"

class CMainSmoke :
    public CUIImage
{
    friend class CUIWindow;
    friend class CScene;

protected:
    CMainSmoke();
    CMainSmoke(const CMainSmoke& Image);
    virtual ~CMainSmoke();

private:
    float m_Time;
    float m_Opacity;
    bool m_OpaReverse;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
    
};

