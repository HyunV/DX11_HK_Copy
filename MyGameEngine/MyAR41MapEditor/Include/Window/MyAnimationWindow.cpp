#include "MyAnimationWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorTree.h"
#include "PathManager.h"
#include "Engine.h"
#include "Resource/ResourceManager.h"
#include "Resource/Animation/AnimationManager.h"

CMyAnimationWindow::CMyAnimationWindow()    :
    m_ImageType(EImageType::Atlas)
{
}

CMyAnimationWindow::~CMyAnimationWindow()
{
    //if (!vecFileName[0] == '\t')
    //{
    //    if (!vecFileName.size() == 0)
    //    {
    //        for (int i = 0; i < m_List->GetListSize(); ++i)
    //        {
    //            SAFE_DELETE_ARRAY(vecFileName[i]);
    //        }
    //    }        
    //}
    //vecFileName.clear();
}

bool CMyAnimationWindow::Init()
{
    CEditorLabel* Label = CreateWidget<CEditorLabel>("시퀀스 툴");

    Label->SetColor(255, 0, 0, 255);
    //Label->SetAlign(0.5f, 0.5f);
    Label->SetSize(120.f, 30.f);

    CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
    Line = CreateWidget<CEditorSameLine>("Line");

    //m_Combo = CreateWidget<CEditorComboBox>("ImageTypeComboBox");
    //m_Combo->SetSelectPrevViewName(true);
    //m_Combo->SetHideName("ImageTypeComboBox");
    //m_Combo->SetPrevViewName("이미지 타입 선택");
    //m_Combo->SetSizeX(150.f);

    //m_Combo->AddItem("Atlas(Default)");
    //m_Combo->AddItem("Frame");
    //m_Combo->AddItem("Array");

    //m_Combo->SetSelectCallback<CMyAnimationWindow>(this, &CMyAnimationWindow::SelectComboCallback);

    //Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* ImageLoadButton = CreateWidget<CEditorButton>("이미지 불러오기");
    ImageLoadButton->SetSize(120.f, 30.f);
    ImageLoadButton->SetClickCallback<CMyAnimationWindow>
        (this, &CMyAnimationWindow::SelectLoadImageButtonCallback);

    CEditorLabel* Label2 = CreateWidget<CEditorLabel>("이미지 목록");
    Label2->SetColor(255, 0, 0, 255);
    Label2->SetAlign(0.5f, 0.5f);
    Label2->SetSize(120.f, 30.f);

    //Line = CreateWidget<CEditorSameLine>("Line");

    //CEditorLabel* Label3 = CreateWidget<CEditorLabel>("선택된 이미지");
    //Label3->SetColor(255, 0, 0, 255);
    //Label3->SetAlign(0.5f, 0.5f);
    //Label3->SetSize(150.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* LoadSqcButton = CreateWidget<CEditorButton>("시퀀스 불러오기");
    LoadSqcButton->SetSize(120.f, 30.f);
    //LoadSqcButton->SetClickCallback<CMyAnimationWindow>
        //(this, &CMyAnimationWindow::SelectLoadImageButtonCallback);

//    Line = CreateWidget<CEditorSameLine>("Line");

    //LoadSqcButton->SetClickCallback<CMyAnimationWindow>
        //(this, &CMyAnimationWindow::SelectLoadImageButtonCallback);

    m_List = CreateWidget<CEditorListBox>("ListBox");
    m_List-> SetHideName("ListBox");
    m_List-> SetPageItemCount(6);
    m_List-> SetSize(120.f, 150.f);

    m_List->SetSelectCallback<CMyAnimationWindow>(this, &CMyAnimationWindow::SelectListCallback);

    //Line = CreateWidget<CEditorSameLine>("Line");

    //CEditorImage* PreviewImage = CreateWidget<CEditorImage>("미리보기");
    //PreviewImage->SetSize(150.f, 150.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* SaveSqcButton = CreateWidget<CEditorButton>("시퀀스 저장");
    SaveSqcButton->SetSize(120.f, 120.f);
    SaveSqcButton->SetClickCallback<CMyAnimationWindow>
        (this, &CMyAnimationWindow::SaveSequence);
    
    //설정란
    m_SequenceName = CreateWidget<CEditorInput>("File Name");
    m_SequenceName->SetHintText("* 필수 입력란");

    m_FrameCount = CreateWidget<CEditorInput>("Frame Count");
    m_FrameCount->SetInputType(EImGuiInputType::Int);

    CEditorLabel* LTLabel = CreateWidget<CEditorLabel>("L, T");
    LTLabel->SetColor(255, 0, 0, 255);
    LTLabel->SetAlign(0.5f, 0.5f);
    LTLabel->SetSize(50.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_InputLT[0] = CreateWidget<CEditorInput>("Left");
    m_InputLT[0]->SetHideName("Left");
    m_InputLT[0]->SetHintText("L : ");
    m_InputLT[0]->SetInputType(EImGuiInputType::Float);
    Line = CreateWidget<CEditorSameLine>("Line");
    m_InputLT[1] = CreateWidget<CEditorInput>("Top");
    m_InputLT[1]->SetHideName("Top");
    m_InputLT[1]->SetHintText("T : ");
    m_InputLT[1]->SetInputType(EImGuiInputType::Float);

    CEditorLabel* RBLabel = CreateWidget<CEditorLabel>("R, B");
    RBLabel->SetColor(255, 0, 0, 255);
    RBLabel->SetAlign(0.5f, 0.5f);
    RBLabel->SetSize(50.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_InputRB[0] = CreateWidget<CEditorInput>("Right");
    m_InputRB[0]->SetHideName("Right");
    m_InputRB[0]->SetHintText("R : ");
    m_InputRB[0]->SetInputType(EImGuiInputType::Float);
    Line = CreateWidget<CEditorSameLine>("Line");
    m_InputRB[1] = CreateWidget<CEditorInput>("Bottom");
    m_InputRB[1]->SetHideName("Bottom");
    m_InputRB[1]->SetHintText("B : ");
    m_InputRB[1]->SetInputType(EImGuiInputType::Float);

    m_SaveMessege = CreateWidget<CEditorText>("Message");
    m_SaveMessege->SetColor(0, 255, 0, 255);
    //m_SaveMessege->SetText("저장완료!");

    return true;
}

void CMyAnimationWindow::Update(float DeltaTime)
{
    CEditorWindow::Update(DeltaTime);
}

void CMyAnimationWindow::SelectComboCallback(int SelectIndex, const std::string& Item)
{
    if (Item == "Atlas(Default)") 
    {
        m_ImageType = EImageType::Atlas;
        HideEditorText(false);
    }    
    else if (Item == "Frame") 
    {
        m_ImageType = EImageType::Frame;
        m_InputLT[0]->SetFloat(0.f);
        m_InputLT[1]->SetFloat(0.f);
        HideEditorText(true);
    }
        
    else if (Item == "Array")
    {
        m_ImageType = EImageType::Array;
        HideEditorText(true);
    }
        
}

void CMyAnimationWindow::SelectLoadImageButtonCallback()
{
    OPENFILENAME    ofn = {};

    TCHAR	FullPath[2048] = {};

    TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
    ofn.lpstrFilter = Filter;
    ofn.lpstrFile = FullPath;
    ofn.nMaxFile = 2048;
    ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;
    ofn.Flags = OFN_EXPLORER|OFN_ALLOWMULTISELECT;
    
    bool check = false;
    //파일 열기
    if (0 != GetOpenFileName(&ofn))
    {
        //동적할당 받았던적 있으면 제거
        if (check)
        {
            for (int i = 0; i < m_List->GetListSize(); ++i)
            {
                SAFE_DELETE_ARRAY(vecFileName[i]);
            }
            check = false;
        }
        
        vecFileName.clear();

        m_List->Clear();

        m_SaveMessege->SetText("");

        TCHAR str[512];
        int i = (int)wcslen(ofn.lpstrFile)+1;

        if (ofn.lpstrFile[i] == NULL) //파일 하나 열 때
        {   
            m_ImageType = EImageType::Atlas;
            HideEditorText(false);
            memset(m_ImageFullPath, 0, sizeof(TCHAR) * 512);
            wsprintf(m_ImageFullPath, ofn.lpstrFile);        

            TCHAR Ext[_MAX_EXT] = {};
            _wsplitpath_s(FullPath, 0, 0, 0, 0, str, 512, Ext, _MAX_EXT);
            wcscat_s(str, Ext);          
            m_List->AddItem(TCHARToString(str));
            vecFileName.push_back(str);
        }

        else //여러개 열 때
        {
            m_ImageType = EImageType::Frame;
            HideEditorText(true);       
            memset(m_ImageFullPath, 0, sizeof(TCHAR) * 512);
            wsprintf(m_ImageFullPath, ofn.lpstrFile);

            for (i; NULL != ofn.lpstrFile[i]; i += (int)(wcslen(ofn.lpstrFile + i) + 1))
            {
                wcscpy_s(str, ofn.lpstrFile + i);
                m_List->AddItem(TCHARToString(str));

                //동적할당, 그냥 TCHAR로 하면 배열 기존 목록들이 지금 TCHAR이름으로 바뀜
                TCHAR* FileName = new TCHAR[512];

                memset(FileName, 0, sizeof(TCHAR) * 512);

                wsprintf(FileName, str);

                vecFileName.push_back(FileName);

                check = true;
            }
        }
    }
    m_FrameCount->SetInt(m_List->GetListSize());
}

const std::string CMyAnimationWindow::TCHARToString(const TCHAR* ptsz)
{      
    size_t tcnt = wcslen((wchar_t*)ptsz);

    char psz[256];

    //wc sqc to multibyte sqc
    wcstombs_s(&tcnt, psz, sizeof(psz), ptsz, 256);

    std::string s = psz;

    return s;
}

void CMyAnimationWindow::HideEditorText(bool enable)
{
    m_FrameCount->ReadOnly(enable);
    m_InputLT[0]->ReadOnly(enable);
    m_InputLT[1]->ReadOnly(enable);
    //m_InputRB[0]->ReadOnly(enable);
    //m_InputRB[1]->ReadOnly(enable);
}

void CMyAnimationWindow::SelectListCallback(int SelectIndex, const std::string& Item)
{
    char	Text[256] = {};

    sprintf_s(Text, "%d : %s\n", SelectIndex, Item.c_str());

    OutputDebugStringA(Text);
}

void CMyAnimationWindow::CreateSequence(EImageType type)
{
    //에디터 기반으로 시퀀스 생성
    std::string FileName = m_SequenceName->GetText();
    std::string TexFileName = FileName + "_SQCTEX";
    int count = m_FrameCount->GetInt();
    float LTRB[4] = { m_InputLT[0]->GetFloat(), m_InputLT[1]->GetFloat(),
                     m_InputRB[0]->GetFloat(), m_InputRB[1]->GetFloat(), };

    switch (type)
    {
    case EImageType::Atlas:
        CResourceManager::GetInst()->
            CreateAnimationSequence2DFullPath(FileName, TexFileName, m_ImageFullPath);

        for (int i = 0; i < count; i++) 
        {
            CResourceManager::GetInst()->AddAnimationSequence2DFrame(FileName,
                Vector2(i * LTRB[2], LTRB[1]), Vector2((i + 1) * LTRB[2], LTRB[3]));
        }
        break;
    case EImageType::Frame:
        break;
    case EImageType::Array:
        break;
    default:
        break;
    }
}

void CMyAnimationWindow::SaveSequence()
{
    //시퀀스 저장
    //std::string FileName = m_SequenceName->GetText();

    //if (FileName.empty())
    //    return;

    ////시퀀스 만들어놓음
    //CreateSequence(m_ImageType);

    //CAnimationSequence2D* Seq = CResourceManager::GetInst()->
    //    FindAnimationSequence2D(FileName);

    //std::string s = Seq->GetName();

    //const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    //char FullPath[MAX_PATH] = {};

    //if (Info)
    //    strcpy_s(FullPath, Info->PathMultibyte);

    //strcat_s(FullPath, "Sequence/");
    //strcat_s(FullPath, FileName.c_str());
    //strcat_s(FullPath, ".sqc");

    ////TCHAR(WCHAR) To CHAR
    //int len = 512;
    //char temp[512];

    //WideCharToMultiByte(CP_ACP, 0, m_ImageFullPath, len, temp, len, 0, 0);
    //printf("%s", temp);
    //if(!Seq->Save(temp))
    //{
    //    m_SaveMessege->SetText("저장 실패..");
    //    return;
    //}
    //else{
    //    m_SaveMessege->SetText("저장 완료!");
    //}
}

