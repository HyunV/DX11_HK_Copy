#pragma once
#include "EditorWidget.h"
//��: ������
class CEditorLabel :
    public CEditorWidget
{
    friend class CEditorWindow;

protected:
    CEditorLabel();
    virtual ~CEditorLabel();

private:
    ImVec2 m_Align; //���ı���

public:
    void SetAlign(float x, float y)
    {
        
        m_Align.x = x; //0:���� 0.5:�߰� 1:������
        m_Align.y = y; //0:�� 0.5: �߰� 1: �Ʒ�
    }

public:
    virtual bool Init();
    virtual void Render();
};

