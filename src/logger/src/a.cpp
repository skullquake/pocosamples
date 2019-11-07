#include<iostream>
#include<Poco/Logger.h>
int main(int argc, char** argv){
	Poco::Logger& logger=Poco::Logger::get("TestLogger");
	logger.information("Test information");
	logger.warning("Test warning");
	return 0;
}
