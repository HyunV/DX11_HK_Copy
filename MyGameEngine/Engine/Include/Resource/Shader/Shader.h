#pragma once
#include "../../Ref.h"
class CShader :
    public CRef
{
    friend class CShaderManager;

protected:
    CShader();
    virtual ~CShader() = 0; //�߻�Ŭ����

protected:
    ShaderType m_ShaderType; //�׷���? ��ǻƮ?

public:
    ShaderType GetShaderType() const
    {
        return m_ShaderType;
    }

public:
    virtual bool Init() = 0; //�̰͵鵵 �߻����� �س���..
    virtual void SetShader() = 0;
};

