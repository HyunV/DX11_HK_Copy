#include "MyAnimationWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorSliderBar.h"
#include "PathManager.h"
#include "Engine.h"
#include "Resource/ResourceManager.h"
#include "Resource/Animation/AnimationManager.h"

bool check = false; //동적할당 받았었는지 여부

CMyAnimationWindow::CMyAnimationWindow()    :
    m_ImageType(EImageType::Atlas)
{
}

CMyAnimationWindow::~CMyAnimationWindow()
{
        //1개면 아틀라스 담았던거였으므로 동적할당을 안해줬으니 패스
        if (!(m_vecFullPathFileName.size() == 0 || m_vecFullPathFileName.size() == 1))
        {
            for (int i = 0; i <= m_List->GetListSize()-1; ++i)
            {
                SAFE_DELETE_ARRAY(m_vecFullPathFileName[i]);
            }
        }        
        m_vecFullPathFileName.clear();
}

bool CMyAnimationWindow::Init()
{
    CEditorLabel* Label = CreateWidget<CEditorLabel>("시퀀스 툴");

    Label->SetColor(255, 0, 0, 255);
    //Label->SetAlign(0.5f, 0.5f);
    Label->SetSize(120.f, 30.f);

    CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* ImageLoadButton = CreateWidget<CEditorButton>("이미지 불러오기");
    ImageLoadButton->SetSize(120.f, 30.f);
    ImageLoadButton->SetClickCallback<CMyAnimationWindow>
        (this, &CMyAnimationWindow::SelectLoadImageButtonCallback);

    CEditorLabel* Label2 = CreateWidget<CEditorLabel>("이미지 목록");
    Label2->SetColor(255, 0, 0, 255);
    Label2->SetAlign(0.5f, 0.5f);
    Label2->SetSize(120.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* LoadSqcButton = CreateWidget<CEditorButton>("시퀀스 불러오기");
    LoadSqcButton->SetSize(120.f, 30.f);
    //LoadSqcButton->SetClickCallback<CMyAnimationWindow>
        //(this, &CMyAnimationWindow::SelectLoadImageButtonCallback);

//    Line = CreateWidget<CEditorSameLine>("Line");

    //LoadSqcButton->SetClickCallback<CMyAnimationWindow>
        //(this, &CMyAnimationWindow::SelectLoadImageButtonCallback);

    m_List = CreateWidget<CEditorListBox>("ListBoxAni");
    m_List-> SetHideName("ListBoxAni");
    m_List-> SetPageItemCount(6);
    m_List-> SetSize(120.f, 150.f);

    m_List->SetSelectCallback<CMyAnimationWindow>(this, &CMyAnimationWindow::SelectListCallback);

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

    CEditorLabel* LTLabel = CreateWidget<CEditorLabel>("시작 좌표");
    LTLabel->SetColor(255, 0, 0, 255);
    LTLabel->SetAlign(0.5f, 0.5f);
    LTLabel->SetSize(100.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_InputStartPoint[0] = CreateWidget<CEditorInput>("Left");
    m_InputStartPoint[0]->SetHideName("Left");
    m_InputStartPoint[0]->SetInputType(EImGuiInputType::Float);
    m_InputStartPoint[0]->SetSizeX(53.f);
    Line = CreateWidget<CEditorSameLine>("Line");
    m_InputStartPoint[1] = CreateWidget<CEditorInput>("Top");
    m_InputStartPoint[1]->SetHideName("Top");
    m_InputStartPoint[1]->SetInputType(EImGuiInputType::Float);
    m_InputStartPoint[1]->SetSizeX(53.f);

    CEditorLabel* RBLabel = CreateWidget<CEditorLabel>("너비, 높이");
    RBLabel->SetColor(255, 0, 0, 255);
    RBLabel->SetAlign(0.5f, 0.5f);
    RBLabel->SetSize(100.f, 30.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    m_InputWidthHeight[0] = CreateWidget<CEditorInput>("Right");
    m_InputWidthHeight[0]->SetHideName("Right");
    m_InputWidthHeight[0]->SetInputType(EImGuiInputType::Float);
    m_InputWidthHeight[0]->SetSizeX(53.f);
    Line = CreateWidget<CEditorSameLine>("Line");
    m_InputWidthHeight[1] = CreateWidget<CEditorInput>("Bottom");
    m_InputWidthHeight[1]->SetHideName("Bottom");
    m_InputWidthHeight[1]->SetInputType(EImGuiInputType::Float);
    m_InputWidthHeight[1]->SetSizeX(53.f);

    m_Messege = CreateWidget<CEditorText>("Message");
    m_Messege->SetColor(0, 255, 0, 255);
    m_Messege->SetText("미리보기");

    //Line = CreateWidget<CEditorSameLine>("Line");

    m_PreviewImage = CreateWidget<CEditorImage>("미리보기");
    m_PreviewImage->SetSize(150.f, 150.f);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* PlayButton = CreateWidget<CEditorButton>(">");
    PlayButton->SetSize(40.f, 40.f);
    PlayButton->SetClickCallback<CMyAnimationWindow>
        (this, &CMyAnimationWindow::PlayButton);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* PauseButton = CreateWidget<CEditorButton>("||");
    PauseButton->SetSize(40.f, 40.f);
    PauseButton->SetClickCallback<CMyAnimationWindow>
        (this, &CMyAnimationWindow::PauseButton);

    Line = CreateWidget<CEditorSameLine>("Line");

    CEditorButton* StopButton = CreateWidget<CEditorButton>("ㅁ");
    StopButton->SetSize(40.f, 40.f);
    StopButton->SetClickCallback<CMyAnimationWindow>
        (this, &CMyAnimationWindow::StopButton);

    m_PlayScale = CreateWidget<CEditorInput>("PlayScale");
    m_PlayScale->SetInputType(EImGuiInputType::Float);
    m_PlayScale->SetFloat(20.f);

    m_Slide = CreateWidget<CEditorSliderBar>("Slide");
    m_Slide->SetBarMaxRange(0);
    m_Slide->SetClickCallback<CMyAnimationWindow>(this, &CMyAnimationWindow::SliderCallback);
    return true;
}

void CMyAnimationWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

    int FrameCount = m_FrameCount->GetInt();

    m_Slide->SetBarMaxRange(FrameCount);

	if (m_Play && m_List->GetListSize() != 0)
	{
        //아틀라스, 프레임 구분
		m_Time += DeltaTime *m_PlayScale->GetFloat();
		if (m_Time > 1.f)
		{
			m_Time = 0;

            m_Slide->AddCurrentValue();
            
			if (m_Slide->GetCurrentValue() > m_Slide->GetBarMaxRange())
			{
				m_Slide->ResetCurrentValue();
			}

		}

        if (m_ImageType == EImageType::Atlas)
        {
            //아틀라스형태로 재생
            if (m_vecFrame.size() > 1)
            {
               int n = m_Slide->GetCurrentValue()-1;
               m_PreviewImage->SetImageStart(m_vecFrame[n].Start.x, m_vecFrame[n].Start.y);
               m_PreviewImage->SetImageEnd(m_vecFrame[n].End.x, m_vecFrame[n].End.y);
            }

        }
        else if (m_ImageType == EImageType::Frame)
        {
            int i = m_Slide->GetCurrentValue() - 1;
            SelectListCallback(i, m_List->GetItem(i));
        }
	}

}

void CMyAnimationWindow::SelectComboCallback(int SelectIndex, const std::string& Item)
{
    //현재 안쓰는 기능
    if (Item == "Atlas(Default)") 
    {
        m_ImageType = EImageType::Atlas;
        HideEditorText(false);
    }    
    else if (Item == "Frame") 
    {
        m_ImageType = EImageType::Frame;
        m_InputStartPoint[0]->SetFloat(0.f);
        m_InputStartPoint[1]->SetFloat(0.f);
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
    m_InputStartPoint[0]->SetFloat(0.f);
    m_InputStartPoint[1]->SetFloat(0.f);
    m_InputWidthHeight[0]->SetFloat(0.f);
    m_InputWidthHeight[1]->SetFloat(0.f);

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
    
    //파일 열기
    if (0 != GetOpenFileName(&ofn))
    {
        m_Play = false;
        //동적할당 받았던적 있으면 제거
        if (check)
        {
            for (int i = 0; i < m_List->GetListSize(); ++i)
            {
                SAFE_DELETE_ARRAY(m_vecFullPathFileName[i]);
            }
            check = false;
        }
        
        m_vecFullPathFileName.clear();

        m_List->Clear();

        m_Messege->SetText("");

        TCHAR str[512];
        int i = (int)wcslen(ofn.lpstrFile)+1;
        
        //파일 하나 열 때
        if (ofn.lpstrFile[i] == NULL) 
        {   
            m_Messege->SetText("아틀라스 이미지");
            m_ImageType = EImageType::Atlas;
            HideEditorText(false);
            memset(m_ImageFullPath, 0, sizeof(TCHAR) * 512);
            wsprintf(m_ImageFullPath, ofn.lpstrFile);        

            TCHAR Ext[_MAX_EXT] = {};
            _wsplitpath_s(FullPath, 0, 0, 0, 0, str, 512, Ext, _MAX_EXT);
            wcscat_s(str, Ext);          
            m_List->AddItem(TCHARToString(str));
            m_vecFullPathFileName.push_back(str);
            m_FrameCount->SetInt(1);
        }

        else //여러개 열 때(프레임)
        {
            m_Messege->SetText("프레임 이미지");
            m_ImageType = EImageType::Frame;
            HideEditorText(true);       
            memset(m_ImageFullPath, 0, sizeof(TCHAR) * 512);         
            wsprintf(m_ImageFullPath, ofn.lpstrFile);
            wcscat_s(m_ImageFullPath, L"\\");

            //파일수대로 이미지 추가
            for (i; NULL != ofn.lpstrFile[i]; i += (int)(wcslen(ofn.lpstrFile + i) + 1))
            {
                wcscpy_s(str, ofn.lpstrFile + i);

                //imgui.ini 예외
                int len = 256;
                char temp[256];
                WideCharToMultiByte(CP_ACP, 0, str, len, temp, len, 0, 0);
                printf("%s", temp);
                if(strcmp(temp, "imgui.ini") == 0)         
                {
                    continue;
                }

                m_List->AddItem(TCHARToString(str));

                //문자열 절대경로로 합쳐놓기
                TCHAR FilePath[512] = {};
                memset(FilePath, 0, sizeof(TCHAR) * 256);
                wcscpy_s(FilePath, m_ImageFullPath);
                wcscat_s(FilePath, str);
                
                //동적할당, 그냥 TCHAR로 하면 배열 기존 목록들이 지금 TCHAR이름으로 바뀜
                TCHAR* FileName = new TCHAR[512];       
                memset(FileName, 0, sizeof(TCHAR) * 512);
                wsprintf(FileName, FilePath);
                
                m_vecFullPathFileName.push_back(FileName);
                check = true;
            }           
        }
    }

    //슬라이드 세팅
    if (m_List->GetListSize() != 0)
    {
        m_FrameCount->SetInt(m_List->GetListSize());
        m_Slide->SetBarMinRange(1);
        m_Slide->SetBarMaxRange(m_FrameCount->GetInt());
        m_Slide->ResetCurrentValue();
        int i = m_Slide->GetCurrentValue()-1;

        SelectListCallback(i, m_List->GetItem(i));

        CTexture* texture = CResourceManager::GetInst()->FindTexture(m_List->GetItem(i));
        int Width = texture->GetWidth();
        int Height = texture->GetHeight();
        m_PreviewImage->SetImageStart(0, 0);
        m_PreviewImage->SetImageEnd(Width, Height);

        if (m_ImageType == EImageType::Frame)
        {
            m_InputWidthHeight[0]->SetFloat((float)Width);
            m_InputWidthHeight[1]->SetFloat((float)Height);
        }

        StopButton();
    }
    m_vecFrame.clear();
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
    m_InputStartPoint[0]->ReadOnly(enable);
    m_InputStartPoint[1]->ReadOnly(enable);
    //m_InputWidthHeight[0]->ReadOnly(enable);
    //m_InputWidthHeight[1]->ReadOnly(enable);
}

void CMyAnimationWindow::SelectListCallback(int SelectIndex, const std::string& Item)
{
    //char	Text[256] = {};

    //sprintf_s(Text, "%d : %s\n", SelectIndex, Item.c_str());

    //OutputDebugStringA(Text);

    m_PreviewImage->SetTextureFullPath(Item, m_vecFullPathFileName[SelectIndex]);
    
    //시퀀스 있으면 좌표값 불러오기?
}

void CMyAnimationWindow::CreateSequence(EImageType type)
{
    //에디터 기반으로 시퀀스 생성
    std::string FileName = m_SequenceName->GetText();

    //==시퀀스 이미지 파일을 리소스 매니저에 ㅁ_SQCTEX 형태로 이름 지어줌
    std::string TexFileName = FileName + "_SQCTEX";
    int count = m_FrameCount->GetInt(); 

    switch (type)
    {
    case EImageType::Atlas:

        CResourceManager::GetInst()->
            CreateAnimationSequence2DFullPath(FileName, TexFileName, m_ImageFullPath);

        for (int i = 0; i < count; i++) 
        {
            //저장 로직 수정!!
            //CResourceManager::GetInst()->AddAnimationSequence2DFrame(FileName,
            //    Vector2(i * LTRB[2], LTRB[1]), Vector2((i + 1) * LTRB[2], LTRB[3]));
            CResourceManager::GetInst()->AddAnimationSequence2DFrame(FileName,
                m_vecFrame[i].Start, m_vecFrame[i].End);
        }
        break;

    case EImageType::Frame:

        CResourceManager::GetInst()->
            CreateAnimationSequence2DFullPath(FileName, TexFileName, m_vecFullPathFileName);
        CResourceManager::GetInst()->
            AddAnimationSequence2DFrameAll(FileName, count, Vector2(0.f, 0.f), 
                Vector2(m_InputWidthHeight[0]->GetFloat(), m_InputWidthHeight[1]->GetFloat()));

        for (int i = 0; i <= count - 1; ++i)
        {
            SAFE_DELETE_ARRAY(m_vecFullPathFileName[i]);
        }

        check = false;
        m_vecFullPathFileName.clear();
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
    std::string FileName = m_SequenceName->GetText();

    if (FileName.empty())
        return;

    //시퀀스 만들어놓음
    CreateSequence(m_ImageType);

    CAnimationSequence2D* Seq = CResourceManager::GetInst()->
        FindAnimationSequence2D(FileName);

    std::string s = Seq->GetName();

    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char FullPath[MAX_PATH] = {};

    if (Info)
        strcpy_s(FullPath, Info->PathMultibyte);

    strcat_s(FullPath, "Sequence/");
    strcat_s(FullPath, FileName.c_str());
    strcat_s(FullPath, ".sqc");

    if(!Seq->Save(FullPath))
    {
        m_Messege->SetText("저장 실패..");
        return;
    }
    else{
        m_Messege->SetText("저장 완료!");
    }
}

void CMyAnimationWindow::PlayButton()
{
    if (m_ImageType == EImageType::Atlas)
    {
        m_vecFrame.clear();
        SetAtlasFrame();
        m_Slide->ResetCurrentValue();
    }
    
    m_Play = true;
}

void CMyAnimationWindow::PauseButton()
{
    m_Play = false;
}

void CMyAnimationWindow::StopButton()
{
    if (m_Slide->GetCurrentValue() == 0)
        return;

    m_Play = false;
    m_Time = 0.f;
    m_Slide->ResetCurrentValue();
    int i = m_Slide->GetCurrentValue()-1;
    SelectListCallback(i, m_List->GetItem(i));
    CTexture* texture = CResourceManager::GetInst()->FindTexture(m_List->GetItem(i));
    int Width = texture->GetWidth();
    int Height = texture->GetHeight();
    m_PreviewImage->SetImageStart(0, 0);
    m_PreviewImage->SetImageEnd(Width, Height);
}

void CMyAnimationWindow::SliderCallback()
{
    //char Text[256] = {};
    //sprintf_s(Text, "%d\n", m_Slide->GetCurrentValue());
    //OutputDebugStringA(Text);

    if (m_ImageType == EImageType::Atlas && m_List->GetListSize() != 0 && m_vecFrame.size() != 0)
    {
        int n = m_Slide->GetCurrentValue()-1;
        m_PreviewImage->SetImageStart(m_vecFrame[n].Start.x, m_vecFrame[n].Start.y);
        m_PreviewImage->SetImageEnd(m_vecFrame[n].End.x, m_vecFrame[n].End.y);
    }

    else if (m_ImageType == EImageType::Frame)
    {
        int i = m_Slide->GetCurrentValue() - 1;
        SelectListCallback(i, m_List->GetItem(i));
    }
}

void CMyAnimationWindow::SetAtlasFrame()
{
    //아틀라스 규격 세팅

    int FrameCount = m_FrameCount->GetInt();

    m_Slide->SetBarMaxRange(FrameCount);
    Animation2DFrameData Data;

    struct Point {
        float x = 0.f;
        float y = 0.f;
        float Width = 0.f;
        float Height = 0.f;
    };
    
    Point point;
    point.x = m_InputStartPoint[0]->GetFloat();
    point.y = m_InputStartPoint[1]->GetFloat();
    point.Width = m_InputWidthHeight[0]->GetFloat();
    point.Height = m_InputWidthHeight[1]->GetFloat();

    //좌표 받아서 만듬
    for (int i = 0; i < FrameCount; i++)
    {
        Data.Start = Vector2(point.x+ (point.Width * i), point.y);
        Data.End = Vector2((point.x + (point.Width * i))+ point.Width, point.y + point.Height);
        m_vecFrame.push_back(Data);
    }
}

