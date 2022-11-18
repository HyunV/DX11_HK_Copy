#include "GravityAgent.h"
#include "SceneComponent.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"
#include "ColliderBox2D.h"
#include "ColliderOBB2D.h"
#include "ColliderSphere2D.h"
//#include "ColliderPixel.h"


CGravityAgent::CGravityAgent()	:
	m_PhysicsSimulate(false),
	m_Ground(false),
	m_GravityAccel(10.f),
	m_FallTime(0.f),
	m_FallStartY(0.f),
	m_Jump(false),
	m_JumpVelocity(0.f),
	m_SideWallCheck(true)
{
	m_ComponentType = ComponentType::Object;

	SetTypeID<CGravityAgent>();

	m_ComponentTypeName = "GravityAgent";
}

CGravityAgent::CGravityAgent(const CGravityAgent& Obj)	:
	CObjectComponent(Obj)
{	
	m_PhysicsSimulate = Obj.m_PhysicsSimulate;
	m_Ground = Obj.m_Ground;
	m_GravityAccel = Obj.m_GravityAccel;
	m_FallTime = Obj.m_FallTime;
	m_FallStartY = Obj.m_FallStartY;
	m_Jump = Obj.m_Jump;
	m_JumpVelocity = Obj.m_JumpVelocity;
	m_SideWallCheck = Obj.m_SideWallCheck;

}

CGravityAgent::~CGravityAgent()
{
}

void CGravityAgent::SetUpdateComponent(CSceneComponent* Component)
{
	m_UpdateComponent = Component;
}

void CGravityAgent::CheckMoveRight()
{
	//TODO
}

void CGravityAgent::CheckMoveLeft()
{
	//TODO
}

void CGravityAgent::Destroy()
{
	CObjectComponent::Destroy();
}

void CGravityAgent::Start()
{
	CObjectComponent::Start();

	if (!m_UpdateComponent)
		m_UpdateComponent = m_Owner->GetRootComponent();

	//TODO
}

bool CGravityAgent::Init()
{
	if (!CObjectComponent::Init())
		return false;

	return true;
}

void CGravityAgent::Update(float DeltaTime)
{
	CObjectComponent::Update(DeltaTime);

	//중력 적용
	if (m_UpdateComponent)
	{
		if (!m_Ground && m_PhysicsSimulate)
		{
			//떨어지는 시간 누적
			m_FallTime += DeltaTime * m_GravityAccel;

			// 9.8 m/s^2
			// t초 후 y값
			// V:속도 A:가속도 G:중력
			// y = V * A - 0.5f * G * t * t
			// 0 = -0.5fGA^2 VA - y
			//이차 방정식이 나오니 근의 공식을 이용해서 해를 구하면 좋음
			float Velocity = 0.f;

			if (m_Jump)
				Velocity = m_JumpVelocity * m_FallTime;
				
			//중력 식
			//float PosY = m_FallStartY - (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);
			m_UpdateComponent->SetWorldPositionY(m_FallStartY + (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime));
		}
	}
}

