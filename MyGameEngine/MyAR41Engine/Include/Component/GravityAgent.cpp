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
	float PosX = m_Pos.x + (m_BodySize.x * 0.5f); //������ ��ǥ

	//float WallLeft = m_WallInfo.Left; // 0
	//float WallTop = m_WallInfo.Top; // 720
	//float WallRight = m_WallInfo.Right; // 1280
	//float WallBottom = m_WallInfo.Bottom; //0

	if ((int)PosX >= (int)m_WallInfo.Right)
	{
		m_SideWallCollision = true;
		m_UpdateComponent->SetWorldPositionX(m_WallInfo.Right - (m_BodySize.x*0.5f));
	}
	else
		m_SideWallCollision = false;
}

void CGravityAgent::CheckMoveLeft()
{
	//TODO	
	float PosX = m_Pos.x - (m_BodySize.x * 0.5f); //���� ��ǥ

	//float WallLeft = m_WallInfo.Left; // 0
	//float WallTop = m_WallInfo.Top; // 720
	//float WallRight = m_WallInfo.Right; // 1280
	//float WallBottom = m_WallInfo.Bottom; //0

	if ((int)PosX <= (int)m_WallInfo.Left)
	{
		m_SideWallCollision = true;
		m_UpdateComponent->SetWorldPositionX(m_WallInfo.Left + (m_BodySize.x * 0.5f));
	}
	else
		m_SideWallCollision = false;
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
	//�浹 ���� ��� ������
	
	//�� �� �ݶ��̴� �ڽ��� ���
	//�ݶ��̴��� ��� �Ǻ�

	//���� �ִ� �ݶ��̴� ��������
	if (m_Scene)
		m_Wall = (CCollider2D*)(m_Scene->FindObject("GlobalWall")->FindComponent("GlobalWall"));
	if (m_Wall)
	{
		m_WallSize = ((CColliderBox2D*)m_Wall.Get())->GetBoxSize();
		m_WallInfo = ((CColliderBox2D*)m_Wall.Get())->GetInfo();
	}
		
	//��ü
	m_Body = (CCollider2D*)m_Owner->FindComponent("Body");

	if (m_Body)
	{
		m_BodySize = ((CColliderBox2D*)m_Body.Get())->GetBoxSize();
		m_BodyInfo = ((CColliderBox2D*)m_Body.Get())->GetInfo();

		m_Pos = m_Body->GetWorldPos(); 
		m_Pos.y = m_Pos.y - (m_BodySize.y * 0.5f); //Center ���ؿ��� �ϴ� �Ǻ����� �ٲ���
		m_PrevPos = m_Pos;		
	}
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

	//�߷� ����
	if (m_UpdateComponent)
	{
		if (!m_Ground && m_PhysicsSimulate)
		{
			//�������� �ð� ����
			m_FallTime += DeltaTime * m_GravityAccel;

			// 9.8 m/s^2
			// t�� �� y��
			// V:�ӵ� A:���ӵ� G:�߷�
			// y = V * A - 0.5f * G * t * t
			// 0 = -0.5fGA^2 VA - y
			//���� �������� ������ ���� ������ �̿��ؼ� �ظ� ���ϸ� ����
			float Velocity = 0.f;

			if (m_Jump)
				Velocity = m_JumpVelocity;
				
			//�߷� ��
			float PosY = (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);
			m_UpdateComponent->AddWorldPosition(0, PosY);
		}
	}
}

void CGravityAgent::PostUpdate(float DeltaTime)
{
	CObjectComponent::PostUpdate(DeltaTime);

	//TODO
	m_Pos = m_Body->GetWorldPos();
	m_Pos.y = m_Pos.y - (m_BodySize.y * 0.5f);
    m_Move.x = m_Pos.x - m_PrevPos.x; //�̵� �Ÿ�
	m_Move.y = m_Pos.y + m_PrevPos.y;

	if (m_Pos.y < m_PrevPos.y)
	{
		m_FallingStart = true;
	}

	if (m_UpdateComponent && m_Wall)
	{
		if (m_Move.x != 0.f && m_SideWallCheck)
		{
			// ���������� �̵��Ҷ�
			if (m_Move.x > 0.f)
			{
				CheckMoveRight();				
			}

			// �������� �̵��Ҷ�
			else
			{
				CheckMoveLeft();
			}
		}
	}
	//�ٴڿ� ������Ų��.
		//&& m_Move.y <= 0.f
		if (m_PhysicsSimulate)
		{			
			//float   PrevBottom = m_PrevPos.y;
			//float   CurBottom = m_Pos.y;
			//float Bottom = m_Pos.y;

			//�� �� ��ǥ�� �΋H�� ��

			bool check = false;
			
			//���� ���� ��
			if ((int)m_Pos.y <= (int)m_WallInfo.Bottom)
			{
				check = true;
				m_FallTime = 0.f;
				m_JumpCount = 0;
				
				m_Owner->SetWorldPositionY(m_WallInfo.Bottom + (m_BodySize.y * 0.5f));
				m_Ground = true;
				m_FallingStart = false;
				m_Jump = false;
			}

			//�ٴ��� ���� ���
			if (!check)
			{
				if (m_Ground)
				{
				    m_FallTime = 0.f;
					m_FallStartY = m_Pos.y;
				}
				m_Ground = false;
			}
		}
		m_PrevPos = m_Pos;
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
  bool   m_Ground;           // ���� ��� �ִ� �������� �ƴ���
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
