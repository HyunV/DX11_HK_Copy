#include "DefaultSetting.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "../GameObject/MyBullet.h"
#include "../UI/StartSceneUI.h"
#include "../UI/MainTitleUI.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "CollisionManager.h"
#include "PathManager.h"
#include "Animation/Animation2D.h"

CDefaultSetting::CDefaultSetting()
{
}

CDefaultSetting::~CDefaultSetting()
{
}

void CDefaultSetting::Init()
{
    LoadResource();

    CreateCDO();

    SetInput();

    SetCollision();
}

void CDefaultSetting::CreateCDO()
{    
    CScene::CreateObjectCDO<CPlayer2D>("Player2D");
    CScene::CreateObjectCDO<CMonster>("Monster");
    CScene::CreateObjectCDO<CMyBullet>("MyBullet");
    
    CScene::CreateUIWindowCDO<CStartSceneUI>("StartSceneUI");
    CScene::CreateUIWindowCDO<CMainTitleUI>("MainTitleUI");
}

void CDefaultSetting::LoadResource()
{
    LoadSequence();
    LoadAnimation();

    //CResourceManager::GetInst()->LoadSound("UI", "hasaki", false, "63.mp3");

    //128 128
    //CResourceManager::GetInst()->CreateAnimationSequence2D(
    //    "PlayerIdle", "PlayerSprite", TEXT("Player.png"));

    ////플레이어 대기모션 사진 구간을 나눠서 애니메이션 처리
    //for (int i = 0; i < 14; ++i)
    //{
    //    CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerIdle",
    //        Vector2(i * 45.f, 60.f), Vector2((i + 1) * 45.f, 120.f));
    //}

    ////낱장단위 이미지를 처리
    //std::vector<const TCHAR*>   vecFileName;

    //for (int i = 1; i <= 89; ++i)
    //{
    //    TCHAR* FileName = new TCHAR[MAX_PATH];

    //    memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

    //    wsprintf(FileName, TEXT("Explosion/Explosion%d.png"), i);

    //    vecFileName.push_back(FileName);
    //}

    //vecFileName;

    //CResourceManager::GetInst()->CreateAnimationSequence2D(
    //    "PlayerRun", "Explosion", vecFileName);

    //CResourceManager::GetInst()->AddAnimationSequence2DFrameAll("PlayerRun",
    //    89, Vector2(0.f, 0.f), Vector2(320.f, 240.f));

    //for (int i = 0; i <= 88; ++i)
    //{
    //    SAFE_DELETE_ARRAY(vecFileName[i]);
    //}

    //vecFileName.clear();
}

void CDefaultSetting::SetInput()
{
    // 키 등록
    CInput::GetInst()->AddBindKey("Rotation", 'D');
    CInput::GetInst()->AddBindKey("RotationInv", 'A');

    CInput::GetInst()->AddBindKey("MoveUp", 'W');
    CInput::GetInst()->AddBindKey("MoveDown", 'S');

    CInput::GetInst()->AddBindKey("Fire", VK_SPACE);
}

void CDefaultSetting::SetCollision()
{
    CCollisionManager::GetInst()->CreateChannel("Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Monster", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterAttack", ECollision_Interaction::Collision);

    CCollisionManager::GetInst()->CreateProfile("Player", "Player", true);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", "PlayerAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Monster", "Monster", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterAttack", "MonsterAttack", true);

    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Player", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "PlayerAttack", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Monster", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "PlayerAttack", ECollision_Interaction::Ignore);
}

void CDefaultSetting::LoadSequence()
{
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char FullPath[MAX_PATH] = {};

    if (Info)
        strcpy_s(FullPath, Info->PathMultibyte);

    strcat_s(FullPath, "Sequence/");

    //시퀀스 폴더 내 있는 모든 파일 로드
    for (const auto& file : std::filesystem::directory_iterator(FullPath))
    {
        char FileName[64] = {};
        char MaxPath[MAX_PATH] = {};
        char Ext[_MAX_EXT] = {};

        strcpy_s(MaxPath, file.path().generic_string().c_str());
        _splitpath_s(MaxPath, nullptr, 0, nullptr, 0, FileName, 64, Ext, _MAX_EXT);

        if (strcmp(FileName, "imgui") == 0)
        {
            continue;
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D(FileName, nullptr);
        CResourceManager::GetInst()->FindAnimationSequence2D(FileName)->Load(MaxPath);
    }
}

void CDefaultSetting::LoadAnimation()
{
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char FullPath[MAX_PATH] = {};

    if (Info)
        strcpy_s(FullPath, Info->PathMultibyte);

    strcat_s(FullPath, "Animation2D/");

    //시퀀스 폴더 내 있는 모든 파일 로드
    for (const auto& file : std::filesystem::directory_iterator(FullPath))
    {
        char FileName[64] = {};
        char MaxPath[MAX_PATH] = {};
        char Ext[_MAX_EXT] = {};

        strcpy_s(MaxPath, file.path().generic_string().c_str());
        _splitpath_s(MaxPath, nullptr, 0, nullptr, 0, FileName, 64, Ext, _MAX_EXT);

        if (strcmp(FileName, "imgui") == 0)
        {
            continue;
        }

        //CAnimation2D* Anim = CAnimation2D::FindCDO("Animation2D");
        
        FILE* File = nullptr;
        fopen_s(&File, MaxPath, "rb");

        CResourceManager::GetInst()->CreateAnimation2D(FileName);
        CAnimation2D* Anim = CResourceManager::GetInst()->FindAnimation2D(FileName);
        

        if (Anim)
        {
            Anim->Load(File);
            Anim->SetName(FileName);
        }

        fclose(File);
    }

    

    

    //fopen_s(&File, "dd", )
    
    //Anim->Load();
}
