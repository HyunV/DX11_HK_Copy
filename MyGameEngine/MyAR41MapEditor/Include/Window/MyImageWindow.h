#pragma once
#include "Editor\EditorWindow.h"

//�̹��� �̸����� �ܾ����
//Ŭ���ϸ� �ش� �̹����� �߰�
//�̹����� ���� ������Ʈ�� ���밡��?
//������Ʈ �����쿡 ������ ��������Ʈ�� ����
class CMyImageWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CMyImageWindow();
    virtual ~CMyImageWindow();

private:
    class CEditorListBox* m_ImageList; //�̹��� ����Ʈ
    std::string     m_SelectImageItem; //������ �̹���
    std::string     m_SelectComponentItem; //������ ������Ʈ

    class CEditorInput* m_SelectImageName;
    class CEditorInput* m_SelectComponentName;
    class CEditorImage* m_SelectImageView;

public:
    const std::string& GetSelectImageItem() const
    {
        return m_SelectImageItem;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void SelectImageCallback(int Index, const std::string& Item); // �̹��� ����
    void ImageSetButtonCallback(); //�̹��� ���� �ݹ�
    void LoadImageName();
    
};

