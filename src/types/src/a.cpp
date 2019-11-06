//#include "Poco/Data/Common.h"
#include"Poco/Types.h"
#include<iostream>
int main(int argc, char* argv[]){
#ifdef POCO_PTR_IS_64_BIT
	std::cout<<"POCO_PTR_IS_64_BIT"<<std::endl;
#else
	std::cout<<"!POCO_PTR_IS_64_BIT"<<std::endl;
#endif
#ifdef POCO_LONG_IS_64_BIT
	std::cout<<"POCO_LONG_IS_64_BIT"<<std::endl;
#else
	std::cout<<"!POCO_LONG_IS_64_BIT"<<std::endl;
#endif
#ifdef POCO_ARCH_LITTLE_ENDIAN
	std::cout<<"POCO_ARCH_LITTLE_ENDIAN"<<std::endl;
#endif
#ifdef POCO_ARCH_BIG_ENDIAN
	std::cout<<"POCO_ARCH_BIG_ENDIAN"<<std::endl;
#endif
	Poco::Int8    int8;
	Poco::Int16   int16;
	Poco::Int32   int32;
	Poco::Int64   int64;
	Poco::UInt8   uint8;
	Poco::UInt16  uint16;
	Poco::UInt32  uint32;
	Poco::UInt64  uint64;
	Poco::IntPtr  intptr;
	Poco::UIntPtr uintptr;
	return 0;
}
