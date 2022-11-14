#include "ClassWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorGroup.h"
#include "PathManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameObject\Player2D.h"
#include "../GameObject\MyBullet.h"
#include "../GameObject\Monster.h"
#include "ObjectWindow.h"
#include "ComponentWindow.h"
#include "Editor/EditorGUIManager.h"

#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderPixel.h"

#include "Component/TileMapComponent.h"

#include "Engine.h"

#include <time.h>

CClassWindow::CClassWindow()
{
}

CClassWindow::~CClassWindow()
{
}

bool CClassWindow::Init()
{
    //�ٹ̱� ��
    CEditorLabel* Label = CreateWidget<CEditorLabel>("ObjectClass");

    Label->SetColor(255, 0, 0, 255);
    Label->SetAlign(0.5f, 0.5f);
    Label->SetSizeY(30.f);

    CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* Button = CreateWidget<CEditorButton>("������Ʈ ����", 150.f, 30.f);

    Button->SetColor(29, 47, 73, 255);
    Button->SetClickCallback<CClassWindow>(this, &CClassWindow::ObjectCreateCallback);
    //

    m_ObjectList = CreateWidget<CEditorListBox>("ObjectListBox");
    
    m_ObjectList->SetHideName("ObjectListBox");

    m_ObjectList->SetSize(200.f, 300.f);
    m_ObjectList->SetPageItemCount(6);

    //������ � ������Ʈ�� �����ߴ��� �����ش�.
    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorGroup* Group = CreateWidget<CEditorGroup>("Group");

    m_ObjectSelectName = Group->CreateWidget<CEditorInput>("ObjectName");

    m_ObjectSelectName->SetHideName("ObjectName");
    m_ObjectSelectName->SetSize(150.f, 30.f);
    m_ObjectSelectName->AddFlag(ImGuiInputTextFlags_ReadOnly);

    m_NumberingCount = Group->CreateWidget<CEditorInput>("NumberingCount");
    m_NumberingCount->SetHideName("NumberingCount");
    m_NumberingCount->SetInputType(EImGuiInputType::Int);

    Label = CreateWidget<CEditorLabel>("ComponentClass");

    Label->SetColor(255, 0, 0, 255);
    Label->SetAlign(0.5f, 0.5f);
    Label->SetSizeY(30.f);
    Label->SetSizeX(150.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    Button = CreateWidget<CEditorButton>("������Ʈ����", 150.f, 30.f);

    Button->SetColor(29, 47, 73, 255);
    Button->SetClickCallback<CClassWindow>(this, &CClassWindow::ComponentCreateCallback);

    m_ObjectList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ObjectClickCallback);
    
    m_ComponentList = CreateWidget<CEditorListBox>("ComponentListBox");

    m_ComponentList->SetHideName("ComponentListBox");

    m_ComponentList->SetSize(200.f, 300.f);
    m_ComponentList->SetPageItemCount(6);

    m_ComponentList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ComponentClickCallback);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_ComponentSelectName = CreateWidget<CEditorInput>("ComponentName");

    m_ComponentSelectName->SetHideName("ComponentName");
    m_ComponentSelectName->SetSize(150.f, 30.f);
    m_ComponentSelectName->AddFlag(ImGuiInputTextFlags_ReadOnly);

    LoadGameObjectName();

    LoadComponentName();

    return true;
}

void CClassWindow::Update(float DeltaTime)
{
    CEditorWindow::Update(DeltaTime);
}

void CClassWindow::ObjectClickCallback(int Index, const std::string& Item)
{
    m_SelectObjectItem = Item;

    m_ObjectSelectName->SetText(Item.c_str());
}

void CClassWindow::ComponentClickCallback(int Index, const std::string& Item)
{
    m_SelectComponentItem = Item;

    m_ComponentSelectName->SetText(Item.c_str());
}

