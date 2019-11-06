#include<iostream>
#include<Poco/DeflatingStream.h>
#include<fstream>
int main(int argc, char** argv){
	std::ofstream ostr("./out/a.gz",std::ios::binary);
	Poco::DeflatingOutputStream deflater(ostr,Poco::DeflatingStreamBuf::STREAM_GZIP);
	deflater<<"Lorem ipsum";
	deflater.close();
	ostr.close();
	return 0;
}
