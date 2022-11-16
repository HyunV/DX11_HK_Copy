#include "UIImageBlack.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CUImageBlack::CUImageBlack()	:
	m_check(false),
	m_Fade(EFade::None),
	m_Time(0.f),
	m_Count(0.f),
	m_Scale(1.f)
{
	m_WidgetTypeName = "UIImageBlack";
}

CUImageBlack::CUImageBlack(const CUImageBlack& Image)	:
	CUIImage(Image),
	m_check(false),
	m_Fade(EFade::None),
	m_Time(0.f),
	m_Count(0.f),
	m_Scale(1.f)
{
	m_TextureInfo = Image.m_TextureInfo;
}

CUImageBlack::~CUImageBlack()
{

}

void CUImageBlack::StartFade(EFade Fade, float Time)
{
	//Fade ȿ�� 
	//���� ���̵���, none�� ����
	
	/*
	None, ȿ�� ����
	FadeIn, //���� ȭ�鿡�� ������°�
	FadeOut, //���� ��ο����°�
	NoEffect,
	*/
	this->SetOpacity(1.f);
	
	m_Fade = Fade;
	m_Time = Time;

	m_check = true;
}

void CUImageBlack::Start()
{
	CUIImage::Start();
}

bool CUImageBlack::Init()
{
	CUIImage::Init();
	
	this->SetTexture("BlackLayer", TEXT("HollowKnight/MainTitle/BlackLayer.png"));
	this->SetSize(1280.f, 720.f);
	//Opacity 1: ���� 0  // 0:���� 100

	return true;
}

void CUImageBlack::Update(float DeltaTime)
{
	CUIImage::Update(DeltaTime);
	
	if (m_check)
	{
		float Per = (m_Time / 100.f); // 0.05 �� �� ���������� 1 ����

		m_Count += DeltaTime;
		if (m_Count > Per)
		{

		}

		this->m_Opacity -= Per;
		if(m_Count > m_Time)
		{	
			if(this->m_Opacity == 0.f)
				this->Destroy();
		}	
	}
}

void CUImageBlack::PostUpdate(float DeltaTime)
{
	CUIImage::PostUpdate(DeltaTime);
}

void CUImageBlack::Render()
{
	CUIImage::Render();
}

CUImageBlack* CUImageBlack::Clone()
{
	return new CUImageBlack(*this);
}

void CUImageBlack::Save(FILE* File)
{
	CUIImage::Save(File);
}

void CUImageBlack::Load(FILE* File)
{
	CUIImage::Load(File);
}
