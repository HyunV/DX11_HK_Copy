#include "EditorManager.h"
#include "Scene/EditorDefaultScene.h"
#include "Scene/SceneManager.h"
#include "Window\TestWindow.h"
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
    //클라이언트 매니저가 작동하는 방식이랑 같음

    //에디터 모드 켜주기
    CEngine::GetInst()->EnableEditor();

    if (!CEngine::GetInst()->Init(hInst, TEXT("Editor"), TEXT("Editor"), IDI_ICON1,
        IDI_ICON1, 1280, 720, 1920, 1080, true))
    {
        return false;
    }

    //테스트 윈도우 클래스로 창을 띄움
    CEditorGUIManager::GetInst()->CreateEditorWindow<CTestWindow>("TestWindow");
    

    // 키 등록
/*CInput::GetInst()->AddBindKey("Rotation", 'D');
CInput::GetInst()->AddBindKey("RotationInv", 'A');

CInput::GetInst()->AddBindKey("MoveUp", 'W');
CInput::GetInst()->AddBindKey("MoveDown", 'S');

CInput::GetInst()->AddBindKey("Fire", VK_SPACE);*/


    // SceneInfo 생성 기본적으로 사용할 씬 등록
    CSceneManager::GetInst()->CreateSceneInfo<CEditorDefaultScene>();

    return true;
}

int CEditorManager::Run()
{
    return CEngine::GetInst()->Run();
}
