#include"Poco/Exception.h"
#include<iostream>
int main(int argc, char* argv[]){
	try{
		throw Poco::ApplicationException("test");
	}catch(Poco::ApplicationException& e){
		std::cerr<<e.displayText()<<std::endl;
	}
	return 0;
}
