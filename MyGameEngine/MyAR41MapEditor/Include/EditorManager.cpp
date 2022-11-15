#include "EditorManager.h"
#include "Scene/EditorDefaultScene.h"
#include "Scene/EditorTestScene.h"

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
#include "Window\MySequenceWindow.h"
#include "Window\MyAnimationWindow.h"
//#include "Window\NMyAnimationWindow2.h"
#include "Window\SectionWindow.h"

#include "Editor/EditorGUIManager.h"
#include "Resource/Animation/AnimationSequence2D.h"

#include "Input.h"
#include "CollisionManager.h"

#include "Setting/EngineShareSetting.h"



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

    if (!CEngine::GetInst()->Init(hInst, TEXT("Editor"), TEXT("Editor"), IDI_ICON2,
        IDI_ICON2, 1280, 720, 1280, 720, true, IDI_ICON2))
    {
        return false;
    }

    CSceneInfo* Info = new CEditorDefaultScene;

    CScene::AddSceneInfoCDO("EditorDefaultScene", Info);

    //========내 코드===========================================
    //CSceneInfo* TestSceneInfo = new CEditorTestScene;

    //CScene::AddSceneInfoCDO("EditorTestScene", TestSceneInfo);
    //==========================================================

    CEngineShareSetting::Setting();

    //테스트 윈도우 클래스로 창을 띄움
    CEngine::SetWndProcCallback<CEditorManager>(this, &CEditorManager::WndProc);

    //#예제 출력# 테스트 윈도우 생성 (티모?)
    //CEditorGUIManager::GetInst()->CreateEditorWindow<CTestWindow>("TestWindow");
    
    //#예제 출력# 오브젝트 윈도우 생성
    CEditorGUIManager::GetInst()->CreateEditorWindow<CObjectWindow>("ObjectWindow"); 

    //#예제 출력#  클래스 윈도우 생성
    CEditorGUIManager::GetInst()->CreateEditorWindow<CClassWindow>("ClassWindow");
    
    //#예제 출력#  컴포넌트 윈도우
    CEditorGUIManager::GetInst()->CreateEditorWindow<CComponentWindow>("ComponentWindow");

    //#예제 출력# 트랜스폼 윈도우
    CEditorGUIManager::GetInst()->CreateEditorWindow<CTransformWindow>("TransformWindow");

    //#예제 출력# 씬 윈도우
    CEditorGUIManager::GetInst()->CreateEditorWindow<CSceneWindow>("SceneWindow");

    //#예제 출력# 디테일 윈도우
    CEditorGUIManager::GetInst()->CreateEditorWindow<CDetailWindow>("DetailWindow");

    //#과제# 이미지 윈도우
    //CEditorGUIManager::GetInst()->CreateEditorWindow<CMyImageWindow>("MyImageWindow");

    //#과제# 시퀀스 윈도우, 애니메이션 윈도우   
    CEditorGUIManager::GetInst()->CreateEditorWindow<CMySequenceWindow>("MySequenceWindow");

    CEditorGUIManager::GetInst()->CreateEditorWindow<CMyAnimationWindow>("MyAnimationWindow");
    //CEditorGUIManager::GetInst()->CreateEditorWindow<CNMyAnimationWindow2>("NMyAnimationWindow2");


    // SceneInfo 생성 기본적으로 사용할 씬 등록
    CSceneManager::GetInst()->CreateSceneInfo<CEditorDefaultScene>();

    //CSceneManager::GetInst()->CreateSceneInfo<CEditorTestScene>();


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
            //MessageBox(hWnd, TEXT("클래스"), TEXT("Empty"), MB_OK);
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ClassWindow");

            if (Window)
                Window->Open();            
        }
        return true;
        case ID_WINDOW_COMPONENT:
        {
            //MessageBox(hWnd, TEXT("컴포넌트"), TEXT("Empty"), MB_OK);
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ComponentWindow");

            if (Window)
                Window->Open();            
        }
        return true;
        //케이스문 끝
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
    //씬 불러오기
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    //빈 오브젝트 생성
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
    
    //클래스 윈도우에서 선택한 오브젝트의 이름을 받아온다.
    std::string SelectObjectItem = ClassWindow->GetSelectObjectItem();
    
    if (SelectObjectItem == "") //오브젝트 선택을 안했으면
        return;

    //오브젝트 선택 되었을 시 오브젝트 윈도우를 만든다.
    CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

    //※ 오브젝트 자주 만드는것들은 여기다 등록을 하는건가 많아지면 힘드니까 CDO같은걸 만들어서 사용한다.
    if (SelectObjectItem == "GameObject")
        Obj = Scene->CreateObject<CGameObject>(SelectObjectItem); //클래스 윈도우에서 선택한 오브젝트를 해당 씬에다 생성?

    else if(SelectObjectItem == "Player2D")
        Obj = Scene->CreateObject<CPlayer2D>(SelectObjectItem);

    else if (SelectObjectItem == "MyBullet")
        Obj = Scene->CreateObject<CMyBullet>(SelectObjectItem);

    else if (SelectObjectItem == "Monster")
        Obj = Scene->CreateObject<CMonster>(SelectObjectItem);

    if (Window)
    {
        Window->AddItem(Obj, SelectObjectItem); //오브젝트 윈도우에 목록을 추가함
        //트리가 해당 오브젝트를 들고있게 된다.
    }

}
