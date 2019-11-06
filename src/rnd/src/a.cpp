#include<iostream>
#include<Poco/Random.h>
#include<Poco/RandomStream.h>
int main(int argc, char** argv){
	Poco::Random rnd;
	rnd.seed();
	std::cout<<rnd.next()<<std::endl;
	std::cout<<rnd.next(10)<<std::endl;
	std::cout<<rnd.nextChar()<<std::endl;
	std::cout<<rnd.nextBool()<<std::endl;
	std::cout<<rnd.nextDouble()<<std::endl;
	Poco::RandomInputStream ris;
	std::string s;
	ris>>s;
	std::cout<<s<<std::endl;
	return 0;
}
