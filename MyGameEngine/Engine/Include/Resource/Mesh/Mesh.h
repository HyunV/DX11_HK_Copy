#pragma once

#include "../../Ref.h"

class CMesh :
    public CRef
{
    friend class CMeshManager; //메시매니저는 얘 맘대로 다룰 수 있음.

protected:
    CMesh();
    virtual ~CMesh() = 0; //메시는 추상클래스로 pure처리

protected:
    class CScene* m_Scene; //메시가 소속된 씬을 담아둠.

public:
    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

protected:
    std::vector<MeshContainer*> m_vecContainer; //메시 컨테이너
    std::vector<MeshSlot*>      m_vecMeshSlot; //메시 슬롯

    Vector3 m_Min; //최소
    Vector3 m_Max; //최대
    MeshType    m_MeshType; //메시 타입(스프라이트? UI? 애니메이션?)

public:
    MeshType GetMeshType()  const
    {
        return m_MeshType;
    }

    const Vector3& GetMin() const
    {
        return m_Min;
    }

    const Vector3& GetMax() const
    {
        return m_Max;
    }

public:
    virtual bool CreateMesh(void* VtxData, int Size, int Count,
        D3D11_USAGE VtxUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive,
        void* IdxData = nullptr, int IdxSize = 0, int IdxCount = 0,
        D3D11_USAGE IdxUsage = D3D11_USAGE_DEFAULT,
        DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN);
    virtual void Render();
    virtual void Render(int SlotNumber);


protected:
    bool CreateBuffer(BufferType Type, void* Data, int Size,
        int Count, D3D11_USAGE Usage, ID3D11Buffer** Buffer);
    //버퍼 타입, 뭐 넣을지 모르는 데이터, 정점의 크기, 정점의 개수, 이 버퍼 사용처, 이중포인터 버퍼
};

