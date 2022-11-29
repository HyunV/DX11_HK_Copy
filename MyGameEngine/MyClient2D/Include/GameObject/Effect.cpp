#include "Effect.h"
#include "Component/SpriteComponent.h"
#include "Animation/Animation2D.h"

CEffect::CEffect()
{
	SetTypeID<CEffect>();

	m_ObjectTypeName = "Effect";
}

CEffect::CEffect(const CEffect& Obj)	:
	CGameObject(Obj)
{
}

CEffect::~CEffect()
{
}

void CEffect::Start()
{
	CGameObject::Start();
	m_Sprite->SetRenderLayerName("BackEffect");
}

bool CEffect::Init()
{
	CGameObject::Init();

	//SetRootComponent(m_Sprite);
	m_Sprite = CreateComponent<CSpriteComponent>("EffectSprite");
	m_Sprite->SetWorldPosition(640.f, 360.f);
	m_Sprite->SetWorldScale(100.f, 100.f);
	m_Sprite->SetRenderLayerName("BackEffect");
	m_Sprite->SetPivot(0.5f, 0.5f);

	m_Sprite->SetAnimationFile("Effects");
	return true;
}

void CEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

CEffect* CEffect::Clone() const
{
	return new CEffect(*this);
}

void CEffect::SetCurAnimation(std::string& AnimationName, float PlayScale)
{
	m_Sprite->GetAnimation()->SetCurrentAnimation(AnimationName);
	m_Sprite->GetAnimation()->SetPlayScale(AnimationName, PlayScale);
}
