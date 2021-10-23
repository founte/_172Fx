#ifndef THREAD_H
#define THREAD_H

#include <windows.h>

class Thread
{
public :

    typedef void (*FuncType)(void*);
    Thread(FuncType Function, void* UserData = NULL);
    virtual ~Thread();
    bool Launch();
    void Wait();
    void Terminate();
	void Suspend()
	{
		SuspendThread(m_handle);
	}
	void Resume()
	{
		ResumeThread(m_handle);
	}
protected :
    Thread();

private :
    virtual void Run();
    static unsigned int __stdcall ThreadFunc(void* UserData);

 
    HANDLE   m_handle;   
    FuncType m_function;
    void*    m_userData;
};




#endif //THREAD_H