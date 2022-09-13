#include "TargetArm.h"

CTargetArm::CTargetArm()	:
	m_TargetDistance(0.f)
{
	SetTypeID<CTargetArm>();

	m_ComponentTypeName = "TargetArm";
}

CTargetArm::CTargetArm(const CTargetArm& component) :
	CSceneComponent(component)
{
	m_TargetDistance = component.m_TargetDistance;
	m_TargetOffset = component.m_TargetOffset;
}

CTargetArm::~CTargetArm()
{
}

void CTargetArm::Destroy()
{
	CSceneComponent::Destroy();
}

void CTargetArm::Start()
{
	CSceneComponent::Start();
}

bool CTargetArm::Init()
{
	CSceneComponent::Init();

	return true;
}

void CTargetArm::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	if (m_Parent)
	{
		Vector3 ParentPos = m_Parent->GetWorldPos();

		Vector3 Pos = ParentPos - GetWorldAxis(m_TargetDistanceAxis) * m_TargetDistance;

		SetWorldPosition(Pos + m_TargetOffset);
	}
}

void CTargetArm::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CTargetArm::Render()
{
	CSceneComponent::Render();
}

CTargetArm* CTargetArm::Clone() const
{
	return new CTargetArm(*this);
}

void CTargetArm::Save(FILE* File)
{
}

void CTargetArm::Load(FILE* File)
{
}
