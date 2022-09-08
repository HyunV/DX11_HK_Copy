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
#include "PathManager.h"

CClassWindow::CClassWindow()
{
}

CClassWindow::~CClassWindow()
{
}

bool CClassWindow::Init()
{
    //꾸미기 라벨
    CEditorLabel* Label = CreateWidget<CEditorLabel>("ObjectClass");

    Label->SetColor(255, 0, 0, 255);
    Label->SetAlign(0.5f, 0.5f);
    Label->SetSizeY(30.f);
    //

    m_ObjectList = CreateWidget<CEditorListBox>("ObjectListBox");
    
    m_ObjectList->SetHideName("ObjectListBox");

    m_ObjectList->SetSize(200.f, 300.f);
    m_ObjectList->SetPageItemCount(6);

    Label = CreateWidget<CEditorLabel>("ComponentClass");

    Label->SetColor(255, 0, 0, 255);
    Label->SetAlign(0.5f, 0.5f);
    Label->SetSizeY(30.f);
    Label->SetSizeX(150.f);

    m_ObjectList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ObjectClickCallback);
    
    m_ComponentList = CreateWidget<CEditorListBox>("ComponentListBox");

    m_ComponentList->SetHideName("ComponentListBox");

    m_ComponentList->SetSize(200.f, 300.f);
    m_ComponentList->SetPageItemCount(6);

    m_ComponentList->SetSelectCallback<CClassWindow>(this, &CClassWindow::ComponentClickCallback);

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
}

void CClassWindow::ComponentClickCallback(int Index, const std::string& Item)
{
    m_SelectComponentItem = Item;
}

void CClassWindow::LoadGameObjectName()
{
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char Path[MAX_PATH] = {};

    strcpy_s(Path, Info->PathMultibyte);

    int Length = (int)strlen(Path);

    // Root Path에서 Bin\을 지워준다.
    for (int i = Length - 2; i >= 0; --i)
    {
        if (Path[i] == '/' || Path[i] == '\\')
        {
            memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
            break;
        }
    }

    char    Directory[MAX_PATH] = {};

    strcpy_s(Directory, Path);

    // Editor의 GameObject폴더에 있는 파일을 읽어온다.
    strcat_s(Directory, "Include/GameObject/");

    for (const auto& file : std::filesystem::directory_iterator(Directory))
    {
        char Name[64] = {};
        char FullPath[MAX_PATH] = {};
        char Ext[_MAX_EXT] = {};

        strcpy_s(FullPath, file.path().generic_string().c_str());

        _splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

        if (strcmp(Ext, ".cpp") == 0)
            continue;

        m_ObjectList->AddItem(Name);
    }

    Length = (int)strlen(Path);

    // Root Path에서 Bin\을 지워준다.
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

    // Editor의 GameObject폴더에 있는 파일을 읽어온다.
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

    // Root Path에서 Bin\을 지워준다.
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

    // Editor의 Component폴더에 있는 파일을 읽어온다.
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

    // Root Path에서 Bin\을 지워준다.
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

    // Editor의 GameObject폴더에 있는 파일을 읽어온다.
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

        else if (strcmp(Name, "Transform") == 0 || strcmp(Name, "Transform2D") == 0)
            continue;

        m_ComponentList->AddItem(Name);
    }
}
