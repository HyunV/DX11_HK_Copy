#include "EditorManager.h"
#include "Scene/EditorDefaultScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Editor/EditorGUIManager.h"
#include "GameObject\Player2D.h"
#include "GameObject\MyBullet.h"
#include "GameObject\Monster.h"

#include "Window\TestWindow.h"
#include "Window\ObjectWindow.h"
#include "Window\ClassWindow.h"
#include "Window\ComponentWindow.h"
#include "Window\TransformWindow.h"
#include "Window\SceneWindow.h"
#include "Window\DetailWindow.h"
#include "Window\MyImageWindow.h"
#include "Window\MyAnimationWindow.h"
#include "Window\NMyAnimationWindow2.h"
#include "Editor/EditorGUIManager.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "PathManager.h"

CEditorManager::CEditorManager()
{
}

CEditorManager::~CEditorManager()
{
    CEngine::DestroyInst();
}

bool CEditorManager::Init(HINSTANCE hInst)
{
    //Ŭ���̾�Ʈ �Ŵ����� �۵��ϴ� ����̶� ����

    //������ ��� ���ֱ�
    CEngine::GetInst()->EnableEditor();

    if (!CEngine::GetInst()->Init(hInst, TEXT("Editor"), TEXT("Editor"), IDI_ICON1,
        IDI_ICON1, 1280, 720, 1280, 720, true, IDR_MENU1))
    {
        return false;
    }

    LoadResource();

    CreateCDO();

    //�׽�Ʈ ������ Ŭ������ â�� ���
    CEngine::SetWndProcCallback<CEditorManager>(this, &CEditorManager::WndProc);

    //#���� ���# �׽�Ʈ ������ ���� (Ƽ��?)
    CEditorGUIManager::GetInst()->CreateEditorWindow<CTestWindow>("TestWindow");
    
    //#���� ���# ������Ʈ ������ ����
    CEditorGUIManager::GetInst()->CreateEditorWindow<CObjectWindow>("ObjectWindow"); 

    //#���� ���#  Ŭ���� ������ ����
    CEditorGUIManager::GetInst()->CreateEditorWindow<CClassWindow>("ClassWindow");
    
    //#���� ���#  ������Ʈ ������
    CEditorGUIManager::GetInst()->CreateEditorWindow<CComponentWindow>("ComponentWindow");

    //#���� ���# Ʈ������ ������
    CEditorGUIManager::GetInst()->CreateEditorWindow<CTransformWindow>("TransformWindow");

    //#���� ���# �� ������
    CEditorGUIManager::GetInst()->CreateEditorWindow<CSceneWindow>("SceneWindow");

    //#���� ���# ������ ������
    CEditorGUIManager::GetInst()->CreateEditorWindow<CDetailWindow>("DetailWindow");

    //#����# �̹��� ������
    CEditorGUIManager::GetInst()->CreateEditorWindow<CMyImageWindow>("MyImageWindow");

    //#����# ������ ������, �ִϸ��̼� ������
    CEditorGUIManager::GetInst()->CreateEditorWindow<CMyAnimationWindow>("MyAnimationWindow");
    CEditorGUIManager::GetInst()->CreateEditorWindow<CNMyAnimationWindow2>("NMyAnimationWindow2");
    
    // Ű ���
    /*CInput::GetInst()->AddBindKey("Rotation", 'D');
    CInput::GetInst()->AddBindKey("RotationInv", 'A');

    CInput::GetInst()->AddBindKey("MoveUp", 'W');
    CInput::GetInst()->AddBindKey("MoveDown", 'S');

    CInput::GetInst()->AddBindKey("Fire", VK_SPACE);*/


    // SceneInfo ���� �⺻������ ����� �� ���
    CSceneManager::GetInst()->CreateSceneInfo<CEditorDefaultScene>();

    return true;
}

int CEditorManager::Run()
{
    return CEngine::GetInst()->Run();
}

bool CEditorManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case ID_FILE_SCENE_SAVE:
            //MessageBox(hWnd, TEXT("Empty"), TEXT("Empty"), MB_OK);
            SaveScene();
            return true;
        case ID_FILE_SCENE_OPEN:
            OpenScene();
            return true;
        case ID_FILE_EXIT:
            DestroyWindow(hWnd);
            return true;
        case ID_OBJECT_EMPTY:
            CreateEmptyObject();
            return true;
        case ID_OBJECT:
            CreateObject();
            return true;
        case ID_WINDOW_TEST:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("TestWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_OBJECT:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ObjectWindow");

            if (Window)
                Window->Open();
        }
        return true;

        case ID_WINDOW_CLASS:
        {
            //MessageBox(hWnd, TEXT("Ŭ����"), TEXT("Empty"), MB_OK);
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ClassWindow");

            if (Window)
                Window->Open();            
        }
        return true;
        case ID_WINDOW_COMPONENT:
        {
            //MessageBox(hWnd, TEXT("������Ʈ"), TEXT("Empty"), MB_OK);
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ComponentWindow");

            if (Window)
                Window->Open();            
        }
        return true;
        //���̽��� ��
        }
        break;
    
    }

    return false;
}

