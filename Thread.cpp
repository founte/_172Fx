#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include <iostream>

Thread::Thread() :m_handle(NULL),m_function(NULL),m_userData(NULL)
{

}


Thread::Thread(Thread::FuncType Function, void* UserData) : m_handle  (NULL), m_function(Function), m_userData(UserData)
{

}


Thread::~Thread()
{
    // Wait for the thread to finish before destroying the instance
    Wait();
}


bool Thread::Launch()
{
    // Wait for the thread to finish, in case it was already running
    Wait();

    // Create the thread
    m_handle = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &Thread::ThreadFunc, this, 0, NULL));

    // Error ?
    if (m_handle == NULL)
	{
        std::cerr << "Failed to create thread" << std::endl;
		return false;
	}
	return true;
}


void Thread::Wait()
{
    if (m_handle)
    {
        // Wait for the thread to finish, no timeout
        WaitForSingleObject(m_handle, INFINITE);

        // Don't forget to close the thread handle (__endthreadex doesn't do it)
        CloseHandle(m_handle);
        m_handle = NULL;
    }
}


void Thread::Terminate()
{
    if (m_handle)
    {
        TerminateThread(m_handle, 0);
        m_handle = NULL;
    }
}

void Thread::Run()
{
    if (m_function)
        m_function(m_userData);
}


////////////////////////////////////////////////////////////
/// Actual thread entry point, dispatches to instances
////////////////////////////////////////////////////////////
unsigned int __stdcall Thread::ThreadFunc(void* UserData)
{
    // The Thread instance is stored in the user data
    Thread* ThreadInstance = reinterpret_cast<Thread*>(UserData);

    // Forward to the instance
    ThreadInstance->Run();

    // Optional, but it is cleaner
    _endthreadex(0);

    return 0;
}