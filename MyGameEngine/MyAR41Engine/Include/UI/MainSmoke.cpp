#include "MainSmoke.h"

CMainSmoke::CMainSmoke()
{
	m_WidgetTypeName = "MainSmoke";
}

CMainSmoke::CMainSmoke(const CMainSmoke& Image)	:
	CUIImage(Image)
{
	m_TextureInfo = Image.m_TextureInfo;
}

CMainSmoke::~CMainSmoke()
{
}

bool CMainSmoke::Init()
{
	CUIImage::Init();

	int TextureNum = rand() % 5;
	switch (TextureNum)
	{
	case 0:
		SetTexture("MainSmoke1", TEXT("HollowKnight/MainTitle/smoke1.png"));
		break;
	case 1:
		SetTexture("MainSmoke2", TEXT("HollowKnight/MainTitle/smoke2.png"));
		break;
	case 2:
		SetTexture("MainSmoke3", TEXT("HollowKnight/MainTitle/smoke3.png"));
		break;
	case 3:
		SetTexture("MainSmoke4", TEXT("HollowKnight/MainTitle/smoke4.png"));
		break;
	case 4:
		SetTexture("MainSmoke5", TEXT("HollowKnight/MainTitle/smoke5.png"));
		break;
	default:
		SetTexture("MainSmoke1", TEXT("HollowKnight/MainTitle/smoke1.png"));
		break;
	}
	SetPivot(0.5f, 0.5f);
	

	int Size = (rand() % 2)+2;
	SetSize(100.f * Size, 100.f * Size);
	
	int PosX = (rand() % 1280);
	//int PosY = (rand() % 120) * (-1);
	int PosY = (rand() % 50);

	SetPos((float)PosX, (float)PosY);

	SetOpacity(0.f);
	m_OpaReverse = false;
	return true;
}

void CMainSmoke::Update(float DeltaTime)
{
	CUIImage::Update(DeltaTime);

	SetOpacity(m_Opacity);
	m_Time += DeltaTime;
	
	if (!m_OpaReverse)
	{
		if (m_Opacity >= 0.9f)
			m_Opacity = 0.9f;
		else
			m_Opacity += DeltaTime * 5.f;				
	}			

	Vector2 Pos = GetPos();

	Pos.y += DeltaTime * 20.f;
	SetPos(Pos);

	if (m_Time >= 4.f)
	{
		m_OpaReverse = true;
		m_Opacity -= DeltaTime * 5.f;
		
		if (m_Opacity <= 0.f)
			Destroy();
	}	
}

void CMainSmoke::Render()
{
	CUIImage::Render();
}
