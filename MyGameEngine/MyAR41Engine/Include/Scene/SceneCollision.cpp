#include "SceneCollision.h"
#include "CollisionSection2D.h"
#include "CollisionSection3D.h"
#include "../Device.h"
#include "../Component/Collider2D.h"
#include "../Component/Collider3D.h"

CSceneCollision::CSceneCollision()
{
}

CSceneCollision::~CSceneCollision()
{
	//섹션 구조체들 제거
	size_t	Count = m_Section2D.vecSection.size();

	for (size_t i = 0; i < Count; ++i)
	{
		SAFE_DELETE(m_Section2D.vecSection[i]);
	}

	Count = m_Section3D.vecSection.size();

	for (size_t i = 0; i < Count; ++i)
	{
		SAFE_DELETE(m_Section3D.vecSection[i]);
	}
}

void CSceneCollision::AddCollider(CCollider* Collider)
{
	m_ColliderList.push_back(Collider);
}

bool CSceneCollision::Init()
{
	float Width = (float)CDevice::GetInst()->GetResolution().Width;
	float Height = (float)CDevice::GetInst()->GetResolution().Height;

	//## 10x10 사이즈로 화면 해상도에 맞추어 영역을 분할한다.
	CreateSection2D(10, 10, Vector2(), Vector2(Width, Height));

	//CreateSection3D(5, 5, 5, Vector3(), Vector3(Width, Height));

	return true;
}

void CSceneCollision::Update(float DeltaTime)
{
	for (int i = 0; i < m_Section2D.Count; ++i)
	{
		m_Section2D.vecSection[i]->m_ColliderList.clear();
	}

	for (int i = 0; i < m_Section3D.Count; ++i)
	{
		m_Section3D.vecSection[i]->m_ColliderList.clear();
	}

	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		//물체가 죽으면 삭제해줌
		if (!(*iter)->GetActive())
		{
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}
		//비활성화 되있으면 삭제하진 않고 그냥 넘어감
		else if (!(*iter)->GetEnable())
		{
			// 이전프레임에 충돌되고 있던 물체가 있다면 해당 물체들에게 충돌이 해제되었다는 통보를
			// 보내야 한다.
			(*iter)->SendPrevCollisionEnd();

			++iter;
			continue;
		}

		//콜라이더들이 어느영역에 속해있는지 최신화
		CheckSection(*iter);
		++iter;
	}

	// 현재 충돌영역이 겹치는지 판단한다. 이전프레임에 충돌되고 있던 물체와 충돌영역이 겹치는게 없다면
	// 현재 프레임에서는 충돌체크 자체를 아예 안하고 충돌 가능성도 0% 이기 때문에 충돌하던 물체가 떨어졌다는
	// 처리를 진행해주어야 한다.
	iter = m_ColliderList.begin();
	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->CheckPrevCollisionColliderSection();
	}

	// 마우스와 먼저 충돌처리를 진행해야 한다.


	// 충돌체끼리 충돌처리를 진행한다.
	// 모든 Section을 반복하며 충돌처리를 수행한다.
	for (int i = 0; i < m_Section2D.Count; ++i)
	{
		m_Section2D.vecSection[i]->Collision(DeltaTime);
	}

	for (int i = 0; i < m_Section3D.Count; ++i)
	{
		m_Section3D.vecSection[i]->Collision(DeltaTime);
	}

	// 충돌처리가 완료되었다면 충돌체를 Clear해준다.
	iter = m_ColliderList.begin();
	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (!(*iter)->GetEnable())
			continue;

		(*iter)->ClearFrame();
	}
}

void CSceneCollision::CreateSection2D(int CountX, int CountY, const Vector2& WorldStart, const Vector2& SectionSize)
{
	//기존의 영역들은 밀어버림
	size_t	Count = m_Section2D.vecSection.size();

	for (size_t i = 0; i < Count; ++i)
	{
		SAFE_DELETE(m_Section2D.vecSection[i]);
	}

	m_Section2D.CountX = CountX;
	m_Section2D.CountY = CountY;
	m_Section2D.Count = CountX * CountY;
	m_Section2D.WorldStart = WorldStart;
	m_Section2D.SectionSize = SectionSize;
	m_Section2D.WorldSize = SectionSize * Vector2((float)CountX, (float)CountY);

	for (int i = 0; i < CountY; ++i)
	{
		for (int j = 0; j < CountX; ++j)
		{
			CCollisionSection2D* Section = new CCollisionSection2D;

			Section->m_Min = WorldStart + SectionSize * Vector2((float)j, (float)i);
			Section->m_Max = Section->m_Min + SectionSize;
			Section->m_IndexX = j;
			Section->m_IndexY = i;
			Section->m_Index = i * CountX + j;

			m_Section2D.vecSection.push_back(Section);
		}
	}
}

