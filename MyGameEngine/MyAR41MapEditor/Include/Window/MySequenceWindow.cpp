#include "MySequenceWindow.h"

#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorSliderBar.h"

#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Engine.h"

CMySequenceWindow::CMySequenceWindow() :
	m_ImageType(EImageType::Atlas)
{
}

CMySequenceWindow::~CMySequenceWindow()
{
	for (int i = 0; i < m_vecFullPathFileName.size(); ++i)
	{
		SAFE_DELETE_ARRAY(m_vecFullPathFileName[i]);
	}
	m_vecFullPathFileName.clear();
}

bool CMySequenceWindow::Init()
{
	m_Sequence = nullptr;

	CEditorLabel* Label = CreateWidget<CEditorLabel>("시퀀스 툴");

	Label->SetColor(255, 0, 0, 255);
	Label->SetSize(120.f, 30.f);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* ImageLoadButton = CreateWidget<CEditorButton>("이미지 불러오기");
	ImageLoadButton->SetSize(120.f, 30.f);
	ImageLoadButton->SetClickCallback<CMySequenceWindow>
		(this, &CMySequenceWindow::SelectLoadImageButtonCallback);

	CEditorLabel* Label2 = CreateWidget<CEditorLabel>("이미지 목록");
	Label2->SetColor(255, 0, 0, 255);
	Label2->SetAlign(0.5f, 0.5f);
	Label2->SetSize(120.f, 30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* LoadSqcButton = CreateWidget<CEditorButton>("시퀀스 불러오기");
	LoadSqcButton->SetSize(120.f, 30.f);
	LoadSqcButton->SetClickCallback<CMySequenceWindow>
		(this, &CMySequenceWindow::SelectLoadSequenceCallback);

	//이미지 리스트
	m_List = CreateWidget<CEditorListBox>("ListBoxAni");
	m_List->SetHideName("ListBoxAni");
	m_List->SetPageItemCount(6);
	m_List->SetSize(120.f, 150.f);

	m_List->SetSelectCallback<CMySequenceWindow>(this, &CMySequenceWindow::SelectListCallback);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* SaveSqcButton = CreateWidget<CEditorButton>("시퀀스 저장");
	SaveSqcButton->SetSize(120.f, 120.f);
	SaveSqcButton->SetClickCallback<CMySequenceWindow>
		(this, &CMySequenceWindow::SaveSequence);

	Label = CreateWidget<CEditorLabel>(" ");
	Label->SetColor(0, 0, 0, 0);
	Label->SetHideName(" ");

	//설정란
	m_SequenceName = CreateWidget<CEditorInput>("File Name");
	m_SequenceName->SetHintText("* 필수 입력란");
	m_SequenceName->SetSize(200.f, 50.f);

	m_FrameCount = CreateWidget<CEditorInput>("Frame Count");
	m_FrameCount->SetInputType(EImGuiInputType::Int);

	m_LoopCount = CreateWidget<CEditorInput>("Loop Count");
	m_LoopCount->SetInputType(EImGuiInputType::Int);

	CEditorLabel* LTLabel = CreateWidget<CEditorLabel>("시작 좌표");
	LTLabel->SetColor(255, 0, 0, 255);
	LTLabel->SetAlign(0.5f, 0.5f);
	LTLabel->SetSize(100.f, 30.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	m_InputStartEnd[0] = CreateWidget<CEditorInput>("Left");
	m_InputStartEnd[0]->SetHideName("Left");
	m_InputStartEnd[0]->SetInputType(EImGuiInputType::Float);
	m_InputStartEnd[0]->SetSizeX(53.f);
	Line = CreateWidget<CEditorSameLine>("Line");
	m_InputStartEnd[1] = CreateWidget<CEditorInput>("Top");
	m_InputStartEnd[1]->SetHideName("Top");
	m_InputStartEnd[1]->SetInputType(EImGuiInputType::Float);
	m_InputStartEnd[1]->SetSizeX(53.f);

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

	m_PreviewImage = CreateWidget<CEditorImage>("미리보기");
	m_PreviewImage->SetSize(150.f, 150.f);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* PlayButton = CreateWidget<CEditorButton>(">");
	PlayButton->SetSize(40.f, 40.f);
	PlayButton->SetClickCallback<CMySequenceWindow>
		(this, &CMySequenceWindow::PlayButton);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* PauseButton = CreateWidget<CEditorButton>("||");
	PauseButton->SetSize(40.f, 40.f);
	PauseButton->SetClickCallback<CMySequenceWindow>
		(this, &CMySequenceWindow::PauseButton);

	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorButton* StopButton = CreateWidget<CEditorButton>("ㅁ");
	StopButton->SetSize(40.f, 40.f);
	StopButton->SetClickCallback<CMySequenceWindow>
		(this, &CMySequenceWindow::StopButton);

	m_PlayScale = CreateWidget<CEditorInput>("PlayScale");
	m_PlayScale->SetInputType(EImGuiInputType::Float);
	m_PlayScale->SetFloat(20.f);

	m_Slide = CreateWidget<CEditorSliderBar>("Slide");
	m_Slide->SetBarMinRange(0);
	m_Slide->SetBarMaxRange(0);
	m_Slide->SetClickCallback<CMySequenceWindow>(this, &CMySequenceWindow::SliderCallback);

	//CEditorButton* testbtn = CreateWidget<CEditorButton>("Test");
	//testbtn->SetClickCallback(this, &CMySequenceWindow::ClearSetting);

	return true;
}

void CMySequenceWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	int FrameCount = m_FrameCount->GetInt();
	//bool AnimEnd = false;//특정 프레임 반복재생 변수

	if (FrameCount > 0)
	{
		m_Slide->SetBarMaxRange(FrameCount - 1); // 프레임 늘릴때마다 슬라이드 갱신

	//아틀라스면 m_vecFrame 갱신?
		if (m_ImageType == EImageType::Atlas)
			SetAtlasFrame(FrameCount);

		if (m_Play) //재생 시
		{
			//둘 다 vecFrame으로 재생
			m_Time += DeltaTime * m_PlayScale->GetFloat();
			if (m_Time > 1.f)
			{
				m_Time = 0;
				m_Slide->AddCurrentValue(); // 슬라이드 +1;

				//현재 값이 최대치를 초과하면
				if (m_Slide->GetCurrentValue() > m_Slide->GetBarMaxRange())
				{
					//AnimEnd = true;
					int loopCount = m_LoopCount->GetInt();

					//루프카운트가 0, 음수거나 최대치를 초과하면
					if (loopCount <= 0 || loopCount > m_Slide->GetBarMaxRange())
						m_Slide->ResetCurrentValue();
					else
						m_Slide->SetCurrentValue(m_LoopCount->GetInt());
				}

				int i = m_Slide->GetCurrentValue();

				if (m_ImageType == EImageType::Atlas)
					i = 0;

				SelectListCallback(i, m_List->GetItem(i));
			}
		}
	}
}

void CMySequenceWindow::SelectLoadImageButtonCallback()
{
	m_Play = false; //재생 중단

	OPENFILENAME    ofn = {};

	TCHAR	FullPath[2048] = {}; //파일 풀경로

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = 2048;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	//파일 열기
	if (0 != GetOpenFileName(&ofn))
	{
		//세팅 클리어
		ClearSetting();

		//리스트에 넣어줄 파일명
		int i = (int)wcslen(ofn.lpstrFile) + 1;

		//파일 하나 열 때 (아틀라스)
		if (ofn.lpstrFile[i] == NULL)
		{
			m_Messege->SetText("아틀라스 이미지");
			m_ImageType = EImageType::Atlas;

			AddFullPath(FullPath);
		}
		else //여러개 열 때(프레임)
		{
			m_Messege->SetText("프레임 이미지");
			m_ImageType = EImageType::Frame;

			//파일수대로 이미지 추가
			for (i; NULL != ofn.lpstrFile[i]; i += (int)(wcslen(ofn.lpstrFile + i) + 1))
			{
				TCHAR FileName[512] = {};
				memset(FileName, 0, sizeof(TCHAR) * 512);
				wcscpy_s(FileName, ofn.lpstrFile + i);

				//imgui.ini 예외
				std::string s = TCHARToString(FileName);
				if (s == "imgui.ini")
					continue;
				//=============

				//문자열 절대경로로 합쳐놓기 에러남
				TCHAR FilePath[512] = {}; //파일 풀경로 제작
				memset(FilePath, 0, sizeof(TCHAR) * 512);
				wcscpy_s(FilePath, FullPath);

				wcscat_s(FilePath, L"\\");
				wcscat_s(FilePath, FileName);
				FileName;

				AddFullPath(FilePath);
			}
		}

		//여기까지 진행완료 시		
		SetList(); //리스트 세팅
		SetSlide(m_ImageType); //슬라이드 세팅		
	}
}

void CMySequenceWindow::SelectLoadSequenceCallback()
{
	//불러온 시퀀스 넣어주기
	//==============파일 로드==================================
	OPENFILENAME    ofn = {};

	TCHAR	FullPath[256] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0*.sqc");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = 256;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(SEQUENCE2D_PATH)->Path;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	//파일 열기
	if (0 != GetOpenFileName(&ofn))
	{
		ClearSetting();

		TCHAR FileName[256] = {};
		TCHAR Ext[256] = {};

		_wsplitpath_s(FullPath, 0, 0, 0, 0, FileName, 256, Ext, 256);

		m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(TCHARToString(FileName));

		if (!m_Sequence)
		{
			m_Messege->SetText("불러오기 실패!");
			return;
		}

		//에디터 세팅
		LoadSequence(m_Sequence);
	}
}

const std::string CMySequenceWindow::TCHARToString(const TCHAR* ptsz)
{
	size_t tcnt = wcslen((wchar_t*)ptsz);

	char psz[256];

	//wc sqc to multibyte sqc
	wcstombs_s(&tcnt, psz, sizeof(psz), ptsz, 256);

	std::string s = psz;

	return s;
}

void CMySequenceWindow::SetList()
{
	//리스트 세팅
	int count = (int)m_vecFullPathFileName.size();

	for (int i = 0; i < count; i++)
	{
		TCHAR FileName[512] = {};
		TCHAR Ext[256] = {}; //확장자 필터
		memset(FileName, 0, sizeof(TCHAR) * 512);

		_wsplitpath_s(m_vecFullPathFileName[i], 0, 0, 0, 0, FileName, 512, Ext, 256);
		wcscat_s(FileName, Ext); //경로 + 확장자
		m_List->AddItem(TCHARToString(FileName));
	}

	//리스트에 들어있는 값이 하나 이상 = 프레임
	if (count > 1)
	{
		m_FrameCount->ReadOnly(true);
		m_FrameCount->SetInt(count);
	}
}

void CMySequenceWindow::SetSlide(EImageType Type)
{
	TCHAR FileName[256] = {};
	TCHAR Ext[256] = {}; //확장자 필터
	memset(FileName, 0, sizeof(TCHAR) * 256);

	_wsplitpath_s(m_vecFullPathFileName[0], 0, 0, 0, 0, FileName, 256, Ext, 256);

	std::string s = TCHARToString(FileName);

	//슬라이드 + 텍스처 세팅
	CResourceManager::GetInst()->LoadTextureFullPath(s, m_vecFullPathFileName);
	CTexture* Texture = CResourceManager::GetInst()->FindTexture(s);

	m_PreviewImage->SetTexture(Texture);

	//vecFrame으로 슬라이더 바 조작
	int count = (int)m_vecFullPathFileName.size();

	//count = (int)m_vecFrame.size();

	//아틀라스
	if (Texture)
	{
		if (!m_Sequence)
		{
			float Width = (float)(Texture->GetWidth());
			float Height = (float)(Texture->GetHeight());

			m_InputWidthHeight[0]->SetFloat((float)Width);
			m_InputWidthHeight[1]->SetFloat((float)Height);

			Animation2DFrameData Data;
			Data.Start = Vector2(0.f, 0.f);
			Data.End = Vector2(Width, Height);

			for (int i = 0; i < count; i++)
			{
				m_vecFrame.push_back(Data);
			}
		}
	}
	else
		return;

	m_Slide->SetBarMaxRange(count - 1);
	m_Slide->ResetCurrentValue();

	int i = m_Slide->GetCurrentValue();
	SelectListCallback(i, m_List->GetItem(i));
}

void CMySequenceWindow::AddFullPath(const TCHAR* FullPath512)
{
	//new로 만들어서 안없어지게 풀경로 저장
	TCHAR* SaveFullPath = new TCHAR[512];
	memset(SaveFullPath, 0, sizeof(TCHAR) * 512);
	wsprintf(SaveFullPath, FullPath512);

	m_vecFullPathFileName.push_back(SaveFullPath);
}

void CMySequenceWindow::SelectListCallback(int SelectIndex, const std::string& Item)
{
	int index = 0;

	if (m_ImageType == EImageType::Frame)
		index = SelectIndex;

	int n = m_Slide->GetCurrentValue();

	m_PreviewImage->SetImageIndex(index);
	m_PreviewImage->SetImageStart(m_vecFrame[n].Start.x, m_vecFrame[n].Start.y);
	m_PreviewImage->SetImageEnd(m_vecFrame[n].End.x, m_vecFrame[n].End.y);

	//====시퀀스 있으면 좌표값 불러오기 ? 보류
}

void CMySequenceWindow::CreateSequence(EImageType type)
{
	//에디터 기반으로 시퀀스 생성
	//성공적으로 만들어지면 멤버 시퀀스를 가지게 됨
	std::string FileName = m_SequenceName->GetText();

	int count = m_FrameCount->GetInt();
	int loopcount = m_LoopCount->GetInt();

	//시퀀스 이름과 텍스처 이름을 같게
	CResourceManager::GetInst()->LoadTextureFullPath(FileName, m_vecFullPathFileName);

	//CTexture* texture = CResourceManager::GetInst()->FindTexture(FileName);

	CResourceManager::GetInst()->CreateAnimationSequence2D(
		FileName, FileName, m_vecFullPathFileName);

	switch (type)
	{
	case EImageType::Atlas:

		for (int i = 0; i < count; i++)
		{
			CResourceManager::GetInst()->AddAnimationSequence2DFrame(FileName,
				m_vecFrame[i].Start, m_vecFrame[i].End);
		}
		break;

	case EImageType::Frame:

		CResourceManager::GetInst()->
			AddAnimationSequence2DFrameAll(FileName, count, Vector2(0.f, 0.f),
				Vector2(m_InputWidthHeight[0]->GetFloat(), m_InputWidthHeight[1]->GetFloat()));
		break;

	case EImageType::Array:
		break;

	default:
		break;
	}

	m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(FileName);

	m_Sequence->SetAnimation2DType((EAnimation2DType)m_ImageType);
	m_Sequence->SetFrameCount(count);
	m_Sequence->SetLoopCount(loopcount);
}

void CMySequenceWindow::SaveSequence()
{
	//시퀀스 저장
	std::string FileName = m_SequenceName->GetText();

	if (FileName.empty())
	{
		m_Messege->SetText("시퀀스 파일 이름을 지어주세요");
		return;
	}

	//같은 이름이 이미 있으면 기존 시퀀스 지워버림
	m_Sequence = CResourceManager::GetInst()->
		FindAnimationSequence2D(FileName);

	if (m_Sequence)
		CResourceManager::GetInst()->ReleaseAnimationSequence2D(FileName);
	//else
	//	return;

	//시퀀스 만들어놓음
	CreateSequence(m_ImageType);

	//시퀀스 파일 저장
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "Sequence/");
	strcat_s(FullPath, FileName.c_str());
	strcat_s(FullPath, ".sqc");

	if (!m_Sequence->Save(FullPath))
	{
		m_Messege->SetText("저장 실패..");
		CResourceManager::GetInst()->ReleaseAnimationSequence2D(FileName);
		m_Sequence = nullptr;
		return;
	}
	else {
		m_Messege->SetText("저장 완료!");
	}
}

