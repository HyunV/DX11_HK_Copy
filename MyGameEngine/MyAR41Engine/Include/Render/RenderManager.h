#pragma once

#include "../EngineInfo.h"
#include "RenderStateManager.h"

struct RenderLayer
{
	std::string		Name;
	int				LayerPriority;
	CSharedPtr<class CRenderState> AlphaBlend;
	std::list<CSharedPtr<class CSceneComponent>>	RenderList;
};

class CRenderManager
{
private:
	std::vector<RenderLayer*>	m_RenderLayerList;
	CRenderStateManager* m_RenderStateManager;

public:
	void CreateLayer(const std::string& Name, int Priority);
	void SetLayerPriority(const std::string& Name, int Priority);
	void SetLayerAlphaBlend(const std::string& Name);
	void DeleteLayer(const std::string& Name);
	void AddRenderList(class CSceneComponent* Component);

public:
	bool Init();
	void Render(float DeltaTime);

public:
	void SetBlendFactor(const std::string& Name, float r, float g, float b, float a);
	void AddBlendInfo(const std::string& Name, bool BlendEnable = true,
		D3D11_BLEND SrcBlend = D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND DestBlend = D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_OP BlendOp = D3D11_BLEND_OP_ADD,
		D3D11_BLEND SrcAlphBlend = D3D11_BLEND_ONE,
		D3D11_BLEND DestAlphBlend = D3D11_BLEND_ZERO,
		D3D11_BLEND_OP BlendAlphOp = D3D11_BLEND_OP_ADD,
		UINT8 WriteMask = D3D11_COLOR_WRITE_ENABLE_ALL);
	bool CreateBlendState(const std::string& Name, bool AlphaToCoverageEnable, bool IndependentBlendEnable);

public:
	template <typename T>
	T* FindRenderState(const std::string& Name)
	{
		return m_RenderStateManager->FindRenderState<T>(Name);
	}

private:
	static bool SortLayer(RenderLayer* Src, RenderLayer* Dest);

	DECLARE_SINGLE(CRenderManager)
};

