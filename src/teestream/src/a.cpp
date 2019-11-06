#include<iostream>
#include<fstream>
#include<Poco/TeeStream.h>
int main(int argc, char** argv){
	Poco::TeeOutputStream tee(std::cout);
	std::ofstream fstr("./out/a.txt");
	tee.addStream(fstr);
	tee<<"Lorem ipsum"<<std::endl;
	return 0;
}
