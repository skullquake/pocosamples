#include<iostream>
#include<Poco/DeflatingStream.h>
#include<Poco/InflatingStream.h>
#include<fstream>
int main(int argc, char** argv){
	{
		std::ofstream ostr("./out/a.gz",std::ios::binary);
		Poco::DeflatingOutputStream deflater(ostr,Poco::DeflatingStreamBuf::STREAM_GZIP);
		for(int i=0;i<4096;i++){
			deflater<<"Lorem ipsum"
			        <<std::to_string(i)
				<<std::endl;
		}
		deflater.close();
		ostr.close();
	}
	{
		std::ifstream istr("./out/a.gz",std::ios::binary);
		Poco::InflatingInputStream inflater(istr,Poco::InflatingStreamBuf::STREAM_GZIP);
		std::string data((std::istreambuf_iterator<char>(inflater)),std::istreambuf_iterator<char>());
		std::cout<<data<<std::endl;
		istr.close();
	}
	return 0;
}
