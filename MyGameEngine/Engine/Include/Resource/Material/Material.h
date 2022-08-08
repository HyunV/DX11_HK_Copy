#pragma once
#include "../../Ref.h"

struct MaterialTextureInfo
{
    std::string Name;
    ESamplerType SamplerType;
    CSharedPtr<class CTexture>  Texture;
    int     Register;
    int     ShaderBufferType;

    MaterialTextureInfo()   :
        SamplerType(ESamplerType::Linear),
        Register(0),
        ShaderBufferType((int)EShaderBufferType::Pixel)
    {
    }
};
class CMaterial :
    public CRef
{
    friend class CMaterialManager;
    friend class CMesh;
    friend class CPrimitiveComponent;

protected:
    CMaterial();
    CMaterial(const CMaterial& Material);
    virtual ~CMaterial();

private:
    class CScene* m_Scene;

public:
    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

protected:
    CSharedPtr<class CShader>   m_Shader;
    std::vector<MaterialTextureInfo*>   m_vecTextureInfo;
    Vector4     m_BaseColor;
    Vector4     m_AmbientColor;
    Vector4     m_SpecularColor;
    Vector4     m_EmissiveColor;    // 자체적으로 빛을 발산하는 물체일 경우
    float       m_Opacity;          // 불투명도.
    class CMaterialConstantBuffer* m_CBuffer;
};

