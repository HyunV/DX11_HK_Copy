#include "MyImageWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "PathManager.h"
#include "Resource/Texture/Texture.h"
#include "Resource/Texture/TextureManager.h"
#include "Component/SpriteComponent.h"
#include "Resource/Material/Material.h"


CMyImageWindow::CMyImageWindow()
{
}

CMyImageWindow::~CMyImageWindow()
{
}

void CMyImageWindow::SetSelectComponent(const std::string& Item, CSceneComponent* Component)
{
    m_SelectComponent = Component;

    char Text[256] = {};
    sprintf_s(Text, "%s\n", Item.c_str());

    m_SelectComponentName->SetText(Item.c_str());

    if (Component && Component->GetComponentTypeName() == "SpriteComponent")
    {
        CTexture* Texture = ((CSpriteComponent*)Component)->GetTexture();

        if(Texture)
            m_LoadSpriteImageView->SetTexture(Texture);
    }
}

bool CMyImageWindow::Init()
{
    CEditorLabel* Label = CreateWidget<CEditorLabel>("Image");

    Label->SetColor(255, 0, 0, 255);
    Label->SetAlign(0.5f, 0.5f);
    Label->SetSize(120.f, 30.f);
    
    CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
    Line = CreateWidget<CEditorSameLine>("Line");

    //
    m_SelectImageName = CreateWidget<CEditorInput>("ImageName");

    m_SelectImageName->SetHideName("ObjectName");
    m_SelectImageName->SetSize(150.f, 30.f);
    m_SelectImageName->AddFlag(ImGuiInputTextFlags_ReadOnly);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* Button = CreateWidget<CEditorButton>("이미지 적용", 150.f, 30.f);

    Button->SetColor(29, 47, 73, 255);
    Button->SetClickCallback<CMyImageWindow>(this, &CMyImageWindow::ImageSetButtonCallback);

    CEditorLabel* Label2 = CreateWidget<CEditorLabel>("선택한 컴포넌트");

    Label2->SetColor(255, 0, 0, 255);
    Label2->SetAlign(0.5f, 0.5f);
    Label2->SetSize(120.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_SelectComponentName = CreateWidget<CEditorInput>("SelectedComponent");
    m_SelectComponentName->SetHideName("SelectedComponent");
    m_SelectComponentName->SetSize(350.f, 30.f);
    m_SelectComponentName->AddFlag(ImGuiInputTextFlags_ReadOnly);

    //이미지 리스트
    m_ImageList = CreateWidget<CEditorListBox>("ImageListBox");
    m_ImageList->SetHideName("ImageListBox");
    m_ImageList->SetSize(200.f, 200.f);
    m_ImageList->SetPageItemCount(10);

    m_ImageList->SetSelectCallback<CMyImageWindow>(this, &CMyImageWindow::SelectImageCallback);

    Line = CreateWidget<CEditorSameLine>("Line");
    
    //우측에 선택한 이미지를 보여준다.
    m_SelectImageView = CreateWidget<CEditorImage>("Image");
    m_SelectImageView->SetSize(200.f, 200.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_LoadSpriteImageView = CreateWidget<CEditorImage>("SeeSpriteImage");
    m_LoadSpriteImageView->SetSize(150.f, 150.f);

    CEditorLabel* Label3 = CreateWidget<CEditorLabel>("Material 적용");
    Label3->SetColor(50, 50, 50, 255);
    Label3->SetAlign(0.5f, 0.5f);
    Label3->SetSize(120.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorLabel* LabelR = CreateWidget<CEditorLabel>("R");
    LabelR->SetColor(255, 0, 0, 255);
    LabelR->SetAlign(0.5f, 0.5f);
    LabelR->SetSize(70.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorLabel* LabelG = CreateWidget<CEditorLabel>("G");
    LabelG->SetColor(0, 255, 0, 255);
    LabelG->SetAlign(0.5f, 0.5f);
    LabelG->SetSize(70.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorLabel* LabelB = CreateWidget<CEditorLabel>("B");
    LabelB->SetColor(0, 0, 255, 255);
    LabelB->SetAlign(0.5f, 0.5f);
    LabelB->SetSize(70.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorLabel* LabelA = CreateWidget<CEditorLabel>("A");
    LabelA->SetColor(50, 50, 50, 255);
    LabelA->SetAlign(0.5f, 0.5f);
    LabelA->SetSize(70.f, 30.f);

    CEditorButton* Button2 = CreateWidget<CEditorButton>("색 적용", 120.f, 30.f);

    Button2->SetColor(50, 50, 50, 255);
    Button2->SetClickCallback<CMyImageWindow>(this, &CMyImageWindow::MaterialSetButtonCallback);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_RGBA[0] = CreateWidget<CEditorInput>("MtR", 70.f, 30.f);
    m_RGBA[0]->SetHideName("MtR");
    m_RGBA[0]->SetInputType(EImGuiInputType::Float);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_RGBA[1] = CreateWidget<CEditorInput>("MtG", 70.f, 30.f);
    m_RGBA[1]->SetHideName("MtG");
    m_RGBA[1]->SetInputType(EImGuiInputType::Float);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_RGBA[2] = CreateWidget<CEditorInput>("MtB", 70.f, 30.f);
    m_RGBA[2]->SetHideName("MtB");
    m_RGBA[2]->SetInputType(EImGuiInputType::Float);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_RGBA[3] = CreateWidget<CEditorInput>("MtA", 70.f, 30.f);
    m_RGBA[3]->SetHideName("MtA");
    m_RGBA[3]->SetInputType(EImGuiInputType::Float);


    LoadImageName();

    return true;
}

void CMyImageWindow::Update(float DeltaTime)
{
    CEditorWindow::Update(DeltaTime);
}

void CMyImageWindow::SelectImageCallback(int Index, const std::string& Item)
{
    m_SelectImageItem = Item;

    m_SelectImageName->SetText(Item.c_str());

    //선택한 파일 이름 저장
    char Text[256] = {};
    sprintf_s(Text, "%s", Item.c_str());


    TCHAR Unicode[256] = {};
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Text, (int)strlen(Text), Unicode, 256);

    m_SelectImageView->SetTexture(Item, Unicode);
}

void CMyImageWindow::ImageSetButtonCallback()
{
    //선택한 파일 이름 저장
    char Text[256] = {};
    sprintf_s(Text, "%s", m_SelectImageItem.c_str());

    TCHAR Unicode[256] = {};
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, Text, (int)strlen(Text), Unicode, 256);


    //선택한 컴포넌트에 이미지 적용
    ((CSpriteComponent*)m_SelectComponent.Get())->SetTexture(m_SelectImageItem, Unicode);

    //로딩이미지에도 적용
    m_LoadSpriteImageView->SetTexture(m_SelectImageItem, Unicode);
}

void CMyImageWindow::MaterialSetButtonCallback()
{
    int arr[4] = {};

    arr[0] = (int)m_RGBA[0]->GetFloat();
    arr[1] = (int)m_RGBA[1]->GetFloat();
    arr[2] = (int)m_RGBA[2]->GetFloat();
    arr[3] = (int)m_RGBA[3]->GetFloat();

    if((CSpriteComponent*)m_SelectComponent.Get())
        ((CSpriteComponent*)m_SelectComponent.Get())->GetMaterial(0)->SetBaseColorUnsignedChar(arr[0], arr[1], arr[2], arr[3]);
    
}

void CMyImageWindow::LoadImageName()
{
    //Texture 폴더에 있는 파일 이름들 다 긁어와서 리스트에 넣어줌
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char Path[MAX_PATH] = {};

    strcpy_s(Path, Info->PathMultibyte);
    strcat_s(Path, "Texture/");

    for (const auto& file : std::filesystem::directory_iterator(Path))
    {
        char Name[64] = {};
        char FullPath[MAX_PATH] = {};
        char Ext[_MAX_EXT] = {};

        strcpy_s(FullPath, file.path().generic_string().c_str());
        _splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

        char ImageFileName[256] = {};
        strcpy_s(ImageFileName, Name);
        strcat_s(ImageFileName, Ext);

        m_ImageList->AddItem(ImageFileName);
    }
}
