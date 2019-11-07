#include<iostream>
#include<Poco/Logger.h>
#include<Poco/ConsoleChannel.h>
#include<Poco/AutoPtr.h>
int main(int argc, char** argv){
	Poco::AutoPtr<Poco::ConsoleChannel> pChannel(new Poco::ConsoleChannel);
	Poco::Logger::root().setChannel(pChannel);
	Poco::Logger& logger=Poco::Logger::get("TestLogger");
	logger.information("Test information");
	logger.warning("Test warning");
	return 0;
}
