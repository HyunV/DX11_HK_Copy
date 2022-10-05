#pragma once

#include "../Ref.h"
#include "../Resource/Shader/UIConstantBuffer.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"

class CUIWidget :
    public CRef
{
    friend class CUIWindow;
    friend class CResourceManager;

protected:
    CUIWidget();
    CUIWidget(const CUIWidget& Widget);
    virtual ~CUIWidget() = 0;

protected:
    static CUIConstantBuffer* m_CBuffer;
    static CAnimation2DConstantBuffer* m_AnimCBuffer;
    class CScene* m_Scene;
    class CUIWindow* m_Owner;
    int     m_ZOrder;
    Vector2	m_Pos;
    Vector2	m_RenderPos;
    Vector2	m_Size;
    Vector2 m_Pivot;
    Vector2 m_MeshSize;
    float   m_Angle;
    float   m_Opacity;
    bool	m_Start;
    Vector4 m_Tint;
    CSharedPtr<class CShader>   m_Shader;
    CSharedPtr<class CMesh>     m_Mesh;

public:
    int GetZOrder() const
    {
        return m_ZOrder;
    }

    class CUIWindow* GetWindow()	const
    {
        return m_Owner;
    }

    const Vector2& GetPos()	const
    {
        return m_Pos;
    }

    const Vector2& GetSize()	const
    {
        return m_Size;
    }

    const Vector4& GetTint()    const
    {
        return m_Tint;
    }

    float GetAngle()    const
    {
        return m_Angle;
    }

    float GetOpacity()  const
    {
        return m_Opacity;
    }

public:
    void SetZOrder(int ZOrder)
    {
        m_ZOrder = ZOrder;
    }

    void SetPos(const Vector2& Pos)
    {
        m_Pos = Pos;
    }

    void SetPos(float x, float y)
    {
        m_Pos.x = x;
        m_Pos.y = y;
    }

    void SetSize(const Vector2& Size)
    {
        m_Size = Size;
    }

    void SetSize(float x, float y)
    {
        m_Size.x = x;
        m_Size.y = y;
    }

    void SetPivot(const Vector2& Pivot)
    {
        m_Pivot = Pivot;
    }

    void SetPivot(float x, float y)
    {
        m_Pivot.x = x;
        m_Pivot.y = y;
    }

    void SetTint(const Vector4& Tint)
    {
        m_Tint = Tint;
    }

    void SetTint(unsigned char r, unsigned char g, unsigned char b,
        unsigned char a)
    {
        m_Tint = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
    }

    void SetOpacity(float Opacity)
    {
        m_Opacity = Opacity;
    }

    void SetAngle(float Angle)
    {
        m_Angle = Angle;
    }

    void SetShader(const std::string& Name);
    void SetMesh(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CUIWidget* Clone();
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

