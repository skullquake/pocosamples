#include<iostream>
#include<Poco/StringTokenizer.h>
#include<Poco/String.h>
int main(int argc, char** argv){
	Poco::StringTokenizer t0("a,b,c,d",",");
	std::cout<<Poco::cat(std::string("|"),t0.begin(),t0.end())<<std::endl;
	Poco::StringTokenizer t1("a|b|c|d","|");
	std::cout<<Poco::cat(std::string(","),t1.begin(),t1.end())<<std::endl;
	Poco::StringTokenizer t2(" a , b , c , d",",");
	std::cout<<Poco::cat(std::string("|"),t2.begin(),t2.end())<<std::endl;
	Poco::StringTokenizer t3(" a | b | c | d ","|");
	std::cout<<Poco::cat(std::string(","),t3.begin(),t3.end())<<std::endl;
	Poco::StringTokenizer t4(" a , b , c , d",",",Poco::StringTokenizer::TOK_TRIM);
	std::cout<<Poco::cat(std::string("|"),t4.begin(),t4.end())<<std::endl;
	Poco::StringTokenizer t5(" a | b | c | d ","|",Poco::StringTokenizer::TOK_TRIM);
	std::cout<<Poco::cat(std::string(","),t5.begin(),t5.end())<<std::endl;
	Poco::StringTokenizer t6("a,,c,d",",",Poco::StringTokenizer::TOK_IGNORE_EMPTY);
	std::cout<<Poco::cat(std::string("|"),t6.begin(),t6.end())<<std::endl;
	return 0;
}
