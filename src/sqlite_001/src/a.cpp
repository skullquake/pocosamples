//#include "Poco/Data/Common.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/Session.h"
#include <iostream>
using namespace Poco::Data;
int main(int argc, char* argv[]){
	SQLite::Connector::registerConnector();
	Session ses("SQLite", "./db/a.db");
	std::cout<<"Dropping table...";
	ses<<
		R"(DROP TABLE IF EXISTS Vec3f)",
		Poco::Data::Keywords::now
	;
	ses<<
		R"(DROP TABLE IF EXISTS DataSet)",
		Poco::Data::Keywords::now
	;
	std::cout<<"done"<<std::endl;
	std::cout<<"Creating table...";
	ses<<
		R"(
		CREATE TABLE IF NOT EXISTS DataSet
		(
			id INTEGER NOT NULL PRIMARY KEY
		)
		)",
		Poco::Data::Keywords::now
	;
	ses<<
		R"(
		CREATE TABLE IF NOT EXISTS Vec3f
		(
			x REAL,
			y REAL,
			z REAL,
			id_DataSet INTEGER,
			FOREIGN KEY(id_DataSet) REFERENCES DataSet(id)
		)
		)",
		Poco::Data::Keywords::now
	;
	std::cout<<"done"<<std::endl;
	ses.begin();
	{
		Poco::Data::Statement stmt(ses);
		stmt<<
			R"(
				INSERT INTO
				DataSet	
				(id)
				VALUES(?)
			)",
			Poco::Data::Keywords::bind(0)
		;
		stmt.execute();
	}

	int nelem=8;
	for(int i=0;i<nelem;i++){
		std::cout<<"Creating row...";
		{
			Poco::Data::Statement stmt(ses);
			stmt<<
				R"(
					INSERT INTO
					Vec3f
					(x,y,z,id_DataSet)
					VALUES(?,?,?,?)
				)",
				Poco::Data::Keywords::bind((float)i/nelem),
				Poco::Data::Keywords::bind((float)i/nelem),
				Poco::Data::Keywords::bind((float)i/nelem),
				Poco::Data::Keywords::bind(0)
			;
			stmt.execute();
		}
		/*
		ses<<
			R"(INSERT INTO Vec3f VALUES(?,?,?))",
			Poco::Data::Keywords::bind(i),
			Poco::Data::Keywords::bind(i),
			Poco::Data::Keywords::bind(i),
			Poco::Data::Keywords::now
		;
		*/

		std::cout<<"done"<<std::endl;

	}
	ses.commit();
	{
		Poco::Data::Statement stmt(ses);
		float x;
		float y;
		float z;
		stmt<<
			R"(SELECT x,y,z FROM Vec3f)",
			Poco::Data::Keywords::into(x),
			Poco::Data::Keywords::into(y),
			Poco::Data::Keywords::into(z),
			Poco::Data::Keywords::range(0,1)
		;
		while(!stmt.done()){
			stmt.execute();
			std::cout<<"["<<x<<","<<y<<","<<z<<"]"<<std::endl;
		}
	}
	SQLite::Connector::unregisterConnector();
}
