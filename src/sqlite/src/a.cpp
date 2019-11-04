//#include "Poco/Data/Common.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/Session.h"
#include <iostream>
using namespace Poco::Data;
int main(int argc, char* argv[])
{
	SQLite::Connector::registerConnector();
	Session ses("SQLite", "./db/a.db");
	ses.begin();
	ses<<"CREATE TABLE IF NOT EXISTS a(b INTEGER)",Poco::Data::Keywords::now;
	ses.commit();
	Poco::Data::Statement stmt(ses);
	for(int i=0;i<32;i++){
		stmt<<
			"INSERT INTO a(b) VALUES(?)",
			//Poco::Data::Keywords::use(i),
			Poco::Data::Keywords::useRef(i),
			//Poco::Data::Keywords::bind(std::to_string(i)),
			//Poco::Data::Keywords::bind(i),
			Poco::Data::Keywords::now
		;
		std::cout<<stmt.toString()<<std::endl;
		stmt.execute();
	}
	//ses.commit();
	//ses<<R"(END TRANSACTION)"<<Poco::Data::Keywords::now;
	//stmt<<R"(CREATE TABLE IF NOT EXISTS A(VAL TEXT))";//<<Poco::Data::Keywords::now;
	//stmt.execute();
	//stmt.execute();
	//ses.execute();
	SQLite::Connector::unregisterConnector();
}
