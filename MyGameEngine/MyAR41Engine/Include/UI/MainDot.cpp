#include "MainDot.h"
#include <time.h>

CMainDot::CMainDot()
{
	m_WidgetTypeName = "MainDot";
}

CMainDot::CMainDot(const CMainDot& Image)	:
	CUIImage(Image)
{
	m_TextureInfo = Image.m_TextureInfo;
}

CMainDot::~CMainDot()
{
	//m_DotCount -= 1;
}

bool CMainDot::Init()
{
	CUIImage::Init();
	SetTexture("MainDot", TEXT("HollowKnight/MainTitle/particle_01.png"));
	SetPivot(0.5f, 0.5f);

	int PosX = (rand() % 980) + 150;
	int PosY = (rand() % 150);

	SetPos((float)PosX, (float)PosY);

	int Size = (rand() % 20) + 10;

	SetSize((float)Size, (float)Size);

	//m_DotCount += 1;

	return true;
}

void CMainDot::Update(float DeltaTime)
{
	CUIImage::Update(DeltaTime);

	m_Time += DeltaTime;

	Vector2 Pos = GetPos();
	
	Pos.y += DeltaTime * 50.f;
	SetPos(Pos);

	if (m_Time >= 2.f)
	{	
		Vector2 Size = GetSize();
		Size -= 10.f * DeltaTime;
		SetSize(Size);
		

		if (Size.x < 0.f)
			Destroy();
	}	
}

void CMainDot::Render()
{
	CUIImage::Render();
}