void CClassWindow::ObjectCreateCallback()
{
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    CGameObject* Obj = nullptr;

    if (m_SelectObjectItem == "")
        return;


    //===================================������Ʈ ���� �ݹ�=======================================
    CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");
    int ObjectNumber = 0;
    
    std::string strNum = std::to_string(ObjectNumber);
    if (ObjectNumber == 0)
        strNum = "";

    std::string FinalName = "";
    while (Scene->FindObject(m_SelectObjectItem + strNum))
    {
        ObjectNumber++;
        strNum = std::to_string(ObjectNumber);
    }

    if (m_SelectObjectItem == "GameObject")
        Obj = Scene->CreateObject<CGameObject>(m_SelectObjectItem+strNum);

    else if (m_SelectObjectItem == "Player2D")
        Obj = Scene->CreateObject<CPlayer2D>(m_SelectObjectItem+strNum);

    else if (m_SelectObjectItem == "MyBullet")
        Obj = Scene->CreateObject<CMyBullet>(m_SelectObjectItem+strNum);

    else if (m_SelectObjectItem == "Monster")
        Obj = Scene->CreateObject<CMonster>(m_SelectObjectItem+strNum);

    if (Window)
    {
        Window->AddItem(Obj, m_SelectObjectItem+strNum);
    }

    //if (ObjectNumber != 0)
    //    m_NumberingCount->SetInt(m_NumberingCount->GetInt() + 1);
    //===================================================================
    //MakeObject();
}

