#include<iostream>
#include<Poco/NumberFormatter.h>
int main(int argc, char** argv){
	std::cout<<Poco::NumberFormatter::format(123)<<std::endl;
	std::cout<<Poco::NumberFormatter::format(123,5)<<std::endl;
	std::cout<<Poco::NumberFormatter::format(-123,5)<<std::endl;
	std::cout<<Poco::NumberFormatter::format(12345,3)<<std::endl;
	std::cout<<Poco::NumberFormatter::format0(123,5)<<std::endl;
	std::cout<<Poco::NumberFormatter::formatHex(123)<<std::endl;
	std::cout<<Poco::NumberFormatter::formatHex(123,4)<<std::endl;
	std::cout<<Poco::NumberFormatter::format(1.5)<<std::endl;
	std::cout<<Poco::NumberFormatter::format(1.5,2)<<std::endl;
	std::cout<<Poco::NumberFormatter::format(1.5,5,2)<<std::endl;
	std::string s=Poco::NumberFormatter::format(1.5,5,2);
	std::cout<<s<<std::endl;
	s=Poco::NumberFormatter::format(&s);
	std::cout<<s<<std::endl;
	return 0;
}
