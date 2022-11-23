#include "SpriteComponentWidgetList.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorGUIManager.h"
#include "../DetailWindow.h"
#include "Component/SpriteComponent.h"
#include "Engine.h"
#include "PathManager.h"
#include "Resource/Texture/Texture.h"
#include "Resource/Material/Material.h"

CSpriteComponentWidgetList::CSpriteComponentWidgetList()
{
}

CSpriteComponentWidgetList::~CSpriteComponentWidgetList()
{
}

void CSpriteComponentWidgetList::SetSpriteContent(CSpriteComponent* Sprite)
{
	m_Sprite = Sprite;

	//텍스처 있으면 불러오기
	CEditorTree<void*>* Category = FindWidget<CEditorTree<void*>>("SpriteComponent");

	if (!Category)
		return;

	CEditorImage* ImageWidget = Category->FindWidget<CEditorImage>("SpriteImage");
	CTexture* texture = m_Sprite->GetTexture();

	if (texture)
	{
		if (!m_Sprite->GetAnimation())
		{
			ImageWidget->SetTexture(texture);
		}	
	}

	//머테리얼 정보 불러오기
	CMaterial* Material = m_Sprite->GetMaterial(0);
	
	Vector4 v = Material->GetBaseColor();
	m_BaseColor[0]->SetFloat(v.x*255.f);
	m_BaseColor[1]->SetFloat(v.y*255.f);
	m_BaseColor[2]->SetFloat(v.z*255.f);
	m_BaseColor[3]->SetFloat(v.w*255.f);

	m_Opacity->SetFloat(Material->GetOpacity());

	//애니메이션
	m_AnimationClass->SetText(Sprite->GetAnimationName().c_str());

	// 애니메이션 정보를 얻어와서 그 이름들을 리스트에 넣어준다.
	m_AnimationList->Clear();

	std::vector<std::string>	vecAnimNames;

	Sprite->GetAnimationNames(vecAnimNames);

	size_t	Size = vecAnimNames.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_AnimationList->AddItem(vecAnimNames[i]);
	}
}

bool CSpriteComponentWidgetList::Init()
{
	CEditorTree<void*>* Category = CreateWidget<CEditorTree<void*>>("SpriteComponent");

	Category->SetSize(400.f, 300.f);

	Category->AddItem(nullptr, "SpriteComponent");
	Category->AddItem(nullptr, "Sprite", "SpriteComponent");
	Category->AddItem(nullptr, "Animation", "SpriteComponent");
	Category->AddItem(nullptr, "Material", "SpriteComponent");
	//Category->AddItem(nullptr, "ss", "Material");

	Category->CreateWidget<CEditorImage>("Sprite", "SpriteImage");

	Category->CreateWidget<CEditorSameLine>("Sprite", "Line");

	CEditorButton* Button = Category->CreateWidget<CEditorButton>("Sprite", "Load Texture");

	Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::SelectTextureButtonClick);


	//==========================애니메이션===================================
	m_AnimationClass = Category->CreateWidget<CEditorInput>("Animation", "AnimationClass", 100.f, 30.f);
	m_AnimationClass->ReadOnly(true);
	m_AnimationClass->SetText("None");
	m_AnimationClass->SetSize(150.f, 30.f);

	Category->CreateWidget<CEditorSameLine>("Animation", "Line");

	Button = Category->CreateWidget<CEditorButton>("Animation", "CreateAnimation");

	Button->SetSize(150.f, 30.f);
	Button->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::CreateAnimationButtonClick);

	m_AnimationList = Category->CreateWidget<CEditorListBox>("Animation", "AnimationList");

	m_AnimationList->SetHideName("AnimationList");

	m_AnimationList->SetSize(150.f, 300.f);
	m_AnimationList->SetPageItemCount(6);
	m_AnimationList->SetSelectCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::AnimationSelectCallback);

	Category->CreateWidget<CEditorSameLine>("Animation", "Line");

	CEditorGroup* AnimDataGroup = Category->CreateWidget<CEditorGroup>("Animation", "Animation2DData");

	m_PlayTime = AnimDataGroup->CreateWidget<CEditorInput>("PlayTime", 100.f, 30.f);
	m_PlayTime->SetInputType(EImGuiInputType::Float);

	m_PlayScale = AnimDataGroup->CreateWidget<CEditorInput>("PlayScale", 100.f, 30.f);
	m_PlayScale->SetInputType(EImGuiInputType::Float);
	//
	//머테리얼

	//Category->CreateWidget<CEditorImage>("Material", "Test");

	//===========BaseColor
	CEditorLabel* Label = Category->CreateWidget<CEditorLabel>("Material", "Base Color", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);

	Category->CreateWidget<CEditorSameLine>("Material", "Line");
	m_BaseColor[0] = Category->CreateWidget<CEditorInput>("Material", "BaseColorR", 60.f, 30.f);
	m_BaseColor[0]->SetInputType(EImGuiInputType::Float);
	m_BaseColor[0]->SetHideName("BaseColorR");
	m_BaseColor[0]->SetInputCallback<CSpriteComponentWidgetList>
		(this, &CSpriteComponentWidgetList::BaseColorCallback);
	
	Category->CreateWidget<CEditorSameLine>("Material", "Line");
	m_BaseColor[1] = Category->CreateWidget<CEditorInput>("Material", "BaseColorG", 60.f, 30.f);
	m_BaseColor[1]->SetInputType(EImGuiInputType::Float);
	m_BaseColor[1]->SetHideName("BaseColorG");
	m_BaseColor[1]->SetInputCallback<CSpriteComponentWidgetList>
		(this, &CSpriteComponentWidgetList::BaseColorCallback);

	Category->CreateWidget<CEditorSameLine>("Material", "Line");
	m_BaseColor[2] = Category->CreateWidget<CEditorInput>("Material", "BaseColorB", 60.f, 30.f);
	m_BaseColor[2]->SetInputType(EImGuiInputType::Float);
	m_BaseColor[2]->SetHideName("BaseColorB");
	m_BaseColor[2]->SetInputCallback<CSpriteComponentWidgetList>
		(this, &CSpriteComponentWidgetList::BaseColorCallback);

	Category->CreateWidget<CEditorSameLine>("Material", "Line");
	m_BaseColor[3] = Category->CreateWidget<CEditorInput>("Material", "BaseColorA", 60.f, 30.f);
	m_BaseColor[3]->SetInputType(EImGuiInputType::Float);
	m_BaseColor[3]->SetHideName("BaseColorA");
	m_BaseColor[3]->SetInputCallback<CSpriteComponentWidgetList>
		(this, &CSpriteComponentWidgetList::BaseColorCallback);

	//=========Opacity
	Label = Category->CreateWidget<CEditorLabel>("Material", "Opacity", 100.f, 30.f);
	Label->SetColor(29, 47, 73, 255);
	m_Opacity = Category->CreateWidget<CEditorInput>("Material", "OpacityValue", 60.f, 30.f);
	m_Opacity->SetInputType(EImGuiInputType::Float);
	m_Opacity->SetHideName("OpacityValue");
	m_Opacity->SetInputCallback<CSpriteComponentWidgetList>
		(this, &CSpriteComponentWidgetList::OpacityCallback);


	//m_Sprite->SetRenderLayerName
	//프로그래스 바로 조절

	//===========현재 미구현 머테리얼
	//Label = Category->CreateWidget<CEditorLabel>("Material", "Ambient", 100.f, 30.f);
	//Label->SetColor(100, 100, 100, 255);

	//Label = Category->CreateWidget<CEditorLabel>("Material", "Specular", 100.f, 30.f);
	//Label->SetColor(100, 100, 100, 255);

	//Label = Category->CreateWidget<CEditorLabel>("Material", "Emissive", 100.f, 30.f);
	//Label->SetColor(100, 100, 100, 255);



	return true;
}