void CMySequenceWindow::LoadSequence(class CAnimationSequence2D* Sequence)
{
	//시퀀스 불러와서 에디터에 값들 세팅해주는 함수
	ClearSetting();

	m_Sequence = Sequence;
	if (!m_Sequence)
	{
		m_Messege->SetText("시퀀스 파일 불러오기 실패");
		return;
	}

	//이미지 풀경로 세팅용
	m_ImageType = (EImageType)m_Sequence->GetAnim2DType();

	std::vector<TextureResourceInfo*> vecTextureInfo = m_Sequence->GetTexture()->GetTextureInfo();

	size_t size = vecTextureInfo.size();

	for (int i = 0; i < (int)size; i++)
	{
		TCHAR FullPath[512] = {};
		wsprintf(FullPath, CPathManager::GetInst()->FindPath(ROOT_PATH)->Path);
		wcscat_s(FullPath, vecTextureInfo[i]->FileName);

		AddFullPath(FullPath);
	}

	//start end frame 세팅

	int count = m_Sequence->GetFrameCount();

	for (int i = 0; i < count; i++)
	{
		m_vecFrame.push_back(m_Sequence->GetFrameData(i));
	}

	m_SequenceName->SetText(m_Sequence->GetName().c_str());
	m_FrameCount->SetInt(count);
	m_LoopCount->SetInt(m_Sequence->GetLoopCount());

	float x = m_vecFrame[0].Start.x;
	float y = m_vecFrame[0].Start.y;
	float w = m_vecFrame[0].End.x - x;
	float h = m_vecFrame[0].End.y - y;

	m_InputStartEnd[0]->SetFloat(x);
	m_InputStartEnd[1]->SetFloat(y);
	m_InputWidthHeight[0]->SetFloat(w);
	m_InputWidthHeight[1]->SetFloat(h);


	SetList();
	SetSlide(m_ImageType);
	//
}

