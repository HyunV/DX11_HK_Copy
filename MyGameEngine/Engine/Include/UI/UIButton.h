#pragma once

#include "UIWidget.h"

class CUIButton :
    public CUIWidget
{
    friend class CUIWindow;

protected:
    CUIButton();
    CUIButton(const CUIButton& Button);
    virtual ~CUIButton();

protected:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUIButton* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

