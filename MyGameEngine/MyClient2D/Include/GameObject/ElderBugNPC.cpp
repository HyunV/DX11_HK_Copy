#include "ElderBugNPC.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Animation/Animation2D.h"
#include "Resource/ResourceManager.h" 

CElderBugNPC::CElderBugNPC()
{
    SetTypeID<CElderBugNPC>();
    m_ObjectTypeName = "ElderBugNPC";
}

CElderBugNPC::CElderBugNPC(const CElderBugNPC& Obj) :
    CGameObject(Obj)
{
    m_Body = (CColliderBox2D*)FindComponent("Body");
    m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
}

CElderBugNPC::~CElderBugNPC()
{
}


void CElderBugNPC::Start()
{
    CGameObject::Start();

    m_Body->SetCollisionCallback(ECollision_Result::Collision, this,
        &CElderBugNPC::CollisionCallback);

    CAnimation2D* Anim = m_Sprite->GetAnimation();
    Anim->SetCurrentAnimation("ElderbugIdle");
}

bool CElderBugNPC::Init()
{
    CGameObject::Init();

    m_Body = CreateComponent<CColliderBox2D>("Body");
    m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

    SetRootComponent(m_Sprite);

    m_Body->SetCollisionProfile("NPC");
    m_Sprite->SetAnimationFile("NPCS");

    //д©╫╨ер

    float X = 124.f;
    float Y = 172.f;

    m_Sprite->SetWorldPosition(100.f, 100.f);
    m_Sprite->SetWorldScale(X, Y);
    m_Sprite->SetPivot(0.5f, 0.5f);
    



    m_Sprite->AddChild(m_Body);
    m_Body->SetBoxSize(120.f, 170.f);
    
    m_Sprite->SetTextureReverse(false);

    return true;
}

void CElderBugNPC::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CElderBugNPC::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

CElderBugNPC* CElderBugNPC::Clone() const
{
    return new CElderBugNPC(*this);
}

void CElderBugNPC::CollisionCallback(const CollisionResult& Result)
{
}
