#include<iostream>
#include<Poco/Base64Encoder.h>
int main(int argc, char** argv){
	Poco::Base64Encoder encoder(std::cout);
	encoder<<"Lorem ipsum";
	return 0;
}
