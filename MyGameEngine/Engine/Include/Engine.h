#pragma once

#include "EngineInfo.h"

class CEngine
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_WindowRS;
	float		m_ClearColor[4];
	static bool m_Loop;
	class CTimer* m_Timer;

public:
	Resolution GetWindowResolution() const
	{
		return m_WindowRS;
	}
	HWND GetWindowHandle() const 
	{
		return m_hWnd;
	}
	HINSTANCE GetWindowInstance() const
	{
		return m_hInst;
	}

public:
	bool Init(HINSTANCE hInst, const TCHAR* Title,
		const TCHAR* ClassName, int IconID, int SmallIconID,
		unsigned int WindowWidth, 
		unsigned int WindowHeight, 
		unsigned int DeviceWidth, unsigned int DeviceHeight, 
		bool WindowMode = true);

	int Run();

private:
	void Logic();
	void Input(float DeltaTime);
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);

private:
	void Register(const TCHAR* ClassName, int IconID, int SmallIconID);
	bool Create(const TCHAR* Title, const TCHAR* ClassName);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CEngine)
};