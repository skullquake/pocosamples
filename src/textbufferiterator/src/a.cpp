#include<iostream>
#include<Poco/TextBufferIterator.h>
#include<Poco/UTF8Encoding.h>
int main(int argc, char** argv){
	Poco::UTF8Encoding u8e;
	char buf[]="0123456789abcdef";
	Poco::TextBufferIterator tbi(buf,u8e);
	Poco::TextBufferIterator end(tbi.end());
	int a=0;
	while(tbi!=end){a++;++tbi;}
	std::cout<<a<<std::endl;
	return 0;
}
