#include<iostream>
#include<Poco/RegularExpression.h>
int main(int argc, char** argv){
	Poco::RegularExpression re0("[0-9]+");
	std::cout<<(re0.match("123")?"Matched":"Not matched")<<std::endl;
	std::cout<<(re0.match("abc")?"Matched":"Not matched")<<std::endl;
	std::cout<<(re0.match("abc123",3)?"Matched":"Not matched")<<std::endl;
	std::cout<<(re0.match("abc123",0)?"Matched":"Not matched")<<std::endl;
	Poco::RegularExpression::Match m;
	re0.match("123",0,m);
	std::cout<<((m.offset==std::string::npos)?"No Found":"Found ["+std::to_string(m.offset)+"]")<<std::endl;
	re0.match("abc123",0,m);
	std::cout<<((m.offset==std::string::npos)?"No Found":"Found ["+std::to_string(m.offset)+"]")<<std::endl;
	re0.match("abc",0,m);
	std::cout<<((m.offset==std::string::npos)?"No Found":"Found ["+std::to_string(m.offset)+"]")<<std::endl;
	Poco::RegularExpression re1("([0-9]+) ([0-9]+)");
	Poco::RegularExpression::MatchVec mv;
	std::string s("123 321");
	re1.match(s,0,mv);
	std::cout<<mv.size()<<" matches"<<std::endl;
	for(auto mvi:mv){
		std::cout<<"["<<mvi.offset<<","<<mvi.length<<"]"<<s.substr(mvi.offset,mvi.length)<<std::endl;
	}
	Poco::RegularExpression("[0-9]+").extract("123",s);
	std::cout<<s<<std::endl;
	Poco::RegularExpression("[0-9]+").extract("abc",s);
	std::cout<<s<<std::endl;
	Poco::RegularExpression("[0-9]+").extract("abc123abc",s);
	std::cout<<s<<std::endl;
	std::vector<std::string> vs;
	Poco::RegularExpression("([0-9]+) ([0-9]+)").split("123 321",vs);
	std::cout<<vs.size()<<std::endl;
	for(auto vsi:vs){
		std::cout<<vsi<<std::endl;
	}
	return 0;
}
