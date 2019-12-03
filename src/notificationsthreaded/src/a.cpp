#include<iostream>
#include<thread>
#include<chrono>
#include<Poco/Notification.h>
#include<Poco/NotificationQueue.h>
#include<Poco/ThreadPool.h>
#include<Poco/Runnable.h>
#include<Poco/AutoPtr.h>
#include<Poco/Stopwatch.h>
class WorkNotification:public Poco::Notification{
	public:
		WorkNotification(int data):_data(data){}
		int data()const{
			return _data;
		}
	private:
		int _data;
};
class Worker:public Poco::Runnable{
	public:
		Worker(Poco::NotificationQueue& queue):_queue(queue){}
		void run(){
			Poco::AutoPtr<Poco::Notification> pNf(_queue.waitDequeueNotification());
			while(pNf){
				WorkNotification* pWorkNf=dynamic_cast<WorkNotification*>(pNf.get());
				if(pWorkNf){
					//std::cout<<"working["<<pWorkNf->data()<<"]"<<"["<<Poco::ThreadPool::defaultPool().allocated()<<"]"<<std::endl;
					for(int i=0;i<4096*4096;i++){
					}
					//Poco::Thread::sleep(100);
					//std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				pNf=_queue.waitDequeueNotification();
			}
		}
	private:
		Poco::NotificationQueue& _queue;
};
int main(int argc, char** argv){
	int nitr=128;
	{
		Poco::Stopwatch sw;
		sw.start();
		Poco::NotificationQueue queue;
		Worker worker1(queue);
		Poco::ThreadPool::defaultPool().start(worker1);
		for(int i=0;i<nitr;++i){
			queue.enqueueNotification(new WorkNotification(i));
		}
		while(!queue.empty())
			Poco::Thread::sleep(1000);
		queue.wakeUpAll();
		///std::cout<<Poco::ThreadPool::defaultPool().available()<<std::endl;
		Poco::ThreadPool::defaultPool().joinAll();
		std::cout<<"dur: "<<sw.elapsed()/1000<<" ms"<<std::endl;
	}
	{
		Poco::Stopwatch sw;
		sw.start();
		Poco::NotificationQueue queue;
		Worker worker1(queue);
		Worker worker2(queue);
		Poco::ThreadPool::defaultPool().start(worker1);
		Poco::ThreadPool::defaultPool().start(worker2);
		for(int i=0;i<nitr;++i){
			queue.enqueueNotification(new WorkNotification(i));
		}
		while(!queue.empty())
			Poco::Thread::sleep(1000);
		queue.wakeUpAll();
		///std::cout<<Poco::ThreadPool::defaultPool().available()<<std::endl;
		Poco::ThreadPool::defaultPool().joinAll();
		std::cout<<"dur: "<<sw.elapsed()/1000<<" ms"<<std::endl;
	}
	{
		Poco::Stopwatch sw;
		sw.start();
		Poco::NotificationQueue queue;
		Worker worker1(queue);
		Worker worker2(queue);
		Worker worker3(queue);
		Worker worker4(queue);
		Poco::ThreadPool::defaultPool().start(worker1);
		Poco::ThreadPool::defaultPool().start(worker2);
		Poco::ThreadPool::defaultPool().start(worker3);
		Poco::ThreadPool::defaultPool().start(worker4);
		for(int i=0;i<nitr;++i){
			queue.enqueueNotification(new WorkNotification(i));
		}
		while(!queue.empty())
			Poco::Thread::sleep(1000);
		queue.wakeUpAll();
		///std::cout<<Poco::ThreadPool::defaultPool().available()<<std::endl;
		Poco::ThreadPool::defaultPool().joinAll();
		std::cout<<"dur: "<<sw.elapsed()/1000<<" ms"<<std::endl;
	}
	{
		Poco::Stopwatch sw;
		sw.start();
		Poco::NotificationQueue queue;
		Worker worker1(queue);
		Worker worker2(queue);
		Worker worker3(queue);
		Worker worker4(queue);
		Worker worker5(queue);
		Worker worker6(queue);
		Worker worker7(queue);
		Worker worker8(queue);
		Poco::ThreadPool::defaultPool().start(worker1);
		Poco::ThreadPool::defaultPool().start(worker2);
		Poco::ThreadPool::defaultPool().start(worker3);
		Poco::ThreadPool::defaultPool().start(worker4);
		Poco::ThreadPool::defaultPool().start(worker5);
		Poco::ThreadPool::defaultPool().start(worker6);
		Poco::ThreadPool::defaultPool().start(worker7);
		Poco::ThreadPool::defaultPool().start(worker8);
		for(int i=0;i<nitr;++i){
			queue.enqueueNotification(new WorkNotification(i));
		}
		while(!queue.empty())
			Poco::Thread::sleep(100);
		queue.wakeUpAll();
		///std::cout<<Poco::ThreadPool::defaultPool().available()<<std::endl;
		Poco::ThreadPool::defaultPool().joinAll();
		std::cout<<"dur: "<<sw.elapsed()/1000<<" ms"<<std::endl;
	}
	return 0;
}
