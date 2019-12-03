#include<iostream>
#include<Poco/SplitterChannel.h>
#include<Poco/Logger.h>
#include<Poco/FileChannel.h>
#include<Poco/ConsoleChannel.h>
#include<Poco/AutoPtr.h>
int main(int argc, char** argv){
	Poco::AutoPtr<Poco::FileChannel> pFileChannel(new Poco::FileChannel);
	pFileChannel->setProperty("path","./log/sample.log");
	pFileChannel->setProperty("rotation","2 K");
	pFileChannel->setProperty("archive","timestamp");
	Poco::AutoPtr<Poco::ConsoleChannel> pConsoleChannel(new Poco::ConsoleChannel);
	Poco::AutoPtr<Poco::SplitterChannel> pSplitterChannel(new Poco::SplitterChannel);
	pSplitterChannel->addChannel(pConsoleChannel);
	pSplitterChannel->addChannel(pFileChannel);
	Poco::Logger::root().setChannel(pSplitterChannel);
	for(int i=0;i<1024;i++){
		Poco::Logger::root().information("Test information");
		Poco::Logger::root().warning("Test warning");
	}	
	return 0;
}
