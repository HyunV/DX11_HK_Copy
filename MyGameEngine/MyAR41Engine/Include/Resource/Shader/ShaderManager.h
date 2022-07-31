#pragma once

#include "../../EngineInfo.h"

class CShaderManager
{
	friend class CResourceManager;

private:
	CShaderManager();
	~CShaderManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CShader>> m_mapShader;

public:
	bool Init();
	class CShader* FindShader(const std::string& Name);
	void ReleaseShader(const std::string& Name);

public:
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		T* Shader = (T*)FindShader(Name);

		if (Shader)
			return true;

		Shader = new T;

		Shader->SetName(Name);

		if (!Shader->Init())
		{
			SAFE_DELETE(Shader);
			return false;
		}

		m_mapShader.insert(std::make_pair(Name, Shader));

		return true;
	}
};

