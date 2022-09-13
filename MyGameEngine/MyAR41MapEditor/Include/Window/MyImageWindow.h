#pragma once
#include "Editor\EditorWindow.h"

//이미지 이름들을 긁어오고
//클릭하면 해당 이미지가 뜨게
//이미지를 게임 오브젝트에 적용가능?
//컴포넌트 윈도우에 선택한 스프라이트에 세팅
class CMyImageWindow :
    public CEditorWindow
{
    friend class CEditorGUIManager;

protected:
    CMyImageWindow();
    virtual ~CMyImageWindow();

private:
    class CEditorListBox* m_ImageList; //이미지 리스트
    std::string     m_SelectImageItem; //선택한 이미지
    std::string     m_SelectComponentItem; //선택한 컴포넌트

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
    void SelectImageCallback(int Index, const std::string& Item); // 이미지 선택
    void ImageSetButtonCallback(); //이미지 설정 콜백
    void LoadImageName();
    
};

