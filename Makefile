OBJS=threadpool.o main.o
main:$(OBJS)
	g++ -o main $(OBJS) -std=c++11 -lpthread
threadpool.o:threadpool.cxx threadpool.h
	g++ -c threadpool.cxx -std=c++11 -lpthread
main.o:main.cxx threadpool.h
	g++ -c main.cxx -std=c++11 -lpthread
clean:
	-rm -f main $(OBJS)
