#pragma once

#include "../EngineInfo.h"

struct RenderLayer
{
	std::string		Name;
	int				LayerPriority;
	std::list<CSharedPtr<class CSceneComponent>>	RenderList;
};

class CRenderManager
{
private:
	std::vector<RenderLayer*>	m_RenderLayerList;

public:
	void CreateLayer(const std::string& Name, int Priority);
	void SetLayerPriority(const std::string& Name, int Priority);
	void DeleteLayer(const std::string& Name);
	void AddRenderList(class CSceneComponent* Component);

public:
	bool Init();
	void Render(float DeltaTime);

private:
	static bool SortLayer(RenderLayer* Src, RenderLayer* Dest);

	DECLARE_SINGLE(CRenderManager)
};

