#include "UIImageBlack.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CUImageBlack::CUImageBlack()
{
	m_WidgetTypeName = "UIImageBlack";
}

CUImageBlack::CUImageBlack(const CUImageBlack& Image)	:
	CUIImage(Image)
{
	m_TextureInfo = Image.m_TextureInfo;
}

CUImageBlack::~CUImageBlack()
{

}

void CUImageBlack::StartFade(EFade FadeType, float PlayTime)
{
	//Fade ȿ�� 
	//���� ���̵���, none�� ����
	
	/*
	None, ȿ�� ����
	FadeIn, //���� ȭ�鿡�� ������°�
	FadeOut, //���� ��ο����°�
	*/
	switch (FadeType)
	{
	case EFade::FadeIn:
		m_FadeType = EFade::FadeIn;
		this->SetOpacity(1.f);
		break;
	case EFade::FadeOut:
		m_FadeType = EFade::FadeOut;
		this->SetOpacity(0.f);
		break;
	default:
		return;
		break;
	}
	
	m_PlayTime = PlayTime;
	m_Time = 0.f;
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
		m_Time += DeltaTime;
		float num = (1.f / m_PlayTime);
		float Opa = GetOpacity();
		Opa -= DeltaTime;
		
		switch (m_FadeType)
		{
		case EFade::FadeIn: //opacity 1 -> 0
				this->SetOpacity(Opa);
			break;
		case EFade::FadeOut: //opacity 0 -> 1
			this->SetOpacity(m_Time / m_PlayTime);
			break;
		default:
			break;
		}
		if (m_Time >= m_PlayTime)
			this->Destroy();
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
