#pragma once
//������ ����â ����ϴ� �༮
#include "Editor.h"

class CEditorManager
{
public:
	CEditorManager();
	~CEditorManager();

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void SaveScene();
	void OpenScene();
	void CreateEmptyObject();
	void CreateObject();
	void CreateCDO();
};

