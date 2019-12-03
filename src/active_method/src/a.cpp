#include<Poco/ActiveMethod.h>
#include<Poco/ActiveResult.h>
#include<Poco/Random.h>
#include<Poco/Stopwatch.h>
#include<iostream>
#include<vector>
using Poco::ActiveMethod;
using Poco::ActiveResult;
class ActiveMethodExample{
	public:
		struct AddArgs
		{
			int a;
			int b;
		};
		
		ActiveMethodExample():
			activeAdd(this, &ActiveMethodExample::activeAddImp)
		{
		}
		Poco::ActiveMethod<int, AddArgs, ActiveMethodExample> activeAdd;
	private:
		int activeAddImp(const AddArgs& args)
		{
			//std::cout<<"activeAddImp():start["<<Poco::Thread::currentTid()<<"]"<<std::endl;
			Poco::Random rnd;
			rnd.seed();
			Poco::Thread::sleep(rnd.next(100));
			//std::cout<<"activeAddImp():end["<<Poco::Thread::currentTid()<<"]"<<std::endl;
			return args.a + args.b;
		}
	};


int main(int argc, char** argv){
	int nelem=16;
	{
		Poco::Stopwatch sw;
		sw.start();
		std::vector<Poco::ActiveResult<int>> var;
		std::vector<int> vr;
		for(int i=0;i<nelem;i++){
			ActiveMethodExample example;
			ActiveMethodExample::AddArgs args={i,i};
			Poco::ActiveResult<int> r=example.activeAdd(args);
			r.wait();
			vr.push_back(r.data());

		}
		for(auto r:vr){
			//std::cout<<r<<std::endl;
		}
		std::cout << "Callback called after " << sw.elapsed()/1000 << " milliseconds." << std::endl;

	}
	{
		Poco::Stopwatch sw;
		sw.start();
		std::vector<Poco::ActiveResult<int>> var;
		std::vector<int> vr;
		for(int i=0;i<nelem;i++){
			ActiveMethodExample example;
			ActiveMethodExample::AddArgs args={i,i};
			var.push_back(example.activeAdd(args));

		}
		for(auto ar:var){
			ar.wait();
			vr.push_back(ar.data());
		}
		for(auto r:vr){
			//std::cout<<r<<std::endl;
		}
		std::cout << "Callback called after " << sw.elapsed()/1000 << " milliseconds." << std::endl;
	}

	return 0;
}
