//#include "Poco/Data/Common.h"
#include"Poco/Any.h"
#include"Poco/Exception.h"
#include<iostream>
int main(int argc, char* argv[]){
	Poco::Any a(42);
	int b=Poco::AnyCast<int>(a);
	int& c=Poco::RefAnyCast<int>(a);
	try{
		short d=Poco::AnyCast<short>(a);
	}catch(Poco::BadCastException&){
		std::cout<<"Poco::BadCastException"<<std::endl;
	}
	return 0;
}
