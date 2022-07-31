#pragma once
#include "../../Ref.h"
class CShader :
    public CRef
{
    friend class CShaderManager;

protected:
    CShader();
    virtual ~CShader() = 0; //추상클래스

protected:
    ShaderType m_ShaderType; //그래픽? 컴퓨트?

public:
    ShaderType GetShaderType() const
    {
        return m_ShaderType;
    }

public:
    virtual bool Init() = 0; //이것들도 추상으로 해놓네..
    virtual void SetShader() = 0;
};

