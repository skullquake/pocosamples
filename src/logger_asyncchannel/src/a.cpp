#include<iostream>
#include<Poco/Logger.h>
#include<Poco/AsyncChannel.h>
#include<Poco/FileChannel.h>
#include<Poco/AutoPtr.h>
int main(int argc, char** argv){
	Poco::AutoPtr<Poco::FileChannel> pChannel(new Poco::FileChannel);
	pChannel->setProperty("path","./log/sample.log");
	pChannel->setProperty("rotation","2 K");
	pChannel->setProperty("archive","timestamp");
	Poco::AutoPtr<Poco::AsyncChannel> pAsync(new Poco::AsyncChannel(pChannel));
	Poco::Logger::root().setChannel(pAsync);
	Poco::Logger& logger=Poco::Logger::get("TestLogger");
	for(int i=0;i<1024*32;i++){
		logger.information("Test information");
		logger.warning("Test warning");
	}	
	return 0;
}
