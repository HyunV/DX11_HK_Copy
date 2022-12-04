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
    bool m_check; //���� ������  true
    float m_PlayTime; //�� �ʵ��� ���� ��������ΰ�
    float m_Time;

    EFade m_FadeType;


public:
    void StartFade(EFade FadeType, float PlayTime = 1.f);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUImageBlack* Clone();
};