void CClassWindow::ComponentCreateCallback()
{
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    CObjectWindow* ObjectWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");
    CComponentWindow* ComponentWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CComponentWindow>("ComponentWindow");

    //������ ������Ʈ�� ������Ʈ �����쿡 ������
    CGameObject* SelectObject = ObjectWindow->GetSelectObject(); 

    if (!SelectObject)
        return;

    //������ ������Ʈ�� ������
    CSceneComponent* SelectComponent = (CSceneComponent*)ComponentWindow->GetSelectComponent();

    if (!SelectComponent)
    {
        SelectComponent = SelectObject->GetRootComponent();
    }

    std::string Name;

    //���ο� �� ���� ����
    CSceneComponent* NewComponent = nullptr;
    

    //## (������Ʈ �߰�)������Ʈ ������ ���� �߰�����
    if (m_SelectComponentItem == "SpriteComponent")
    {
        Name = "SpriteComponent(SpriteComponent)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CSpriteComponent>("SpriteComponent");
              
    }

    else if (m_SelectComponentItem == "SceneComponent")
    {
        Name = "SceneComponent(SceneComponent)";
        NewComponent = SelectObject->CreateComponent<CSceneComponent>("SceneComponent");
    }
    else if (m_SelectComponentItem == "TargetArm")
    {
        Name = "TargetArm(TargetArm)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CTargetArm>("TargetArm");
    }
    else if (m_SelectComponentItem == "CameraComponent")
    {
        Name = "CameraComponent(CameraComponent)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CCameraComponent>("CameraComponent");
    }
    else if (m_SelectComponentItem == "ColliderBox2D")
    {
        Name = "ColliderComponent(ColliderBox2D)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderBox2D>("ColliderBox2D");
        NewComponent->SetScene(CSceneManager::GetInst()->GetScene());
    }
    else if (m_SelectComponentItem == "ColliderOBB2D")
    {
        Name = "ColliderComponent(ColliderOBB2D)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderOBB2D>("ColliderOBB2D");
    }
    else if (m_SelectComponentItem == "ColliderSphere2D")
    {
        Name = "ColliderComponent(ColliderSphere2D)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderSphere2D>("ColliderSphere2D");
    }
    else if (m_SelectComponentItem == "ColliderPixel")
    {
        Name = "ColliderComponent(ColliderPixel)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CColliderPixel>("ColliderPixel");

        OPENFILENAME	ofn = {};

        TCHAR	FullPath[MAX_PATH] = {};

        TCHAR	Filter[] = TEXT("��� ����\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
        ofn.lpstrFilter = Filter;
        ofn.lpstrFile = FullPath;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

        if (GetOpenFileName(&ofn) != 0)
        {
            ((CColliderPixel*)NewComponent)->SetInfoFullPath("test", FullPath);
        }        
    }
    else if (m_SelectComponentItem == "TileMapComponent")
    {
        Name = "TileMapComponent(TileMapComponent)";
        NewComponent = (CSceneComponent*)SelectObject->CreateComponent<CTileMapComponent>("TileMapComponent");
    }


    //�����ߴ� ������Ʈ ���� ���� ������Ʈ �߰�
    if (SelectComponent)
    {
        std::string	ParentName = SelectComponent->GetName() + "(" + SelectComponent->GetComponentTypeName() + ")";

        SelectComponent->AddChild(NewComponent);
        NewComponent->Start();

        //������Ʈ �����쿡�� �߰�
        ComponentWindow->AddItem((CComponent*)NewComponent, Name, ParentName);
    }
    else
    {
        std::string	ObjName = SelectObject->GetName() + "(" + SelectObject->GetObjectTypeName() + ")";

        ComponentWindow->AddItem((CComponent*)NewComponent, Name, ObjName);
    }

}


void CClassWindow::LoadGameObjectName()
{
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH); //~Bin ��������

    char Path[MAX_PATH] = {};

    strcpy_s(Path, Info->PathMultibyte); //��Ʈ�н� ��θ� ������ �´�.(Editor/Bin)
    
    int Length = (int)strlen(Path); //��� ������ ���� (�������� \0����)
    

    //#### MapEditor ���� ���ӿ�����Ʈ �̸��� ��������#####################################################
    
    //��Ʈ�н� ��� �������� Bin\ �̰� ������� �Ѵ�. (4��)
    for (int i = Length - 2; i >= 0; --i)
    {
        if (Path[i] == '/' || Path[i] == '\\') //��ο� /�� \\�� ���������
        {
            //�� ���ڿ� ���� 0���� �ʱ�ȭ���ش�. ���� Bin\�� ����� ���� ����          
            memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
            break;
        }
    }

    char    Directory[MAX_PATH] = {}; 

    strcpy_s(Directory, Path); //~MapEditor �����̸������ �����ؿ�������

    // Editor�� GameObject������ �ִ� ������ �о�´�.
    strcat_s(Directory, "Include/GameObject/");

    for (const auto& file : std::filesystem::directory_iterator(Directory))
        //directory_iterator(Directory) �� ��� �ȿ� �ִ� �̸����� file�� �־� �� ���� �� �� �ְ� ���ش�.
        //�� ���ϴ� ���� �ȿ� �ִ� ���� �̸����� �� �� �ܾ�� ���ִ�.

    {
        char Name[64] = {}; //���� �̸�
        char FullPath[MAX_PATH] = {}; //���� ���
        char Ext[_MAX_EXT] = {}; //Ȯ���� 

        //���� file�� �Ϲ� ���ڿ��� �ƴ϶� generic_string�� �̾ƿͼ� �Ϲ� ���ڿ�(c_str)�� �ٲ���� �Ѵ�.
        strcpy_s(FullPath, file.path().generic_string().c_str());
        
        //�޾ƿ� Ǯ�н� ��θ� Ǯ�н�, �̸�, Ȯ���ڷ� �и��ؼ� �־���
        _splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);
                                                       //�����̸�, ����, Ȯ����, ����

        if (strcmp(Ext, ".cpp") == 0) //Ȯ���ڰ� .cpp�� �ǳʶ�
            continue;

        m_ObjectList->AddItem(Name);
    }

    //#### Engine ���� ���ӿ�����Ʈ �̸��� ��������#################################################
    Length = (int)strlen(Path);

    // Root Path���� Bin\�� �����ش�.
    for (int i = Length - 2; i >= 0; --i)
    {
        if (Path[i] == '/' || Path[i] == '\\')
        {
            memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
            break;
        }
    }

    memset(Directory, 0, MAX_PATH);
    strcpy_s(Directory, Path);

    // Editor�� GameObject������ �ִ� ������ �о�´�.
    strcat_s(Directory, "Engine/Include/GameObject/");

    for (const auto&file : std::filesystem::directory_iterator(Directory))
    {
        char    Name[64] = {};
        char    FullPath[MAX_PATH] = {};
        char    Ext[_MAX_EXT] = {};

        strcpy_s(FullPath, file.path().generic_string().c_str());

        _splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

        if (strcmp(Ext, ".cpp") == 0)
            continue;

        m_ObjectList->AddItem(Name);
    }
}

