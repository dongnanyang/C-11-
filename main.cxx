#include"threadpool.h"
#include<sstream>
int main(int argc, char* argv[])
{
	threadPool p(10);
	p.Create();
	for (int i = 0; i < 100; ++i)
	{
		std::stringstream sql;
		sql << i;
		p.inMsgeQueue(sql.str());
	}
	p.threadwait();
	return 0;
}
