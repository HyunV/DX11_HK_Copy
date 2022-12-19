#pragma once
#include "UIImage.h"

//static int m_DotCount;

class CMainDot :
    public CUIImage
{
    friend class CUIWindow;
    friend class CScene;

protected:
    CMainDot();
    CMainDot(const CMainDot& Image);
    virtual ~CMainDot();

private:
    float m_Time;

    //public:
    //int GetCount()
    //{
    //    return m_DotCount;
    //}

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render();
};