void CClassWindow::LoadComponentName()
{
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char	Path[MAX_PATH] = {};

    strcpy_s(Path, Info->PathMultibyte);

    int	Length = (int)strlen(Path);

    // Root Path���� Bin\�� �����ش�.
    for (int i = Length - 2; i >= 0; --i)
    {
        if (Path[i] == '/' || Path[i] == '\\')
        {
            memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
            break;
        }
    }

    char	Directory[MAX_PATH] = {};

    strcpy_s(Directory, Path);

    // Editor�� Component������ �ִ� ������ �о�´�.
    strcat_s(Directory, "Include/Component/");

    for (const auto& file : std::filesystem::directory_iterator(Directory))
    {
        char	Name[64] = {};
        char	FullPath[MAX_PATH] = {};
        char	Ext[_MAX_EXT] = {};

        strcpy_s(FullPath, file.path().generic_string().c_str());

        _splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

        if (strcmp(Ext, ".cpp") == 0)
            continue;

        m_ComponentList->AddItem(Name);
    }

    Length = (int)strlen(Path);

    // Root Path���� Bin\�� �����ش�.
    for (int i = Length - 2; i >= 0; --i)
    {
        if (Path[i] == '/' || Path[i] == '\\')
        {
            memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
            break;
        }
    }

    memset(Directory, 0, MAX_PATH);
    strcpy_s(Directory, Path);

    // Editor�� GameObject������ �ִ� ������ �о�´�.
    strcat_s(Directory, "Engine/Include/Component/");

    for (const auto& file : std::filesystem::directory_iterator(Directory))
    {
        char	Name[64] = {};
        char	FullPath[MAX_PATH] = {};
        char	Ext[_MAX_EXT] = {};

        strcpy_s(FullPath, file.path().generic_string().c_str());

        _splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

        if (strcmp(Ext, ".cpp") == 0)
            continue;

        //Ʈ������ ������Ʈ�� ���ܷ� ���ֱ�
        else if (strcmp(Name, "Transform") == 0 ||
            strcmp(Name, "Transform2D") == 0 ||
            strcmp(Name, "Component") == 0 ||
            strcmp(Name, "PrimitiveComponent") == 0||
            strcmp(Name, "ObjectComponent") == 0||
            strcmp(Name, "Collider") == 0 ||
            strcmp(Name, "Collider2D") == 0 ||
            strcmp(Name, "Collider3D") == 0||
            strcmp(Name, "Tile") == 0)
            continue;

        m_ComponentList->AddItem(Name);
    }
}

void CClassWindow::MakeObject()
{
    CScene* Scene = CSceneManager::GetInst()->GetScene();
    CGameObject* Obj = nullptr;
    CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");
    
    srand((unsigned int)time(0));

    for (int i = 0; i < 100; i++)
    {
        Obj = Scene->CreateObject<CPlayer2D>(m_SelectObjectItem);
        Obj->SetWorldPosition((float)(rand() %1280), (float)(rand() % 720));
        //Obj->SetRelativePosition(500, 200);

        if (Window)
        {
            Window->AddItem(Obj, m_SelectObjectItem);
        }
    }


}
