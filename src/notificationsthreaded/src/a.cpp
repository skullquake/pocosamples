#include<iostream>
#include<thread>
#include<chrono>
#include<Poco/Notification.h>
#include<Poco/NotificationQueue.h>
#include<Poco/ThreadPool.h>
#include<Poco/Runnable.h>
#include<Poco/AutoPtr.h>
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
					std::cout<<"working["<<pWorkNf->data()<<"]"<<std::endl;
					//Poco::Thread::sleep(10);
					//std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				pNf=_queue.waitDequeueNotification();
			}
		}
	private:
		Poco::NotificationQueue& _queue;
};
int main(int argc, char** argv){
	Poco::NotificationQueue queue;
	Worker worker1(queue);
	Worker worker2(queue);
	Poco::ThreadPool::defaultPool().start(worker1);
	Poco::ThreadPool::defaultPool().start(worker2);
	for(int i=0;i<100;++i){
		queue.enqueueNotification(new WorkNotification(i));
	}
	while(!queue.empty())
		Poco::Thread::sleep(100);
	queue.wakeUpAll();
	Poco::ThreadPool::defaultPool().joinAll();
	return 0;
}
