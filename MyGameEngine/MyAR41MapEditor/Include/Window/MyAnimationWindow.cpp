//#include "MyAnimationWindow.h"
//#include "Editor/EditorButton.h"
//#include "Editor/EditorSameLine.h"
//#include "Editor/EditorLabel.h"
//#include "Editor/EditorImage.h"
//#include "Editor/EditorText.h"
//#include "Editor/EditorInput.h"
//#include "Editor/EditorComboBox.h"
//#include "Editor/EditorListBox.h"
//#include "Editor/EditorTree.h"
//#include "PathManager.h"
//#include "Engine.h"
//
//CMyAnimationWindow::CMyAnimationWindow()    :
//    m_ImageType(EImageType::Atlas)
//{
//}
//
//CMyAnimationWindow::~CMyAnimationWindow()
//{
//}
//
//bool CMyAnimationWindow::Init()
//{
//    CEditorLabel* Label = CreateWidget<CEditorLabel>("시퀀스 툴");
//
//    Label->SetColor(255, 0, 0, 255);
//    Label->SetAlign(0.5f, 0.5f);
//    Label->SetSize(120.f, 30.f);
//
//    CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
//    Line = CreateWidget<CEditorSameLine>("Line");
//
//    m_Combo = CreateWidget<CEditorComboBox>("ImageTypeComboBox");
//    m_Combo->SetSelectPrevViewName(true);
//    m_Combo->SetHideName("ImageTypeComboBox");
//    m_Combo->SetPrevViewName("이미지 타입 선택");
//    m_Combo->SetSizeX(150.f);
//
//    m_Combo->AddItem("Atlas(Default)");
//    m_Combo->AddItem("Frame");
//    m_Combo->AddItem("Array");
//
//    m_Combo->SetSelectCallback<CMyAnimationWindow>(this, &CMyAnimationWindow::SelectComboCallback);
//
//    Line = CreateWidget<CEditorSameLine>("Line");
//
//    CEditorButton* ImageLoadButton = CreateWidget<CEditorButton>("이미지 불러오기");
//    ImageLoadButton->SetSize(120.f, 30.f);
//    ImageLoadButton->SetClickCallback<CMyAnimationWindow>
//        (this, &CMyAnimationWindow::SelectLoadImageButtonCallback);
//
//    Label = CreateWidget<CEditorLabel>("이미지 목록");
//
//    m_List = CreateWidget<CEditorListBox>("ListBox");
//    m_List-> SetHideName("ListBox");
//    m_List-> SetPageItemCount(10);
//
//    return true;
//}
//
//void CMyAnimationWindow::Update(float DeltaTime)
//{
//    CEditorWindow::Update(DeltaTime);
//}
//
//void CMyAnimationWindow::SelectComboCallback(int SelectIndex, const std::string& Item)
//{
//    if (Item == "Atlas(Default)")
//        m_ImageType = EImageType::Atlas;
//    else if (Item == "Frame")
//        m_ImageType = EImageType::Frame;
//    else if (Item == "Array")
//        m_ImageType = EImageType::Array;
//}
//
//void CMyAnimationWindow::SelectLoadImageButtonCallback()
//{
//    OPENFILENAME    ofn = {};
//
//    TCHAR	FullPath[MAX_PATH] = {};
//
//    TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");
//
//    ofn.lStructSize = sizeof(OPENFILENAME);
//    ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
//    ofn.lpstrFilter = Filter;
//    ofn.lpstrFile = FullPath;
//    ofn.nMaxFile = MAX_PATH;
//    ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;
//    ofn.Flags = OFN_EXPLORER|OFN_ALLOWMULTISELECT;
//    GetOpenFileName(&ofn);
//    
//    ofn.lpstrFile;
//
//
//    //OutputDebugStringA(Text);
//}
