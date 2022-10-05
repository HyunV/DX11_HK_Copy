#pragma once
#include "SceneComponent.h"
class CCollider :
    public CSceneComponent
{
    friend class CGameObject;
    friend class CScene;
    friend class CCollisionManager;

protected:
    CCollider();
    CCollider(const CCollider& component);
    virtual ~CCollider();

protected:
    CSharedPtr<class CMesh> m_Mesh; //콜라이더에 쓸 메시
    CSharedPtr<class CShader> m_Shader; // 콜라이더에 쓸 쉐이더
    Vector4                 m_Color; //테두리 색
    ECollider_Type          m_ColliderType;
    Vector3                 m_Min;
    Vector3                 m_Max;
    CollisionResult         m_Result;   //결과에 반영될 충돌체 대상?
    CollisionResult         m_MouseResult;
    std::list<CCollider*>   m_PrevCollisionList; //이전 프레임에 충돌하고 있던 물체들
    std::list<int>          m_CurrentSectionList;
    CollisionProfile*       m_Profile; //콜리전 프로파일
    Vector3                 m_HitPoint;
    bool                    m_MouseCollision;

    std::function<void(const CollisionResult&)> m_CollisionCallback[(int)ECollision_Result::Max];
    std::function<void(const CollisionResult&)> m_CollisionMouseCallback[(int)ECollision_Result::Max];

public:
    const Vector3& GetMin() const
    {
        return m_Min;
    }

    const Vector3& GetMax() const
    {
        return m_Max;
    }

    ECollider_Type GetColliderType()    const
    {
        return m_ColliderType;
    }

    CollisionProfile* GetCollisionProfile() const
    {
        return m_Profile;
    }
public:
    void AddSectionIndex(int Index)
    {
        m_CurrentSectionList.push_back(Index);
    }

    void AddPrevCollisionCollider(CCollider* Collider)
    {
        m_PrevCollisionList.push_back(Collider);
    }

    void DeletePrevCollisionCollider(CCollider* Collider);
    
    bool CheckPrevCollision(CCollider* Collider);

    //이전 프레임에 충돌했던 충돌체들을 반복하여 현재 나의 영역과 겹치는지 판단한다.
    void CheckPrevCollisionColliderSection();

    //이전 프레임에 충돌되던 물체들에게 충돌해제를 통보한다.
    void SendPrevCollisionEnd();

    void CallCollisionCallback(ECollision_Result Type);
    void CallCollisionMouseCallback(ECollision_Result Type);
    void ClearFrame();

    // 충돌 영역이 겹치는게 2개 이상일 경우 이미 앞에서 충돌처리를 했을것이기 때문에 처리를 안하도록 한다.
    // 반환은 겹치는 충돌섹션이 2개 미만이면 -1, 2개 이상이면 겹치는 영역중 가장 작은 인덱스를 반환한다.
    int CheckOverlapSection(CCollider* Dest);
    void SetCollisionProfile(const std::string& Name);

    void SetCollisionResultDest(CCollider* Dest)
    {
        m_Result.Dest = Dest;
    }

public: 
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CCollider* Clone()    const = 0;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
    virtual bool Collision(CCollider* Dest) = 0;

public:
    template <typename T>
    void SetCollisionCallback(ECollision_Result Type, T* Obj, void(T::* Func)(const CollisionResult&))
    {
        m_CollisionCallback[(int)Type] = std::bind(Func, Obj, std::placeholders::_1);
    }

    template <typename T>
    void SetCollisionMouseCallback(ECollision_Result Type, T* Obj, void(T::* Func)(const CollisionResult&))
    {
        m_CollisionMouseCallback[(int)Type] = std::bind(Func, Obj, std::placeholders::_1);
    }
};