void CSpriteComponentWidgetList::SelectTextureButtonClick()
{
	//로딩함수 
	OPENFILENAME	ofn = {};

	TCHAR	FullPath[MAX_PATH] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&ofn) != 0)
	{
		CEditorTree<void*>* Category = FindWidget<CEditorTree<void*>>("SpriteComponent");

		if (!Category)
			return;

		CEditorImage* ImageWidget = Category->FindWidget<CEditorImage>("SpriteImage");

		if (ImageWidget)
		{
			TCHAR	wTexName[256] = {};

			_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

			char	TexName[256] = {};

			int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

			WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

			ImageWidget->SetTextureFullPath(TexName, FullPath);

			// 선택한 SpriteComponent의 Texture를 교체한다.
			if (m_Sprite)
			{				
				m_Sprite->SetTextureFullPath(TexName, FullPath);

				// Animation을 제거한다.
				m_Sprite->ClearAnimation();
			}
		}
	}
}

void CSpriteComponentWidgetList::CreateAnimationButtonClick()
{
	//CAnimation2DWindow* Animation2DWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CAnimation2DWindow>("Animation2DWindow");

	//std::string Name = Animation2DWindow->GetAnimation2DSelectName();

	//if (Name.empty())
	//	return;

	//CSpriteComponent* Sprite = (CSpriteComponent*)m_DetailWindow->GetSelectComponent();

	//if (Name == "Animation2D")
	//{
	//	Sprite->SetAnimation<CAnimation2D>("Animation2D");
	//}
}

void CSpriteComponentWidgetList::AnimationSelectCallback(int Index, const std::string& Item)
{
}

void CSpriteComponentWidgetList::BaseColorCallback()
{
	OutputDebugStringA("Base");

	CMaterial* Material = m_Sprite->GetMaterial(0);

	Vector4 v = Vector4(
		m_BaseColor[0]->GetFloat(),
		m_BaseColor[1]->GetFloat(),
		m_BaseColor[2]->GetFloat(),
		m_BaseColor[3]->GetFloat());

	Material->SetBaseColor(v / 255.f);

	
}

void CSpriteComponentWidgetList::OpacityCallback()
{
	OutputDebugStringA("Opacity");
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->SetOpacity(m_Opacity->GetFloat());
}
