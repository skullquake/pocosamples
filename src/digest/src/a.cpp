#include<iostream>
#include<Poco/HMACEngine.h>
#include<Poco/SHA1Engine.h>
//#include<Poco/MD2Engine.h>
#include<Poco/MD4Engine.h>
#include<Poco/MD5Engine.h>
#include<Poco/DigestEngine.h>
#include<Poco/DigestStream.h>
int main(int argc, char** argv){
	std::string smsg1("Lorem ipsum");
	std::string smsg2("Sit consecutar");
	std::string spas("s3cr3t");
	{
		Poco::HMACEngine<Poco::SHA1Engine> hmac(spas);
		hmac.update(smsg1);
		hmac.update(smsg2);
		const Poco::DigestEngine::Digest& d=hmac.digest();
		std::string sds(Poco::DigestEngine::digestToHex(d));
		std::cout<<sds<<std::endl;
	}
	/*
	{
		Poco::HMACEngine<Poco::MD2Engine> hmac(spas);
		hmac.update(smsg1);
		hmac.update(smsg2);
		const Poco::DigestEngine::Digest& d=hmac.digest();
		std::string sds(Poco::DigestEngine::digestToHex(d));
		std::cout<<sds<<std::endl;
	}
	*/
	{
		Poco::HMACEngine<Poco::MD4Engine> hmac(spas);
		hmac.update(smsg1);
		hmac.update(smsg2);
		const Poco::DigestEngine::Digest& d=hmac.digest();
		std::string sds(Poco::DigestEngine::digestToHex(d));
		std::cout<<sds<<std::endl;
	}
	{
		Poco::HMACEngine<Poco::MD5Engine> hmac(spas);
		hmac.update(smsg1);
		hmac.update(smsg2);
		const Poco::DigestEngine::Digest& d=hmac.digest();
		std::string sds(Poco::DigestEngine::digestToHex(d));
		std::cout<<sds<<std::endl;
	}
	{
		Poco::MD5Engine md5e;
		Poco::DigestOutputStream dos(md5e);
		dos<<"Lorem ipsum";
		dos.flush();
		const Poco::DigestEngine::Digest& d=md5e.digest();
		std::string r=Poco::DigestEngine::digestToHex(d);
		std::cout<<r<<std::endl;
	}
	return 0;
}
