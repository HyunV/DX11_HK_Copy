#pragma once
#include "Shader.h"
class CGraphicShader :
    public CShader
{
    friend class CShaderManager;

protected:
    CGraphicShader();
    virtual ~CGraphicShader() = 0;

private:
    ID3D11InputLayout* m_InputLayout; 
    //정점이 어떻게 생겼는지 알려주기 위해
    //레이아웃 세팅을 해준다.

    // D3D11_INPUT_ELEMENT_DESC 구조체 1개가 정점을 구성하는 요소 1개다.
    // 위치, 색상이라면 2개의 구조체가 작성되어 추가되어야 한다.
    std::vector<D3D11_INPUT_ELEMENT_DESC> m_vecInputDesc;

    unsigned int m_InputSize;

private:
    ID3D11VertexShader* m_VS;
    ID3DBlob* m_VSBlob;  //VertexShader 코드를 가지고 있을 버퍼

    ID3D11PixelShader* m_PS;
    ID3DBlob* m_PSBlob; //픽셀셰이더 코드를 가지고 있을 버퍼

    ID3D11HullShader* m_HS; //덮개 쉐이더
    ID3DBlob* m_HSBlob;

    ID3D11DomainShader* m_DS; //도메인 쉐이더 (영영?)
    ID3DBlob* m_DSBlob;

    ID3D11GeometryShader* m_GS; // 기하 쉐이더 (지오메트리)
    ID3DBlob* m_GSBlob;

public:
    virtual bool Init() = 0;
    virtual void SetShader();

public:
    void AddInputDesc(const char* SemanticName, unsigned int SemanticIndex,
        DXGI_FORMAT Fmt, unsigned int Slot, unsigned int Size,
        D3D11_INPUT_CLASSIFICATION SlotClass,
        unsigned int InstanceDataStepRate);
    /*
    시멘틱네임 : 정점 셰이더의 유효한 문자열 이름(변수 이름)
    시멘틱 인덱스 : 유효한 인덱스(텍스쳐 좌표의 인덱스 구분)
    포맷 : 정점의 자료 형식
    슬롯 : 이 성분의 자료가 공급될 정점버퍼 슬롯의 인덱스
    사이즈 :
    인풋 슬롯 클래스 :인스턴싱에 쓰이는 부분
    인스턴스 데이타 스텝 레이트 : 인스턴싱에 쓰이는 부분
    */

    bool CreateInputLayout();
    bool LoadVertexShader(const char* EntryName, const TCHAR* FileName,
        const std::string& PathName);
    bool LoadPixelShader(const char* EntryName, const TCHAR* FileName,
        const std::string& PathName);
    bool LoadHullShader(const char* EntryName, const TCHAR* FileName,
        const std::string& PathName);
    bool LoadDomainShader(const char* EntryName, const TCHAR* FileName,
        const std::string& PathName);
    bool LoadGeometryShader(const char* EntryName, const TCHAR* FileName,
        const std::string& PathName);

};

