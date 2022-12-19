#include "GrimmSmoke.h"
#include "Component/SpriteComponent.h"
#include "Resource\Material\Material.h"

CGrimmSmoke::CGrimmSmoke()
{
    SetTypeID<CGrimmSmoke>();

    m_ObjectTypeName = "GrimmSmoke";
}

CGrimmSmoke::CGrimmSmoke(const CGrimmSmoke& Obj)    :
    CGameObject(Obj)
{
}

CGrimmSmoke::~CGrimmSmoke()
{
}

void CGrimmSmoke::Start()
{
    CGameObject::Start();
    m_Sprite->SetRenderLayerName("BackEffect");
}

bool CGrimmSmoke::Init()
{
    CGameObject::Init();


    SetLifeTime(1.f);
    m_Sprite = CreateComponent<CSpriteComponent>("GrimmSmoke");
    m_Sprite->SetWorldPosition(100.f, 100.f);
    m_Sprite->SetWorldScale(430.f, 406.f);
    m_Sprite->SetRenderLayerName("BackEffect");
    m_Sprite->SetPivot(0.5f, 0.5f);

    m_Sprite->SetTexture("Smoke", TEXT("HollowKnight/Effects/smoke.png"));
    m_Opacity = 0.f;
    m_Sprite->GetMaterial(0)->SetOpacity(m_Opacity);
    SetRootComponent(m_Sprite);

    return true;
}

void CGrimmSmoke::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    if (m_Opacity >= 0.8f)
    {
        m_OpaReverse = true;           
    }        
    
    if (!m_OpaReverse)
    {
        m_Opacity += DeltaTime * 4.f;
        if (m_Opacity >= 1.f)
            m_Opacity = 1.f;
    }
    else
    {
        m_Opacity -= DeltaTime * 4.f;
    }
        

    m_Sprite->GetMaterial(0)->SetOpacity(m_Opacity);

    if (m_Opacity < 0.f && m_OpaReverse)
        Destroy();
}

CGrimmSmoke* CGrimmSmoke::Clone() const
{
    return new CGrimmSmoke(*this);
}
