#include "Thread.h"

CThread::CThread() :
    m_Loop(false)
{
}

CThread::~CThread()
{
}

void CThread::Suspend()
{
    //* 리턴타입이 DWORD unsigned long로 되어있음
    //* 스레드는 서스펜드 카운트라는걸 갖고 있어서 호출하면 1씩 늘어나는 방식
    //* 즉 일시정지를 호출하면 1씩 증가하고 재시작 같은걸 하면 1씩 감소하는 방식
    //* 일시정지를 연속으로 3번 호출하면 재시작도 3번 호출해주어야 다시 작동됨. 
    SuspendThread(m_Thread);
}

void CThread::Resume()
{
    //얘도 DWORD 반환으로 되어있어서 이 함수를 작동하면 서스펜드 카운트를 1 감소시킨값을 반환
    ResumeThread(m_Thread);
}

void CThread::ReStart()
{
    DWORD   Count = 0;

    do
    {
        //* 한번은 무조건 돌려야하니 do while
        Count = ResumeThread(m_Thread);
    } while (Count > 0);
}

void CThread::Stop()
{
    if (m_Thread)
    {
        m_Loop = false;
        Start(); //혹시 모르니 이벤트 부여

        // 스레드가 종료될때까지 기다린다. 종료도 이벤트라 맘대로 하면 안됨
        WaitForSingleObject(m_Thread, INFINITE);
        CloseHandle(m_Thread);
        m_Thread = 0;
    }
}

void CThread::Start()
{
    //신호를 주는 함수 여기서 스레드 함수쪽에 WaitForSingleObject를 빠져나와서 일을 수행한다.
    SetEvent(m_StartEvent);
}

bool CThread::Init()
{
    //이벤트 동기화는 단순하게 신호가 있다, 없다로 판단함
    m_StartEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    //스레드 함수에서 return 0을 반환 받으면 신호가 있는 상태가 됨(종료 이벤트)
    m_Thread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunction,
        (void*)this, 0, nullptr);
    //beginthreadex(
    //시큐리티-> null, 
    //스택사이즈->0으로 고정, 
    //쓸 함수 포인터->스레드 펑션 
    //Arglist->인자로 전달할 리스트
    //init 플래그(바로 작동할지, 일시정지 할 지 판단할 스레드->this
    //?: 0
    //?: nullptr

    return true;
}

unsigned int __stdcall CThread::ThreadFunction(void* Arg)
{
    CThread* Thread = (CThread*)Arg;

    //신호가 있을 때까지 대기하는 함수
    WaitForSingleObject(Thread->m_StartEvent, INFINITE);

    do
    {
        Thread->Run();
    } while (Thread->m_Loop);

    return 0; //스레드 동작하는 함수 종료
}
