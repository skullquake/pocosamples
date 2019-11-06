#include<iostream>
#include<vector>
#include<Poco/Foundation.h>
#include<Poco/Environment.h>
#include<Poco/Exception.h>
int main(int argc, char** argv){
#if POCO_OS == POCO_OS_WINDOWS_NT
	std::cout<<"POCO_OS_WINDOWS_NT"<<std::endl;
#elif POCO_OS == POCO_OS_LINUX
	std::cout<<"POCO_OS_LINUX"<<std::endl;
#endif
#if POCO_OS_FAMILY == POCO_OS_FAMILY_WINDOWS
	std::cout<<"POCO_OS_FAMILY_WINDOWS"<<std::endl;
#elif POCO_OS_FAMILY == POCO_OS_FAMILY_LINUX
	std::cout<<"POCO_OS_FAMILY_LINUX"<<std::endl;
#endif
#if POCO_ARCH == POCO_ARCH_ALPHA
	std::cout<<"POCO_ARCH_ALPHA"<<std::endl;
#elif POCO_ARCH == POCO_ARCH_ARM
	std::cout<<"POCO_ARCH_ARM"<<std::endl;
#elif POCO_ARCH == POCO_ARCH_AMD64
	std::cout<<"POCO_ARCH_AMD64"<<std::endl;
#elif POCO_ARCH == POCO_ARCH_HPPA
	std::cout<<"POCO_ARCH_HPPA"<<std::endl;
#elif POCO_ARCH == POCO_ARCH_IA32
	std::cout<<"POCO_ARCH_IA32"<<std::endl;
#endif
#ifdef POCO_ARCH_LITTLE_ENDIAN
	std::cout<<"POCO_ARCH_LITTLE_ENDIAN"<<std::endl;
#endif
#ifdef POCO_ARCH_BIG_ENDIAN
	std::cout<<"POCO_ARCH_BIG_ENDIAN"<<std::endl;
#endif
	std::vector<std::string> vs={
		"PATH",
		"TERM",
		"PYTHON_HOME"
	};
	for(auto vsi:vs){
		try{
			std::cout<<vsi<<": "<<(Poco::Environment::has(vsi)?Poco::Environment::get(vsi):"Not set")<<std::endl;
		}catch(Poco::NotFoundException& e){
			std::cerr<<e.displayText()<<std::endl;
		}
	}
	if(!Poco::Environment::has("POCO")){
		Poco::Environment::set("POCO","foo");
	}
	std::cout<<Poco::Environment::osName()<<std::endl;
	std::cout<<Poco::Environment::osVersion()<<std::endl;
	std::cout<<Poco::Environment::osArchitecture()<<std::endl;
	std::cout<<Poco::Environment::nodeName()<<std::endl;
	std::cout<<Poco::Environment::nodeId()<<std::endl;
	return 0;
}
