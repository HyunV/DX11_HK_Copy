#include "MonGenerator.h"
#include "Component/ColliderBox2D.h"
#include "Zombie.h"
#include "Zombie2.h"
#include "Player2D.h"
#include "Scene/Scene.h"
#include <time.h>

CMonGenerator::CMonGenerator()
{
    SetTypeID<CMonGenerator>();

    m_ObjectTypeName = "MonGenerator";
}

CMonGenerator::CMonGenerator(const CMonGenerator& Obj)  :
    CGameObject(Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("GeneratorFrame");
}

CMonGenerator::~CMonGenerator()
{
}



void CMonGenerator::Start()
{
    CGameObject::Start();
    m_Delay = 5.f;

    m_Body->SetWorldPosition(640.f, 800.f);
    m_Body->SetBoxSize(1200.f, 100.f);
    m_FallX = m_Body->GetWorldPos().x;
    m_FallY = m_Body->GetWorldPos().y;

    m_Body->SetCollisionCallback(ECollision_Result::Collision, this, &CMonGenerator::CollisionStart);
}

bool CMonGenerator::Init()
{
    CGameObject::Init();

    m_Body = CreateComponent<CColliderBox2D>("GeneratorFrame");
    SetRootComponent(m_Body);
    //m_Delay = 5.f;
    //m_FallX = m_Body->GetWorldPos().x;
    //m_FallY = m_Body->GetWorldPos().y;
    return true;
}

void CMonGenerator::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    if (m_Start)
    {
        m_Time += DeltaTime;

        if (m_Time >= m_Delay)
        {
            MonsterGenerate();
            m_Time = 0.f;
        }
    }
}

void CMonGenerator::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CMonGenerator* CMonGenerator::Clone() const
{
    return new CMonGenerator(*this);
}

void CMonGenerator::StartGenerate(bool Enable)
{
    m_Start = Enable;
}

void CMonGenerator::MonsterGenerate()
{
    int i = rand() % 2;
    if (i == 0)
    {
        CZombie* Zom = m_Scene->CreateObject<CZombie>("Zombie");

        float k = (float)(rand() % 500);
        int j = rand() % 2;
        if (j == 1)
        {
            Zom->CheckDir();
            Zom->ChangeDir();
            k *= -1.f;
        }

        if (m_CollisionCount % 3 == 0)
        {
            float x = m_Scene->FindObject("Player2D")->GetWorldPos().x;
            Zom->SetWorldPosition(x, m_FallY);
        }
        else
            Zom->SetWorldPosition(m_FallX + k, m_FallY);
        

    }
    else
    {
        CZombie2* Zom2 = m_Scene->CreateObject<CZombie2>("Zombie2");

        float k = (float)(rand() % 500);
        int j = rand() % 2;
        if (j == 1)
        {
            Zom2->CheckDir();
            Zom2->ChangeDir();
            k *= -1.f;
        }
        
        if (m_CollisionCount % 3 == 0)
        {
            float x = m_Scene->FindObject("Player2D")->GetWorldPos().x;
            Zom2->SetWorldPosition(x, m_FallY);
        }
        else
            Zom2->SetWorldPosition(m_FallX + k, m_FallY);
    }

    if (m_CollisionCount % 3 == 0)
    {
        if(!(m_Delay <= 1.f))
            m_Delay -= 0.5f;
    }
}

void CMonGenerator::CollisionStart(const CollisionResult& Result)
{
    m_CollisionCount++;
    char c[256] = {};
    sprintf_s(c, "%d", m_CollisionCount);
    OutputDebugStringA(c);
}
