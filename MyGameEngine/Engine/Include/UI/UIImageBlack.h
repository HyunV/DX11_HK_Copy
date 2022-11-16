#pragma once

#include "UIImage.h"

class CUImageBlack :
    public CUIImage
{
    friend class CUIWindow;
    friend class CScene;

protected:
    CUImageBlack();
    CUImageBlack(const CUImageBlack& Image);
    virtual ~CUImageBlack();

private:
    bool m_check;
    EFade m_Fade;
    float m_Time;
    float m_Count;
    float m_Scale;

public:
    void StartFade(EFade Fade, float Time);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUImageBlack* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

