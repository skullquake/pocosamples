#include<iostream>
#include<vector>
#include<Poco/String.h>
int main(int argc, char** argv){
	std::string hello(" Hello, world! ");
	std::cout<<hello<<std::endl;
	std::string s1(Poco::trimLeft(hello));
	std::cout<<s1<<std::endl;
	Poco::trimRightInPlace(s1);
	std::cout<<s1<<std::endl;
	std::string s2(Poco::trim(hello));
	std::cout<<s2<<std::endl;
	std::cout<<Poco::toUpper(hello)<<std::endl;
	std::cout<<Poco::toLower(hello)<<std::endl;
	std::cout<<Poco::toUpperInPlace(hello)<<std::endl;
	std::cout<<Poco::toLowerInPlace(hello)<<std::endl;
	std::cout<<Poco::icompare(Poco::toLower(hello),Poco::toLower(hello))<<std::endl;
	std::cout<<Poco::icompare(Poco::toUpper(hello),Poco::toLower(hello))<<std::endl;
	std::string s="0123456789abcdef";
	std::cout<<s<<std::endl;
	std::cout<<Poco::translate(s,"0123456789abcdef","fedcba9876543210")<<std::endl;
	std::cout<<s<<std::endl;
	Poco::translateInPlace(s,"0123456789abcdef","fedcba9876543210");
	std::cout<<s<<std::endl;
	s="0123456789abcdef";
	std::cout<<Poco::replace(s,"abcdef","ABCDEF")<<std::endl;
	Poco::replaceInPlace(s,"abcdef","ABCDEF");
	std::cout<<s<<std::endl;
	std::vector<std::string> vs={"foo","bar","baz"};
	for(auto vsi:vs){
		std::cout<<vsi<<std::endl;
	}
	std::cout<<Poco::cat(std::string(","),vs.begin(),vs.end())<<std::endl;;
	return 0;
}
