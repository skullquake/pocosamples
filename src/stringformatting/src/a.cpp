#include<iostream>
#include<Poco/Format.h>
int main(int argc, char** argv){
	std::cout<<Poco::format("_%d_",1)<<std::endl;
	std::cout<<Poco::format("_%d_%d_",1,2)<<std::endl;
	std::cout<<Poco::format("_%4d_%4d_",1,2)<<std::endl;
	std::cout<<Poco::format("_%-4d_%-4d_",1,2)<<std::endl;
	std::cout<<Poco::format("_%f_",1.1)<<std::endl;
	std::cout<<Poco::format("_%f_%f_",1.1,2.2)<<std::endl;
	std::cout<<Poco::format("_%4f_%4f_",1.1,2.2)<<std::endl;
	std::cout<<Poco::format("_%-4f_%-4f_",1.1,2.2)<<std::endl;
	std::cout<<Poco::format("_%s_%s_",std::string("a"),std::string("a"))<<std::endl;
	std::cout<<Poco::format("_%4s_%4s_",std::string("a"),std::string("a"))<<std::endl;
	std::cout<<Poco::format("_%-4s_%-4s_",std::string("a"),std::string("a"))<<std::endl;
	return 0;
}
