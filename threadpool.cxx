#include "threadpool.h"
#include<iostream>
using namespace std;
bool threadPool::shoutDown = false;
condition_variable threadPool::threadCond;
mutex              threadPool::threadMutex;
threadPool::threadPool(int n) :workerthreadNum(n), ThreadRuningCount(0)
{

}

threadPool::~threadPool()
{
	//std::vector<struct m_thread*>::iterator pos;
	for (auto pos = m_threadVec.begin(); pos != m_threadVec.end(); ++pos)
	{
		delete (*pos);
	}
	m_threadVec.clear();
}

bool threadPool::Create()
{
	int n = workerthreadNum;
	for (int i = 0; i < n; ++i)
	{
		m_thread* pNew=new m_thread(this);
		m_threadVec.push_back(pNew);
		threadVec.push_back(std::thread(&threadPool::OutMsgThread,pNew));
	}
lblThreadRunSuccessfual:
	//std::vector<m_thread*>::iterator pos, posend;
	auto pos = m_threadVec.begin();
	auto posend = m_threadVec.end();
	for (; pos != posend; ++pos)
	{
		if ((*pos)->iffalse == false)
			goto lblThreadRunSuccessfual;
	}
	return true;
}

void threadPool::inMsgeQueue(string c)
{
	unique_lock<mutex>(threadMutex);
	MsgQueueList.push_back(c);
	Call();
}

void threadPool::Call()
{
	threadCond.notify_one();
	if (ThreadRuningCount == workerthreadNum)
	{
		cout << "线程池正在扩容" << endl;
		for (int i = 0; i < 50; ++i)
		{
			m_thread* pNew;
			m_threadVec.push_back(pNew = new m_thread(this));
			threadVec.push_back(thread(&threadPool::OutMsgThread, pNew));
		}
	}

}

void threadPool::stopAll()
{
	if (shoutDown == true)
	{
		return;
	}
	shoutDown = true;
	threadCond.notify_all();
}

void* threadPool::OutMsgThread(void*pthread)
{
	m_thread* pThread = static_cast<m_thread*>(pthread);
	threadPool* pool = pThread->pthis;
	while (true)
	{
		unique_lock<mutex>myguard(threadMutex);
		if (pThread->iffalse == false)
		{
			pThread->iffalse = true;
		}
		threadCond.wait(myguard, [&]() {
			if (shoutDown == false && pool->MsgQueueList.empty())
				return false;
			return true;
			});
		if (shoutDown == true)
		{
			myguard.unlock();
			break;
		}
		string ptmp;
		ptmp = pool->MsgQueueList.front();
		pool->ThreadRuningCount++;
		cout << ptmp << endl;
		//在这里做具体的业务
		pool->MsgQueueList.pop_front();
		myguard.unlock();
		pool->ThreadRuningCount--;
	}
	return(void*)0;
}

void threadPool::threadwait()
{
	std::vector<thread>::iterator pos;
	for (pos = threadVec.begin(); pos != threadVec.end(); ++pos)
	{
		(*pos).join();
	}
	threadVec.clear();
}
