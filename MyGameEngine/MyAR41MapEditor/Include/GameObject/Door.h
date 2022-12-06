#pragma once
#include "GameObject\GameObject.h"
class CDoor :
    public CGameObject
{
    friend class CScene;

    enum class EDoorName
    {
        None,
        TownToArena,
        TownToShop,
        TownToBoss,
        ArenaToTown,     
        ShopToTown,
        BossToTown,
    };

protected:
    CDoor();
    CDoor(const CDoor& Obj);
    virtual ~CDoor();

private:
    CSharedPtr<class CColliderBox2D> m_Body;
    CSharedPtr<class CSpriteComponent>	m_InBox;
    CSharedPtr<class CSpriteComponent>	m_DoorImage;
    //Body의 이름을 받아서 Enum
    EDoorName m_DoorName;
public:
    void SetEnableBox(bool Enable);
    void SetDoorSpriteEnable(bool Enable);
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CDoor* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

public:
    void ChangeScene(std::string& Name);
    void SetPlayer(EDoorName DoorName);
    

public:
    void CollisionBegin(const CollisionResult& Result);
};