void CEditorManager::SaveScene()
{
}

void CEditorManager::OpenScene()
{
}

void CEditorManager::CreateEmptyObject()
{
    //�� �ҷ�����
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    //�� ������Ʈ ����
    CGameObject* EmptyObj = Scene->CreateObject<CGameObject>("GameObjectEmpty");


    CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

    if (Window)
    {
        Window->AddItem(EmptyObj, "GameObjectEmpty");
    }
}

void CEditorManager::CreateObject()
{
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    CGameObject* Obj = nullptr;

    CClassWindow* ClassWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CClassWindow>("ClassWindow");
    
    //Ŭ���� �����쿡�� ������ ������Ʈ�� �̸��� �޾ƿ´�.
    std::string SelectObjectItem = ClassWindow->GetSelectObjectItem();
    
    if (SelectObjectItem == "") //������Ʈ ������ ��������
        return;

    //������Ʈ ���� �Ǿ��� �� ������Ʈ �����츦 �����.
    CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

    //�� ������Ʈ ���� ����°͵��� ����� ����� �ϴ°ǰ� �������� ����ϱ� CDO������ ���� ����Ѵ�.
    if (SelectObjectItem == "GameObject")
        Obj = Scene->CreateObject<CGameObject>(SelectObjectItem); //Ŭ���� �����쿡�� ������ ������Ʈ�� �ش� ������ ����?

    else if(SelectObjectItem == "Player2D")
        Obj = Scene->CreateObject<CPlayer2D>(SelectObjectItem);

    else if (SelectObjectItem == "MyBullet")
        Obj = Scene->CreateObject<CMyBullet>(SelectObjectItem);

    else if (SelectObjectItem == "Monster")
        Obj = Scene->CreateObject<CMonster>(SelectObjectItem);

    if (Window)
    {
        Window->AddItem(Obj, SelectObjectItem); //������Ʈ �����쿡 ����� �߰���
        //Ʈ���� �ش� ������Ʈ�� ����ְ� �ȴ�.
    }

}

void CEditorManager::CreateCDO()
{
    CSceneInfo* Info = new CEditorDefaultScene;

    CScene::AddSceneInfoCDO("EditorDefaultScene", Info);

    CScene::CreateObjectCDO<CPlayer2D>("Player2D");
    CScene::CreateObjectCDO<CMonster>("Monster");
    CScene::CreateObjectCDO<CMyBullet>("MyBullet");
}

void CEditorManager::LoadResource()
{
    //128 128
    CResourceManager::GetInst()->CreateAnimationSequence2D(
        "PlayerIdle", "PlayerSprite", TEXT("Player.png"));

    //�÷��̾� ����� ���� ������ ������ �ִϸ��̼� ó��
    for (int i = 0; i < 14; ++i)
    {
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerIdle",
            Vector2(i * 45.f, 60.f), Vector2((i + 1) * 45.f, 120.f));
    }

 
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char FullPath[MAX_PATH] = {};

    if (Info)
        strcpy_s(FullPath, Info->PathMultibyte);

    strcat_s(FullPath, "Sequence/");

    //������ ���� �� �ִ� ��� ���� �ε�
    for (const auto& file : std::filesystem::directory_iterator(FullPath))
    {
        char FileName[64] = {};
        char MaxPath[MAX_PATH] = {};
        char Ext[_MAX_EXT] = {};

        strcpy_s(MaxPath, file.path().generic_string().c_str());
        _splitpath_s(MaxPath, nullptr, 0, nullptr, 0, FileName, 64, Ext, _MAX_EXT);

        CResourceManager::GetInst()->CreateAnimationSequence2D(FileName, nullptr);
        CResourceManager::GetInst()->FindAnimationSequence2D(FileName)->Load(MaxPath);
    }



    //������� �̹����� ó��
    std::vector<const TCHAR*>   vecFileName;

    for (int i = 1; i <= 89; ++i)
    {
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

        wsprintf(FileName, TEXT("Explosion/Explosion%d.png"), i);

        vecFileName.push_back(FileName);
    }

    vecFileName;

    CResourceManager::GetInst()->CreateAnimationSequence2D(
        "PlayerRun", "Explosion", vecFileName);

    CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("PlayerRun",
        89, Vector2(0.f, 0.f), Vector2(320.f, 240.f));

    for (int i = 0; i <= 88; ++i)
    {
        SAFE_DELETE_ARRAY(vecFileName[i]);
    }

    vecFileName.clear();
}
