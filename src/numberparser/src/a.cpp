#include<iostream>
#include<Poco/NumberParser.h>
int main(int argc, char** argv){
	std::string s("123");
	int i=Poco::NumberParser::parse(s);
	std::cout<<s<<std::endl;
	std::cout<<i<<std::endl;
	if(Poco::NumberParser::tryParse(s,i)){
		std::cout<<"Parsed "+s<<std::endl;
	}else{
		std::cout<<"Failed to parse "+s<<std::endl;
	}
	s="qwer";
	if(Poco::NumberParser::tryParse(s,i)){
		std::cout<<"Parsed "+s<<std::endl;
	}else{
		std::cout<<"Failed to parse "+s<<std::endl;
	}
	s="123";
	int f;
	unsigned int j;
	long k;
	long unsigned int l;
	double d;
	Poco::NumberParser::parseUnsigned(s);
	Poco::NumberParser::parseHex(s);
	Poco::NumberParser::parse64(s);
	Poco::NumberParser::parseUnsigned64(s);
	Poco::NumberParser::parseHex64(s);
	Poco::NumberParser::parseFloat(s);
	std::cout<<(Poco::NumberParser::tryParseUnsigned(s,j)?"Parsed":"Not parsed")<<std::endl;
	std::cout<<(Poco::NumberParser::tryParseHex(s,j)?"Parsed":"Not parsed")<<std::endl;
	std::cout<<(Poco::NumberParser::tryParse64(s,k)?"Parsed":"Not parsed")<<std::endl;
	std::cout<<(Poco::NumberParser::tryParseUnsigned64(s,l)?"Parsed":"Not parsed")<<std::endl;
	std::cout<<(Poco::NumberParser::tryParseHex64(s,l)?"Parsed":"Not parsed")<<std::endl;
	std::cout<<(Poco::NumberParser::tryParseFloat(s,d)?"Parsed":"Not parsed")<<std::endl;

	return 0;
}