void CGravityAgent::PostUpdate(float DeltaTime)
{
	CObjectComponent::PostUpdate(DeltaTime);

	//TODO
    m_Pos = m_Body->GetWorldPos();
    m_Move = m_Pos - m_PrevPos;

    //if (m_UpdateComponent && m_TileMap)
    //{
    //    if (m_Move.x != 0.f && m_SideWallCheck)
    //    {
    //        // 오른쪽으로 이동할때
    //        if (m_Move.x > 0.f)
    //        {
    //            CheckMoveRight();
    //        }

    //        // 왼쪽으로 이동할때
    //        else
    //        {
    //            CheckMoveLeft();
    //        }
    //    }

        // 바닥에 착지시킨다.
	// 바닥에 착지시킨다.
		if (m_PhysicsSimulate && m_Move.y >= 0.f)
		{
			//CTileMap* TileMap = m_Scene->GetTileMap();

			float	PrevBottom = m_PrevPos.y + (1.f - m_BodyPivot.y) * m_BodySize.y;
			float	CurBottom = m_Pos.y + (1.f - m_BodyPivot.y) * m_BodySize.y;

			float	PrevLeft = m_PrevPos.x - m_BodyPivot.x * m_BodySize.x;
			float	CurLeft = m_Pos.x - m_BodyPivot.x * m_BodySize.x;

			float	PrevRight = m_PrevPos.x + (1.f - m_BodyPivot.x) * m_BodySize.x;
			float	CurRight = m_Pos.x + (1.f - m_BodyPivot.x) * m_BodySize.x;

			float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
			float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
			float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
			float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

			int LeftIndex = TileMap->GetTileOriginIndexX(ResultLeft);
			int RightIndex = TileMap->GetTileOriginIndexX(ResultRight);
			int TopIndex = TileMap->GetTileOriginIndexY(ResultTop);
			int BottomIndex = TileMap->GetTileOriginIndexY(ResultBottom);

			LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
			TopIndex = TopIndex < 0 ? 0 : TopIndex;
			RightIndex = RightIndex > TileMap->GetCountX() - 1 ? TileMap->GetCountX() - 1 : RightIndex;
			BottomIndex = BottomIndex > TileMap->GetCountY() - 1 ? TileMap->GetCountY() - 1 : BottomIndex;

			if (LeftIndex <= TileMap->GetCountX() - 1 && TopIndex <= TileMap->GetCountY() - 1 &&
				RightIndex >= 0 && BottomIndex >= 0)
			{
				bool	Check = false;

				// 위에서 아래로 차례로 검사를 해나간다.
				// 아래에서부터 하게 되면 위에 벽이 있을 경우 무시하고 처리되버릴 수도 있기 때문이다.
				for (int i = TopIndex; i <= BottomIndex; ++i)
				{
					for (int j = LeftIndex; j <= RightIndex; ++j)
					{
						CTile* Tile = TileMap->GetTile(j, i);

						if (!Tile)
							continue;

						/*if (Tile->GetPos().y < PrevBottom)
							continue;*/

							// 현재 타일이 이동불가 타일일 경우 바닥을 밟았다는 것이다.
						if (Tile->GetOption() == ETile_Option::ImpossibleToMove)
						{
							Check = true;
							m_FallTime = 0.f;

							m_JumpCount = 0;

							// 현재 타일의 Top을 이 오브젝트의 Bottom값으로 지정한다.
							m_Pos.y = Tile->GetPos().y - (1.f - m_Pivot.y) * m_Size.y;
							m_Ground = true;
							m_Jump = false;
							break;
						}
					}

					if (Check)
						break;
				}

				// 바닥이 없을 경우
				if (!Check)
				{
					// 땅을 밟고 있던 상태라면 이제 떨어지는 상태가 될것이다.
					if (m_Ground)
					{
						m_FallTime = 0.f;
						m_FallStartY = m_Pos.y;
					}

					m_Ground = false;
				}
			}
		}
}

void CGravityAgent::Render()
{
    CObjectComponent::Render();
}

CGravityAgent* CGravityAgent::Clone() const
{
    return new CGravityAgent(*this);



}

void CGravityAgent::Render()
{
	CObjectComponent::Render();
}

CGravityAgent* CGravityAgent::Clone() const
{
	return new CGravityAgent(*this);
}

void CGravityAgent::Save(FILE* File)
{
	CObjectComponent::Save(File);

	/*
 bool   m_PhysicsSimulate;
  bool   m_Ground;           // 땅을 밟고 있는 상태인지 아닌지
  float   m_GravityAccel;
  float   m_FallTime;
  float   m_FallStartY;
  bool   m_Jump;
  float   m_JumpVelocity;
  bool   m_SideWallCheck;
 */

 //int Length = (int)m_UpdateComponent->GetName().length();
 //fwrite(&Length, sizeof(int), 1, File);

 //fwrite(m_UpdateComponent->GetName().c_str(), 1, Length, File);

 //fwrite(&m_PhysicsSimulate, sizeof(bool), 1, File);
 //fwrite(&m_Ground, sizeof(bool), 1, File);
 //fwrite(&m_GravityAccel, sizeof(float), 1, File);
 //fwrite(&m_FallTime, sizeof(float), 1, File);
 //fwrite(&m_FallStartY, sizeof(float), 1, File);
 //fwrite(&m_Jump, sizeof(bool), 1, File);
 //fwrite(&m_JumpVelocity, sizeof(float), 1, File);
 //fwrite(&m_SideWallCheck, sizeof(bool), 1, File);

}

void CGravityAgent::Load(FILE* File)
{
	CObjectComponent::Load(File);

	//int Length = 0;
	//fread(&Length, sizeof(int), 1, File);

	//char   ComponentName[256] = {};
	//fread(ComponentName, 1, Length, File);

	//CSceneComponent* UpdateComponent = (CSceneComponent*)m_Owner->FindComponent(ComponentName);
	//SetUpdateComponent(UpdateComponent);

	//fread(&m_PhysicsSimulate, sizeof(bool), 1, File);
	//fread(&m_Ground, sizeof(bool), 1, File);
	//fread(&m_GravityAccel, sizeof(float), 1, File);
	//fread(&m_FallTime, sizeof(float), 1, File);
	//fread(&m_FallStartY, sizeof(float), 1, File);
	//fread(&m_Jump, sizeof(bool), 1, File);
	//fread(&m_JumpVelocity, sizeof(float), 1, File);
	//fread(&m_SideWallCheck, sizeof(bool), 1, File);

}
