#include<iostream>
#include<Poco/NotificationCenter.h>
#include<Poco/Notification.h>
#include<Poco/Observer.h>
#include<Poco/NObserver.h>
#include<Poco/AutoPtr.h>
class BaseNotification:public Poco::Notification{
};
class SubNotification:public BaseNotification{
};
class Target{
	public:
		void handleBase(BaseNotification* pNf){
			std::cout<<"handleBase: "<<pNf->name()<<std::endl;
			pNf->release();
		}
		void handleSub(const Poco::AutoPtr<SubNotification>& pNf){
			std::cout<<"handleSub:"<<pNf->name()<<std::endl;
		}
};
int main(int argc, char** argv){
	Poco::NotificationCenter nc;
	Target target;
	nc.addObserver(Poco::Observer<Target,BaseNotification>(target,&Target::handleBase));
	nc.addObserver(Poco::NObserver<Target,SubNotification>(target,&Target::handleSub));
	nc.postNotification(new BaseNotification);
	nc.postNotification(new SubNotification);
	nc.removeObserver(Poco::Observer<Target,BaseNotification>(target,&Target::handleBase));
	nc.removeObserver(Poco::NObserver<Target,SubNotification>(target,&Target::handleSub));
	return 0;
}
