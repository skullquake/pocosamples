//#include "Poco/Data/Common.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/Session.h"
#include <iostream>
using namespace Poco::Data;
struct Foo{
	std::string Bar;
	std::string Baz;
	std::string Qux;
};
int main(int argc, char* argv[]){
	SQLite::Connector::registerConnector();
	Session ses("SQLite", "./db/a.db");
	ses<<R"(DROP TABLE IF EXISTS A)",Poco::Data::Keywords::now;
	ses<<R"(CREATE TABLE IF NOT EXISTS Foo(Bar VARCHAR(30),Baz VARCHAR(30),Qux VARCHAR(30)))",Poco::Data::Keywords::now;
	Foo f={
		"Bar",
		"Baz",
		"Qux"
	};
	{
		Poco::Data::Statement stmt(ses);
		stmt<<
			R"(INSERT INTO Foo VALUES(?,?,?))",
			Poco::Data::Keywords::use(f.Bar),
			Poco::Data::Keywords::use(f.Baz),
			Poco::Data::Keywords::use(f.Qux)
		;
		stmt.execute();
	}
	{
		Poco::Data::Statement stmt(ses);
		stmt<<
			R"(SELECT Bar,Baz,QUX FROM Foo)",
			Poco::Data::Keywords::into(f.Bar),
			Poco::Data::Keywords::into(f.Baz),
			Poco::Data::Keywords::into(f.Qux),
			Poco::Data::Keywords::range(0,1)
		;
		while(!stmt.done()){
			stmt.execute();
			std::cout<<f.Bar<<" "<<f.Baz<<" "<<f.Qux<<std::endl;
		}
	}
	SQLite::Connector::unregisterConnector();
}