void CSceneCollision::CreateSection3D(int CountX, int CountY, int CountZ, const Vector3& WorldStart, const Vector3& SectionSize)
{
	size_t	Count = m_Section3D.vecSection.size();

	for (size_t i = 0; i < Count; ++i)
	{
		SAFE_DELETE(m_Section3D.vecSection[i]);
	}

	m_Section3D.CountX = CountX;
	m_Section3D.CountY = CountY;
	m_Section3D.CountZ = CountZ;
	m_Section3D.Count = CountX * CountY * CountZ;
	m_Section3D.WorldStart = WorldStart;
	m_Section3D.SectionSize = SectionSize;
	m_Section3D.WorldSize = SectionSize * Vector3((float)CountX, (float)CountY, (float)CountZ);

	for (int i = 0; i < CountZ; ++i)
	{
		for (int j = 0; j < CountY; ++j)
		{
			for (int k = 0; k < CountX; ++k)
			{
				CCollisionSection3D* Section = new CCollisionSection3D;

				Section->m_Min = WorldStart + SectionSize * Vector3((float)k, (float)j, (float)i);
				Section->m_Max = Section->m_Min + SectionSize;
				Section->m_IndexX = k;
				Section->m_IndexY = j;
				Section->m_IndexZ = i;
				Section->m_Index = i * CountX * CountY + j * CountX + k;

				m_Section3D.vecSection.push_back(Section);
			}
		}
	}
}

void CSceneCollision::Save(FILE* File)
{
}

void CSceneCollision::Load(FILE* File)
{
}

void CSceneCollision::CheckSection(CCollider* Collider)
{

	Vector3	Min = Collider->GetMin();
	Vector3	Max = Collider->GetMax();

	if (Collider->GetColliderType() == ECollider_Type::Collider2D)
	{
		//충돌체 Min과 0 인덱스의 Min(WorldStart)의 상대적인 거리를 구한다.
		Min -= Vector3(m_Section2D.WorldStart.x, m_Section2D.WorldStart.y, 0.f); // 충돌체 Min -= 월드스타트 Min
		Max -= Vector3(m_Section2D.WorldStart.x, m_Section2D.WorldStart.y, 0.f);

		int	IndexMinX, IndexMinY, IndexMaxX, IndexMaxY;

		
		IndexMinX = (int)(Min.x / m_Section2D.SectionSize.x);
		IndexMinY = (int)(Min.y / m_Section2D.SectionSize.y);

		IndexMaxX = (int)(Max.x / m_Section2D.SectionSize.x);
		IndexMaxY = (int)(Max.y / m_Section2D.SectionSize.y);

		//화면을 벗어났는지 예외처리
		IndexMinX = IndexMinX < 0 ? 0 : IndexMinX;
		IndexMinY = IndexMinY < 0 ? 0 : IndexMinY;

		IndexMaxX = IndexMaxX >= m_Section2D.CountX ? m_Section2D.CountX - 1 : IndexMaxX;
		IndexMaxY = IndexMaxY >= m_Section2D.CountY ? m_Section2D.CountY - 1 : IndexMaxY;

		for (int i = IndexMinY; i <= IndexMaxY; ++i)
		{
			for (int j = IndexMinX; j <= IndexMaxX; ++j)
			{
				//인자로 들어온 콜라이더가 어느 영역의 인덱스인지 도출
				int	Index = i * m_Section2D.CountX + j; 

				m_Section2D.vecSection[Index]->AddCollider((CCollider2D*)Collider);
			}
		}
	}

	else //3D타입일때
	{
		Min -= m_Section3D.WorldStart;
		Max -= m_Section3D.WorldStart;

		int	IndexMinX, IndexMinY, IndexMinZ, IndexMaxX, IndexMaxY, IndexMaxZ;

		IndexMinX = (int)(Min.x / m_Section3D.SectionSize.x);
		IndexMinY = (int)(Min.y / m_Section3D.SectionSize.y);
		IndexMinZ = (int)(Min.z / m_Section3D.SectionSize.z);

		IndexMaxX = (int)(Max.x / m_Section3D.SectionSize.x);
		IndexMaxY = (int)(Max.y / m_Section3D.SectionSize.y);
		IndexMaxZ = (int)(Max.z / m_Section3D.SectionSize.z);

		IndexMinX = IndexMinX < 0 ? 0 : IndexMinX;
		IndexMinY = IndexMinY < 0 ? 0 : IndexMinY;
		IndexMinZ = IndexMinZ < 0 ? 0 : IndexMinZ;

		IndexMaxX = IndexMaxX >= m_Section3D.CountX ? m_Section3D.CountX - 1 : IndexMaxX;
		IndexMaxY = IndexMaxY >= m_Section3D.CountY ? m_Section3D.CountY - 1 : IndexMaxY;
		IndexMaxZ = IndexMaxZ >= m_Section3D.CountZ ? m_Section3D.CountZ - 1 : IndexMaxZ;

		for (int i = IndexMinZ; i <= IndexMaxZ; ++i)
		{
			for (int j = IndexMinY; j <= IndexMaxY; ++j)
			{
				for (int k = IndexMinX; k <= IndexMaxX; ++k)
				{
					int	Index = i * m_Section3D.CountX * m_Section3D.CountY * +j * m_Section3D.CountX + k;

					m_Section3D.vecSection[Index]->AddCollider((CCollider3D*)Collider);
				}
			}
		}
	}
}
