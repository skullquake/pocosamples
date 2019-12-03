#include<iostream>
#include<Poco/Util/Units.h>
int main(int argc, char** argv){
	for(int i=0;i<8;i++){
		std::cout<<Poco::Util::Units::Values::km(Poco::Util::Units::Values::mile(i))<<std::endl;
	}
	for(int i=0;i<8;i++){
		std::cout<<Poco::Util::Units::Values::mile(Poco::Util::Units::Values::km(i))<<std::endl;
	}
	for(int i=0;i<8;i++){
		std::cout<<Poco::Util::Units::Values::hour(Poco::Util::Units::Values::day(i))<<std::endl;
	}
	for(int i=0;i<8;i++){
		std::cout<<Poco::Util::Units::Values::day(Poco::Util::Units::Values::hour(i))<<std::endl;
	}
	return 0;
}
