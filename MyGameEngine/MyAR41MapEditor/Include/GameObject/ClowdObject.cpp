#include "ClowdObject.h"
#include "Component/SpriteComponent.h"
#include "Component/SceneComponent.h"
#include "Resource/Material/Material.h"

CClowdObject::CClowdObject()
{
	SetTypeID<CClowdObject>();

	m_ObjectTypeName = "ClowdObject";
}

CClowdObject::CClowdObject(const CClowdObject& Obj)	:
	CGameObject(Obj)
{
	std::string name = "Clowd";

	m_Component = (CSceneComponent*)FindComponent("Clowds");

	for (int i = 0; i < 20; i++)
	{
		std::string s = name;
		s += std::to_string(i + 1);
		m_Sprite[i] = (CSpriteComponent*)FindComponent(s);
	}
}

CClowdObject::~CClowdObject()
{
}

void CClowdObject::Start()
{
	CGameObject::Start();

	for (int i = 0; i < 20; i++)
	{
		m_Sprite[i]->SetRenderLayerName("Back");
		//m_Sprite[i]->GetMaterial(0)->SetShader("TileMapBackShader");
		m_Sprite[i]->GetMaterial(0)->SetRenderState("DepthDisable");
		//m_Sprite[i]->GetMaterial(0)->SetRenderState("AlphaBlend");
		CAnimation2D* Anim = m_Sprite[0]->GetAnimation();
		Anim->SetPlayScale("Clowd", 1.f);
		Anim->SetPlayTime("Clowd", 10.f);
	}
	for (int i = 0; i < 12; i++)
		m_Sprite[i]->SetTextureReverse(true);
}

bool CClowdObject::Init()
{
	CGameObject::Init();
	//АќСп 20
	m_Component = CreateComponent<CSceneComponent>("Clowds");
	SetRootComponent(m_Component);

	std::string name = "Clowd";
	for (int i = 0; i < 20; i++)
	{	
		std::string n = name;
		n += std::to_string(1 + i);
		CSpriteComponent* Sprite = CreateComponent<CSpriteComponent>(n);
		Sprite->SetWorldPosition(100.f, 100.f);
		Sprite->SetWorldScale(156.f, 143.f);
		Sprite->SetAnimationFile("GrimmClowd");
		Sprite->SetRenderLayerName("Back");
		Sprite->GetMaterial(0)->SetOpacity(0.9f);
		Sprite->GetMaterial(0)->SetRenderState("DepthDisable");
		m_Sprite[i] = Sprite;
	}

	CAnimation2D* Anim = m_Sprite[0]->GetAnimation();
	Anim->SetCurrentAnimation("Clowd");

	for (int i = 0; i < 20; i++)
		m_Component->AddChild(m_Sprite[i]);

	m_Sprite[0]->SetWorldPosition(-290.f, 440.f);
	m_Sprite[0]->SetWorldScale(136.f, 203.f);

	m_Sprite[1]->SetWorldPosition(-340.f, 400.f);

	m_Sprite[2]->SetWorldPosition(-130.f, 390.f);
	m_Sprite[2]->SetWorldScale(116.f, 203.f);

	m_Sprite[3]->SetWorldPosition(-200.f, 360.f);
	m_Sprite[3]->SetWorldScale(156.f, 203.f);

	m_Sprite[4]->SetWorldPosition(-60.f, 260.f);
	m_Sprite[4]->SetWorldScale(156.f, 203.f);

	m_Sprite[5]->SetWorldPosition(0.f, 190.f);
	m_Sprite[5]->SetWorldScale(156.f, 143.f);

	m_Sprite[6]->SetWorldPosition(100.f, 300.f);
	m_Sprite[6]->SetWorldScale(125.f, 115.f);

	m_Sprite[7]->SetWorldPosition(150.f, 130.f);
	m_Sprite[7]->SetWorldScale(156.f, 183.f);

	m_Sprite[8]->SetWorldPosition(260.f, 170.f);
	m_Sprite[8]->SetWorldScale(136.f, 203.f);

	m_Sprite[9]->SetWorldPosition(360.f, 240.f);
	m_Sprite[9]->SetWorldScale(101.f, 103.f);

	m_Sprite[10]->SetWorldPosition(260.f, 50.f);
	m_Sprite[10]->SetWorldScale(156.f, 203.f);

	m_Sprite[11]->SetWorldPosition(420.f, 50.f);
	m_Sprite[11]->SetWorldScale(136.f, 203.f);

	m_Sprite[12]->SetWorldPosition(810.f, 100.f);
	m_Sprite[12]->SetWorldScale(156.f, 143.f);

	m_Sprite[13]->SetWorldPosition(960.f, 150.f);
	m_Sprite[13]->SetWorldScale(156.f, 203.f);

	m_Sprite[14]->SetWorldPosition(960.f, 40.f);
	m_Sprite[14]->SetWorldScale(136.f, 183.f);

	m_Sprite[15]->SetWorldPosition(1100.f, 105.f);
	m_Sprite[15]->SetWorldScale(156.f, 203.f);

	m_Sprite[16]->SetWorldPosition(1030.f, 260.f);
	m_Sprite[16]->SetWorldScale(156.f, 143.f);

	m_Sprite[17]->SetWorldPosition(1160.f, 300.f);
	m_Sprite[17]->SetWorldScale(125.f, 143.f);

	m_Sprite[18]->SetWorldPosition(1240.f, 200.f);
	m_Sprite[18]->SetWorldScale(136.f, 203.f);

	m_Sprite[19]->SetWorldPosition(1280.f, 380.f);
	m_Sprite[19]->SetWorldScale(156.f, 183.f);

	return true;
}

void CClowdObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

CClowdObject* CClowdObject::Clone() const
{
	return new CClowdObject(*this);
}
