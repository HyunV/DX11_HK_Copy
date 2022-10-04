#include "CollisionManager.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderPixel.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	{
		auto	iter = m_mapProfile.begin();
		auto	iterEnd = m_mapProfile.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}
	}

	{
		auto	iter = m_vecChannel.begin();
		auto	iterEnd = m_vecChannel.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE((*iter));
		}
	}
}

bool CCollisionManager::Init()
{
	CreateChannel("Default", ECollision_Interaction::Collision);
	CreateChannel("Mouse", ECollision_Interaction::Collision);

	CreateProfile("Default", "Default", true);
	CreateProfile("Mouse", "Mouse", true);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name,
	const std::string& ChannelName, bool Enable,
	ECollision_Interaction BaseInteraction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (Profile)
		return false;

	CollisionChannel* Channel = nullptr;

	size_t	Count = m_vecChannel.size();

	for (size_t i = 0; i < Count; ++i)
	{
		if (m_vecChannel[i]->Name == ChannelName)
		{
			Channel = m_vecChannel[i];
			break;
		}
	}

	if (!Channel)
		return false;

	Profile = new CollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;
	Profile->vecCollisionInteraction.resize(m_vecChannel.size());

	Count = Profile->vecCollisionInteraction.size();

	for (size_t i = 0; i < Count; ++i)
	{
		Profile->vecCollisionInteraction[i] = BaseInteraction;
	}

	m_mapProfile.insert(std::make_pair(Name, Profile));

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& Name,
	const std::string& ChannelName, ECollision_Interaction Interaction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	CollisionChannel* Channel = nullptr;

	size_t	Count = m_vecChannel.size();

	for (size_t i = 0; i < Count; ++i)
	{
		if (m_vecChannel[i]->Name == ChannelName)
		{
			Channel = m_vecChannel[i];
			break;
		}
	}

	if (!Channel)
		return false;

	Profile->vecCollisionInteraction[(int)Channel->Channel] = Interaction;

	return true;
}

bool CCollisionManager::CreateChannel(const std::string& Name,
	ECollision_Interaction Interaction)
{
	size_t	Count = m_vecChannel.size();

	for (size_t i = 0; i < Count; ++i)
	{
		if (m_vecChannel[i]->Name == Name)
			return false;
	}

	CollisionChannel* NewChannel = new CollisionChannel;

	NewChannel->Name = Name;
	NewChannel->Channel = (ECollision_Channel)m_vecChannel.size();
	NewChannel->Interaction = Interaction;

	m_vecChannel.push_back(NewChannel);

	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->vecCollisionInteraction.push_back(Interaction);
	}

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& Name)
{
	auto	iter = m_mapProfile.find(Name);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}

