#pragma once
#include "Scene\SceneInfo.h"
class CEditorTestScene :
    public CSceneInfo
{
public:
    CEditorTestScene();
    ~CEditorTestScene();

public:
    virtual bool Init();
};

