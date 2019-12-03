#include<iostream>
#include<Poco/Thread.h>
#include<Poco/Runnable.h>
class A:public Poco::Runnable{
	virtual void run(){
		for(int i=0;i<8;i++){
			std::cout<<"A():["<<Poco::Thread::current()->name()<<"]["<<Poco::Thread::currentTid()<<"]"<<std::endl;
			Poco::Thread::sleep(100);
		}
	}
};
int main(int argc, char** argv){
	Poco::Thread t("t0");
	A a;
	t.start(a);
	std::cout<<"main"<<std::endl;
	t.join();
	return 0;
}
