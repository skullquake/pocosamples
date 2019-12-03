#include<Poco/Base64Encoder.h>
#include<algorithm>
#include<cstddef>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<iterator>
#include<numeric>
#include<sstream>
#include<string.h>
#include<utility>
#include<vector>
template<class T,class CharT=char,class Traits=std::char_traits<CharT>>
class ostreambin_iterator:public std::iterator<std::output_iterator_tag,void,void,void,void>{
	public:
		typedef std::basic_ostream<CharT,Traits> ostream_type;
		typedef Traits traits_type;
		typedef CharT char_type;
		ostreambin_iterator(ostream_type& stream):stream_(stream) { }
		ostreambin_iterator& operator=(T const& value){
			stream_.write(reinterpret_cast<const char*>(&value),sizeof(T));
			return *this;
		}
		ostreambin_iterator& operator*(){return *this;}
		ostreambin_iterator& operator++(){return *this;}
		ostreambin_iterator& operator++(int){return *this;}
	protected:
		ostream_type& stream_;
};
int main(int argc,char *argv[]){
	if(argc==2){
		std::vector<float>v;// v(1);
		for(int i=0;i<2;i++){
			v.push_back(i);
		}
		for(int i=0;i<2;i++){
			v.push_back(i);
		}
		if(strcmp(argv[1],"--raw")==0){
			ostreambin_iterator<float> out(std::cout);
			copy(std::begin(v),std::end(v),out);
			//std::cout<<std::endl;
			return EXIT_SUCCESS;
		}else 
		if(strcmp(argv[1],"--b64")==0){
			Poco::Base64Encoder b64out(
				std::cout,
				Poco::BASE64_NO_PADDING
			);
			ostreambin_iterator<float> out(b64out);
			copy(std::begin(v),std::end(v),out);
			b64out.close();
			//std::cout<<std::endl;
			return EXIT_SUCCESS;

		}else{
			std::cerr<<"Usage: "<<argv[0]<<" --raw|--b64"<<std::endl;
			return EXIT_FAILURE;
		}
	}else{
		std::cerr<<"Usage: "<<argv[0]<<" --raw|--b64"<<std::endl;
		return EXIT_FAILURE;
	}
}


