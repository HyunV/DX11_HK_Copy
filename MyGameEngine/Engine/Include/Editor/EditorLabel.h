#pragma once
#include "EditorWidget.h"
//라벨: 네임택
class CEditorLabel :
    public CEditorWidget
{
    friend class CEditorWindow;

protected:
    CEditorLabel();
    virtual ~CEditorLabel();

private:
    ImVec2 m_Align; //정렬기준

public:
    void SetAlign(float x, float y)
    {
        
        m_Align.x = x; //0:왼쪽 0.5:중간 1:오른쪽
        m_Align.y = y; //0:위 0.5: 중간 1: 아래
    }

public:
    virtual bool Init();
    virtual void Render();
};

