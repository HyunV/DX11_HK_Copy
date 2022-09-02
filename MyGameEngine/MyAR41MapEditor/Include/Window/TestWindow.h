#pragma once

//하나의 팝업인가?
#include "Editor/EditorWindow.h"

class CTestWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
	CTestWindow();
	virtual ~CTestWindow();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void TestButtonCallback();
};

