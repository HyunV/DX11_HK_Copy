#pragma once

#include "../EngineInfo.h"
#include "../Resource/Animation/AnimationSequence2D.h"

struct Animation2DNotify
{
	std::string Name;
	int		Frame;
	float	Time;
	bool	Call;
	std::function<void()>	Function;

	Animation2DNotify() :
		Frame(0),
		Time(0.f),
		Call(false)
	{
	}
};

class CAnimation2DData
{
	friend class CAnimation2D;

private:
	CAnimation2DData();
	CAnimation2DData(const CAnimation2DData& Anim);
	~CAnimation2DData();

private:
	std::string m_Name;
	std::string m_SequenceName;
	CSharedPtr<CAnimationSequence2D>	m_Sequence;
	int		m_Frame;		//현재 애니메이션이 동작되는 프레임
	float	m_Time;			//애니메이션 프레임을 증가시켜주기 위한 시간값
	float	m_FrameTime;	//한 프레임이 증가하기 위한 시간
	float	m_PlayTime;		//모션 한번이 동작되기 위한 시간.
	float	m_PlayScale;	//재생속도 배율
	bool	m_Loop;			//반복 여부
	bool	m_Reverse;		//역재생 여부
	std::function<void()>	m_EndFunction; //애니메이션이 끝날때마다 호출될 함수
	std::vector<Animation2DNotify*> m_vecNotify; //특정 프레임에 호출될 정보들

public:
	void SetSequence(CAnimationSequence2D* Sequence);
	void Save(FILE* File);
	void Load(FILE* File);
	CAnimation2DData* Clone();

public:
	const std::string& GetName()	const
	{
		return m_Name;
	}

	int GetCurrentFrame()	const
	{
		return m_Frame;
	}

	float GetAnimationTime()	const
	{
		return m_Time;
	}

	class CAnimationSequence2D* GetAnimationSequence() const
	{
		return m_Sequence;
	}

public:
	template <typename T>
	void SetEndFunction(T* Obj, void(T::* Func)())
	{
		m_EndFunction = std::bind(Func, Obj);
	}

	template <typename T> //Notify, 프레임단위
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
	{
		Animation2DNotify* Notify = new Animation2DNotify;

		Notify->Name = Name;
		Notify->Frame = Frame;
		Notify->Time = Frame * m_FrameTime;
		Notify->Function = std::bind(Func, Obj);

		m_vecNotify.push_back(Notify);
	}

	template <typename T> //Notify, 초단위
	void AddNotify(const std::string& Name, float Time, T* Obj, void(T::* Func)())
	{
		Animation2DNotify* Notify = new Animation2DNotify;

		Notify->Name = Name;
		Notify->Frame = Time / m_FrameTime;
		Notify->Time = Time;
		Notify->Function = std::bind(Func, Obj);

		m_vecNotify.push_back(Notify);
	}
};

