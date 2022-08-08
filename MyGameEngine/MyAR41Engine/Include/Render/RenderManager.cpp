
#include "RenderManager.h"
#include "../Component/SceneComponent.h"

DEFINITION_SINGLE(CRenderManager)

CRenderManager::CRenderManager()
{
}

CRenderManager::~CRenderManager()
{
	auto	iter = m_RenderLayerList.begin();
	auto	iterEnd = m_RenderLayerList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}
}

void CRenderManager::CreateLayer(const std::string& Name, int Priority)
{
	RenderLayer* Layer = new RenderLayer;

	Layer->Name = Name;
	Layer->LayerPriority = Priority;

	m_RenderLayerList.push_back(Layer);

	std::sort(m_RenderLayerList.begin(), m_RenderLayerList.end(), CRenderManager::SortLayer);
}

void CRenderManager::SetLayerPriority(const std::string& Name, int Priority)
{
	auto	iter = m_RenderLayerList.begin();
	auto	iterEnd = m_RenderLayerList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->Name == Name)
		{
			(*iter)->LayerPriority = Priority;
			break;
		}
	}

	std::sort(m_RenderLayerList.begin(), m_RenderLayerList.end(), CRenderManager::SortLayer);
}

void CRenderManager::DeleteLayer(const std::string& Name)
{
	auto	iter = m_RenderLayerList.begin();
	auto	iterEnd = m_RenderLayerList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->Name == Name)
		{
			SAFE_DELETE((*iter));
			iter = m_RenderLayerList.erase(iter);
			break;
		}
	}
}

void CRenderManager::AddRenderList(CSceneComponent* Component)
{
	auto	iter = m_RenderLayerList.begin();
	auto	iterEnd = m_RenderLayerList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->Name == Component->GetRenderLayerName())
		{
			(*iter)->RenderList.push_back(Component);
			break;
		}
	}
}

bool CRenderManager::Init()
{
	CreateLayer("Default", 1);
	CreateLayer("Back", 0);

	return true;
}

void CRenderManager::Render(float DeltaTime)
{
	{
		auto	iter = m_RenderLayerList.begin();
		auto	iterEnd = m_RenderLayerList.end();

		for (; iter != iterEnd; ++iter)
		{
			auto	iter1 = (*iter)->RenderList.begin();
			auto	iter1End = (*iter)->RenderList.end();

			for (; iter1 != iter1End;)
			{
				if (!(*iter1)->GetActive())
				{
					iter1 = (*iter)->RenderList.erase(iter1);
					iter1End = (*iter)->RenderList.end();
					continue;
				}

				else if (!(*iter1)->GetEnable())
				{
					++iter1;
					continue;
				}

				(*iter1)->Render();
				++iter1;
			}
		}
	}
}

bool CRenderManager::SortLayer(RenderLayer* Src, RenderLayer* Dest)
{
	return Src->LayerPriority < Dest->LayerPriority;
}