bool CCollisionManager::CollisionBox2DToBox2D(Vector2& HitPoint, CColliderBox2D* Src, CColliderBox2D* Dest)
{
	if (CollisionBox2DToBox2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionSphere2DToSphere2D(Vector2& HitPoint, CColliderSphere2D* Src,
	CColliderSphere2D* Dest)
{
	if (CollisionSphere2DToSphere2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionOBB2DToOBB2D(Vector2& HitPoint, CColliderOBB2D* Src, CColliderOBB2D* Dest)
{
	return false;
}

bool CCollisionManager::CollisionBox2DToSphere2D(Vector2& HitPoint, CColliderBox2D* Src, CColliderSphere2D* Dest)
{
	if (CollisionBox2DToSphere2D(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = Vector3(HitPoint.x, HitPoint.y, 0.f);
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToOBB2D(Vector2& HitPoint, CColliderBox2D* Src, CColliderOBB2D* Dest)
{
	return false;
}

bool CCollisionManager::CollisionBox2DToPixel(Vector2& HitPoint, CColliderBox2D* Src, CColliderPixel* Dest)
{
	return false;
}

bool CCollisionManager::CollisionSphere2DToOBB2D(Vector2& HitPoint, CColliderSphere2D* Src, CColliderOBB2D* Dest)
{
	return false;
}

bool CCollisionManager::CollisionSphere2DToPixel(Vector2& HitPoint, CColliderSphere2D* Src, CColliderPixel* Dest)
{
	return false;
}

bool CCollisionManager::CollisionOBB2DToPixel(Vector2& HitPoint, CColliderOBB2D* Src, CColliderPixel* Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToBox2D(Vector2& HitPoint, const Vector2& Src, CColliderBox2D* Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToSphere2D(Vector2& HitPoint, const Vector2& Src, CColliderSphere2D* Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToOBB2D(Vector2& HitPoint, const Vector2& Src, CColliderOBB2D* Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToPixel(Vector2& HitPoint, const Vector2& Src, CColliderPixel* Dest)
{
	return false;
}

bool CCollisionManager::CollisionBox2DToBox2D(Vector2& HitPoint, const Box2DInfo& Src,
	const Box2DInfo& Dest)
{
	if (Src.Left > Dest.Right)
		return false;

	else if (Src.Right < Dest.Left)
		return false;

	else if (Src.Bottom > Dest.Top)
		return false;

	else if (Src.Top < Dest.Bottom)
		return false;

	float Left = Src.Left > Dest.Left ? Src.Left : Dest.Left;
	float Bottom = Src.Bottom > Dest.Bottom ? Src.Bottom : Dest.Bottom;
	float Right = Src.Right < Dest.Right ? Src.Right : Dest.Right;
	float Top = Src.Top < Dest.Top ? Src.Top : Dest.Top;

	HitPoint.x = (Left + Right) / 2.f;
	HitPoint.y = (Top + Bottom) / 2.f;

	return true;
}

bool CCollisionManager::CollisionSphere2DToSphere2D(Vector2& HitPoint, const Sphere2DInfo& Src,
	const Sphere2DInfo& Dest)
{
	float	Dist = Src.Center.Distance(Dest.Center);

	bool result = Dist <= Src.Radius + Dest.Radius;

	HitPoint = (Src.Center + Dest.Center) / 2.f;

	return result;
}

bool CCollisionManager::CollisionOBB2DToOBB2D(Vector2& HitPoint, const OBB2DInfo& Src, const OBB2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionBox2DToSphere2D(Vector2& HitPoint, const Box2DInfo& Src,
	const Sphere2DInfo& Dest)
{
	if ((Src.Left <= Dest.Center.x && Dest.Center.x <= Src.Right) ||
		(Src.Bottom <= Dest.Center.y && Dest.Center.y <= Src.Top))
	{
		Box2DInfo	Info = Src;
		Info.Left -= Dest.Radius;
		Info.Bottom -= Dest.Radius;
		Info.Right += Dest.Radius;
		Info.Top += Dest.Radius;

		if (Info.Left > Dest.Center.x)
			return false;

		else if (Info.Bottom > Dest.Center.y)
			return false;

		else if (Info.Right < Dest.Center.x)
			return false;

		else if (Info.Top < Dest.Center.y)
			return false;

		Box2DInfo	OverlapBox;

		OverlapBox.Left = Dest.Center.x - Dest.Radius;
		OverlapBox.Bottom = Dest.Center.y - Dest.Radius;
		OverlapBox.Right = Dest.Center.x + Dest.Radius;
		OverlapBox.Top = Dest.Center.y + Dest.Radius;

		OverlapBox.Left = Src.Left > OverlapBox.Left ? Src.Left : OverlapBox.Left;
		OverlapBox.Bottom = Src.Bottom > OverlapBox.Bottom ? Src.Bottom : OverlapBox.Bottom;
		OverlapBox.Right = Src.Right < OverlapBox.Right ? Src.Right : OverlapBox.Right;
		OverlapBox.Top = Src.Top < OverlapBox.Top ? Src.Top : OverlapBox.Top;

		HitPoint.x = (OverlapBox.Left + OverlapBox.Right) / 2.f;
		HitPoint.y = (OverlapBox.Bottom + OverlapBox.Top) / 2.f;

		return true;
	}

	Vector2	Pos[4] =
	{
		Vector2(Src.Left, Src.Top),
		Vector2(Src.Right, Src.Top),
		Vector2(Src.Left, Src.Bottom),
		Vector2(Src.Right, Src.Bottom)
	};

	for (int i = 0; i < 4; ++i)
	{
		float Dist = Dest.Center.Distance(Pos[i]);

		if (Dist <= Dest.Radius)
		{
			Box2DInfo	OverlapBox;

			OverlapBox.Left = Dest.Center.x - Dest.Radius;
			OverlapBox.Bottom = Dest.Center.y - Dest.Radius;
			OverlapBox.Right = Dest.Center.x + Dest.Radius;
			OverlapBox.Top = Dest.Center.y + Dest.Radius;

			OverlapBox.Left = Src.Left > OverlapBox.Left ? Src.Left : OverlapBox.Left;
			OverlapBox.Bottom = Src.Bottom > OverlapBox.Bottom ? Src.Bottom : OverlapBox.Bottom;
			OverlapBox.Right = Src.Right < OverlapBox.Right ? Src.Right : OverlapBox.Right;
			OverlapBox.Top = Src.Top < OverlapBox.Top ? Src.Top : OverlapBox.Top;

			HitPoint.x = (OverlapBox.Left + OverlapBox.Right) / 2.f;
			HitPoint.y = (OverlapBox.Bottom + OverlapBox.Top) / 2.f;

			return true;
		}
	}

	return false;
}

bool CCollisionManager::CollisionBox2DToOBB2D(Vector2& HitPoint, const Box2DInfo& Src, const OBB2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionBox2DToPixel(Vector2& HitPoint, const Box2DInfo& Src, const PixelInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionSphere2DToOBB2D(Vector2& HitPoint, const Sphere2DInfo& Src, const OBB2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionSphere2DToPixel(Vector2& HitPoint, const Sphere2DInfo& Src, CColliderPixel* Dest)
{
	return false;
}

bool CCollisionManager::CollisionOBB2DToPixel(Vector2& HitPoint, const OBB2DInfo& Src, const PixelInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToBox2D(Vector2& HitPoint, const Vector2& Src, const Box2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToSphere2D(Vector2& HitPoint, const Vector2& Src, const Sphere2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToOBB2D(Vector2& HitPoint, const Vector2& Src, const OBB2DInfo& Dest)
{
	return false;
}

bool CCollisionManager::CollisionPointToPixel(Vector2& HitPoint, const Vector2& Src, const PixelInfo& Dest)
{
	return false;
}
