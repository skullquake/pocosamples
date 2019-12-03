#include<iostream>
#include<fstream>
#include<cstdlib>
#include<Poco/Base64Encoder.h>
int main(int argc,char *argv[]){
	if(argc==3){
		std::ifstream ifs(argv[1]);
		std::ofstream ofs(argv[2]);
		Poco::Base64Encoder b64out(
			ofs,
			Poco::BASE64_URL_ENCODING||
			Poco::BASE64_NO_PADDING
		);
		std::copy(
			std::istreambuf_iterator<char>(ifs),
			std::istreambuf_iterator<char>(),
			std::ostreambuf_iterator<char>(b64out));
		b64out.close();
		return EXIT_SUCCESS;
	}else{
		std::cerr<<"Usage: "<<argv[0]<<" INPUTFILE OUTPUTFILE"<<std::endl;
		return EXIT_FAILURE;
	}
} 
