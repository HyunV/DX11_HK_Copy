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
#include "Editor/EditorGUIManager.h"

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

    //�׽�Ʈ ������ Ŭ������ â�� ���
    CEngine::SetWndProcCallback<CEditorManager>(this, &CEditorManager::WndProc);

    //�׽�Ʈ ������ ���� (Ƽ��?)
    //CEditorGUIManager::GetInst()->CreateEditorWindow<CTestWindow>("TestWindow");
    
    //������Ʈ ������ ����
    CEditorGUIManager::GetInst()->CreateEditorWindow<CObjectWindow>("ObjectWindow"); 

    //Ŭ���� ������ ����
    CEditorGUIManager::GetInst()->CreateEditorWindow<CClassWindow>("ClassWindow");
    

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
            //CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("TestWindow");

            //if (Window)
            //    Window->Open();
        }
        return true;
        case ID_WINDOW_OBJECT:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ObjectWindow");

            if (Window)
                Window->Open();
        }
        return true;
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
        Window->AddItem("GameObjectEmpty");
    }
}

void CEditorManager::CreateObject()
{
}
