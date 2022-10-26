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
    //* ����Ÿ���� DWORD unsigned long�� �Ǿ�����
    //* ������� ������� ī��Ʈ��°� ���� �־ ȣ���ϸ� 1�� �þ�� ���
    //* �� �Ͻ������� ȣ���ϸ� 1�� �����ϰ� ����� ������ �ϸ� 1�� �����ϴ� ���
    //* �Ͻ������� �������� 3�� ȣ���ϸ� ����۵� 3�� ȣ�����־�� �ٽ� �۵���. 
    SuspendThread(m_Thread);
}

void CThread::Resume()
{
    //�굵 DWORD ��ȯ���� �Ǿ��־ �� �Լ��� �۵��ϸ� ������� ī��Ʈ�� 1 ���ҽ�Ų���� ��ȯ
    ResumeThread(m_Thread);
}

void CThread::ReStart()
{
    DWORD   Count = 0;

    do
    {
        //* �ѹ��� ������ �������ϴ� do while
        Count = ResumeThread(m_Thread);
    } while (Count > 0);
}

void CThread::Stop()
{
    if (m_Thread)
    {
        m_Loop = false;
        Start(); //Ȥ�� �𸣴� �̺�Ʈ �ο�

        // �����尡 ����ɶ����� ��ٸ���. ���ᵵ �̺�Ʈ�� ����� �ϸ� �ȵ�
        WaitForSingleObject(m_Thread, INFINITE);
        CloseHandle(m_Thread);
        m_Thread = 0;
    }
}

void CThread::Start()
{
    //��ȣ�� �ִ� �Լ� ���⼭ ������ �Լ��ʿ� WaitForSingleObject�� �������ͼ� ���� �����Ѵ�.
    SetEvent(m_StartEvent);
}

bool CThread::Init()
{
    //�̺�Ʈ ����ȭ�� �ܼ��ϰ� ��ȣ�� �ִ�, ���ٷ� �Ǵ���
    m_StartEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    //������ �Լ����� return 0�� ��ȯ ������ ��ȣ�� �ִ� ���°� ��(���� �̺�Ʈ)
    m_Thread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunction,
        (void*)this, 0, nullptr);
    //beginthreadex(
    //��ť��Ƽ-> null, 
    //���û�����->0���� ����, 
    //�� �Լ� ������->������ ��� 
    //Arglist->���ڷ� ������ ����Ʈ
    //init �÷���(�ٷ� �۵�����, �Ͻ����� �� �� �Ǵ��� ������->this
    //?: 0
    //?: nullptr

    return true;
}

unsigned int __stdcall CThread::ThreadFunction(void* Arg)
{
    CThread* Thread = (CThread*)Arg;

    //��ȣ�� ���� ������ ����ϴ� �Լ�
    WaitForSingleObject(Thread->m_StartEvent, INFINITE);

    do
    {
        Thread->Run();
    } while (Thread->m_Loop);

    return 0; //������ �����ϴ� �Լ� ����
}
