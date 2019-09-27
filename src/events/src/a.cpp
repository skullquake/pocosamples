#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include <iostream>
using Poco::BasicEvent;
using Poco::Delegate;
class Source{
	public:
		BasicEvent<int> theEvent;
		void fireEvent(int n)
		{
			theEvent(this,n);
		}
};
class Target{
	public:
		void onEvent(const void* pSender,int& arg)
		{
			std::cout<<"onEvent: "<<arg<<std::endl;
		}
};
int main(int argc,char** argv){
	Source source;
	Target target;
	source.theEvent += Delegate<Target, int>(
	&target, &Target::onEvent);
	source.fireEvent(42);
	source.theEvent -= Delegate<Target, int>(
	&target, &Target::onEvent);
	return 0;
}
