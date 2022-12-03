#pragma once

#include "UIWidget.h"

class CUIImage :
    public CUIWidget
{
    friend class CUIWindow;
    friend class CScene;

protected:
    CUIImage();
    CUIImage(const CUIImage& Image);
    virtual ~CUIImage();

protected:
    UIWidgetImageInfo   m_TextureInfo;
    bool m_StartAnimation;
    bool m_Destroy;

public:
    void AnimationEnable(bool Enable, int StartFrame = 0)
    {
        m_StartAnimation = Enable;
        m_TextureInfo.Frame = StartFrame;
        if (StartFrame == 0)
        {
            m_TextureInfo.Time = 0.f;
        }
    }
    void SetDestroy(bool Enable)
        {
            m_Destroy = Enable;
        }

public:
    void SetTexture(CTexture* Texture);
    bool SetTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
    bool SetTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    void SetImageTint(const Vector4& Tint);
    void SetImageTint(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void AddFrameData(const Vector2& Start, const Vector2& End);
    void SetPlayTime(float PlayTime);
    void SetPlayScale(float PlayScale);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUIImage* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

