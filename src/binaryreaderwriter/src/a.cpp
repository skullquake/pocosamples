#include<iostream>
#include<fstream>
#include<Poco/BinaryWriter.h>
#include<Poco/BinaryReader.h>
int main(int argc, char** argv){
	{
		std::ofstream ostr("./out/a.dat",std::ios::binary);
		Poco::BinaryWriter writer(ostr);
		writer.writeBOM();
		writer<<"Lorem"<<42;
		//writer.write7BitEncoded(123);
		writer<<true;
		ostr.close();
	}
	{
		std::ifstream istr("./out/a.dat",std::ios::binary);
		Poco::BinaryReader reader(istr);
		reader.readBOM();
		std::string s;
		int i;
		bool b;
		reader>>s;
		reader>>i;
		reader>>b;
		std::cout<<s<<std::endl;
		std::cout<<i<<std::endl;
		std::cout<<b<<std::endl;
		istr.close();
	}
	return 0;
}
