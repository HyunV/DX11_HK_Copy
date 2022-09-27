#pragma once

#include "EngineInfo.h"

class CCollisionManager
{
private:
	std::unordered_map<std::string, CollisionProfile*> m_mapProfile;
	std::vector<CollisionChannel*> m_vecChannel;

public:
	bool Init();

	bool CreateProfile(const std::string& Name, const std::string& ChannelName,
		bool Enable, ECollision_Interaction BaseInteraction = ECollision_Interaction::Collision);
	bool SetCollisionInteraction(const std::string& Name, const std::string& ChannelName,
		ECollision_Interaction Interaction);
	bool CreateChannel(const std::string& Name,
		ECollision_Interaction Interaction = ECollision_Interaction::Collision);
	CollisionProfile* FindProfile(const std::string& Name);

	DECLARE_SINGLE(CCollisionManager)
};

