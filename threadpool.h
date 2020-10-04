#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include<string>
#include<atomic>
#include<list>
#include<vector>
#include<thread>
#include<mutex>
#include<condition_variable>
class threadPool
{
public:
	explicit threadPool(int n);
public:
	virtual ~threadPool();
public:
	bool Create(); //创造线程
	void Call();   //唤醒一个线程
	void inMsgeQueue(std::string);
	void stopAll();
	void threadwait();
public:
	static bool shoutDown;
	int workerthreadNum;
	std::atomic<int>ThreadRuningCount;
	std::vector<std::thread>threadVec;
	std::list<std::string>MsgQueueList; //这是消息队列可以放其他类型，如果放的是指针要记得释放内存这里为了演示就放string线程将其拿出打印；
private:
  static std::condition_variable threadCond;
  static std::mutex              threadMutex;

public:
	struct m_thread
	{
	public:
		threadPool* pthis;
		bool    iffalse;
		m_thread(threadPool* _this) :pthis(_this),iffalse(false)
		{

		}
	};
public:
	std::vector<m_thread*>m_threadVec;
  static void* OutMsgThread(void* p_Thread);
};

#endif