void CMySequenceWindow::PlayButton()
{
	int Size = m_List->GetListSize();

	if (Size)
		m_Play = true;
}

void CMySequenceWindow::PauseButton()
{
	m_Play = false;
}

void CMySequenceWindow::StopButton()
{
	m_Play = false;
	m_Time = 0.f;
	m_Slide->ResetCurrentValue();

	int i = m_Slide->GetCurrentValue();

	int Size = m_List->GetListSize();
	if (Size)
		SelectListCallback(i, m_List->GetItem(i));
}

void CMySequenceWindow::ClearSetting()
{
	StopButton();

	

	m_ImageType = EImageType::Atlas;

	m_List->Clear(); //이미지 리스트

	m_vecFrame.clear();

	if (m_SequenceName->GetText())
		m_SequenceName->SetText("");

	m_FrameCount->SetInt(0);
	m_FrameCount->ReadOnly(false);

	m_LoopCount->SetInt(0);

	for (int i = 0; i < 2; i++)
	{
		m_InputStartEnd[i]->SetFloat(0.f);
		m_InputWidthHeight[i]->SetFloat(0.f);
	}

	m_PreviewImage->SetTexture("DefaultUI", TEXT("DefaultUI.png"));
	m_PreviewImage->SetSize(150.f, 150.f);

	m_Slide->SetBarMaxRange(0);
	m_Slide->SetBarMinRange(0);
	m_Slide->ResetCurrentValue();

	m_PlayScale->SetFloat(20.f);

	m_Play = false;
	m_Time = 0.f;

	//CResourceManager::GetInst()->ReleaseTexture("PreviewTexture");
	m_PreviewImage->SetTexture("DefaultUI");
	m_PreviewImage->SetImageStart(0.f, 0.f);
	m_PreviewImage->SetImageEnd(100.f, 100.f);

	m_Sequence = nullptr;

	//동적할당 전부 제거
	for (int i = 0; i < m_vecFullPathFileName.size(); ++i)
	{
		SAFE_DELETE_ARRAY(m_vecFullPathFileName[i]);
	}
	m_vecFullPathFileName.clear();

}

void CMySequenceWindow::SliderCallback()
{
	if (m_List->GetListSize())
	{
		int n = m_Slide->GetCurrentValue();

		if (m_ImageType == EImageType::Atlas)
			n = 0;

		SelectListCallback(n, m_List->GetItem(n));
	}
}

void CMySequenceWindow::SetAtlasFrame(int FrameCount)
{
	//미리보기 시 아틀라스 규격이면 이미지 세팅
	m_vecFrame.clear();

	Animation2DFrameData Data;

	struct Point {
		float x = 0.f;
		float y = 0.f;
		float Width = 0.f;
		float Height = 0.f;
	};

	Point point;
	point.x = m_InputStartEnd[0]->GetFloat();
	point.y = m_InputStartEnd[1]->GetFloat();
	point.Width = m_InputWidthHeight[0]->GetFloat();
	point.Height = m_InputWidthHeight[1]->GetFloat();

	//좌표 받아서 만듬
	for (int i = 0; i < FrameCount; i++)
	{
		Data.Start = Vector2(point.x + (point.Width * i), point.y);
		Data.End = Vector2((point.x + (point.Width * i)) + point.Width, point.y + point.Height);
		m_vecFrame.push_back(Data);
	}
}

