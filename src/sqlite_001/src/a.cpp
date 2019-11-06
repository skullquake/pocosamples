//#include "Poco/Data/Common.h"
#include"Poco/Data/SQLite/Connector.h"
#include"Poco/Data/Session.h"
#include"Poco/Data/RecordSet.h"
#include"Poco/Data/Row.h"
#include<iostream>
#include<vector>
#include<tuple>
using namespace Poco::Data;
int main(int argc, char* argv[]){
	SQLite::Connector::registerConnector();
	Session ses("SQLite", "./db/a.db");
	//ses.setFeature("emptyStringIsNull",true);
	//ses.setFeature("forceEmptyString",true);
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
	int nvec3f=10;
	int ndataset=10;
	std::cout<<"Populating...";
	for(int datasetidx=0;datasetidx<ndataset;datasetidx++){
		{
			Poco::Data::Statement stmt(ses);
			stmt<<
				R"(
					INSERT INTO
					DataSet	
					(id)
					VALUES(?)
				)",
				Poco::Data::Keywords::bind(datasetidx)
			;
			stmt.execute();
		}
		for(int vec3fidx=0;vec3fidx<nvec3f;vec3fidx++){
			{
				Poco::Data::Statement stmt(ses);
				stmt<<
					R"(
						INSERT INTO
						Vec3f
						(x,y,z,id_DataSet)
						VALUES(?,?,?,?)
					)",
					Poco::Data::Keywords::bind((float)vec3fidx/nvec3f),
					Poco::Data::Keywords::bind((float)vec3fidx/nvec3f),
					Poco::Data::Keywords::bind((float)vec3fidx/nvec3f),
					Poco::Data::Keywords::bind(datasetidx)
				;
				stmt.execute();
			}
		}

	}
	ses.commit();
	std::cout<<"done"<<std::endl;
	//iterate
	{
		Poco::Data::Statement stmt(ses);
		Poco::Nullable<int> dsid;
		Poco::Nullable<float> x;
		Poco::Nullable<float> y;
		Poco::Nullable<float> z;
		stmt<<
			R"(
				SELECT
					dataset.id,
					vec3f.x,
					vec3f.y,
					vec3f.z
				FROM Vec3f AS vec3f
				INNER JOIN DataSet as dataset
				ON Vec3f.id_DataSet=DataSet.id
			)",
			Poco::Data::Keywords::into(dsid),
			Poco::Data::Keywords::into(x),
			Poco::Data::Keywords::into(y),
			Poco::Data::Keywords::into(z),
			Poco::Data::Keywords::range(0,1)
		;
		while(!stmt.done()){
			stmt.execute();
			std::cout<<"["
			         //<<(dsid.isNull()?0:dsid)
			         <<dsid
			         <<"]["
			         <<x
			         <<","
			         <<y
			         <<","
			         <<z
			         <<"]"
			         <<std::endl
			;
		}
	}
	//multiple data sets
	{
		Poco::Data::Statement stmt(ses);
		Poco::Nullable<int> dsid;
		Poco::Nullable<float> x;
		Poco::Nullable<float> y;
		Poco::Nullable<float> z;
		std::vector<std::tuple<int,float,float,float>> a;
		stmt<<
			R"(
				SELECT
					dataset.id,
					vec3f.x,
					vec3f.y,
					vec3f.z
				FROM Vec3f AS vec3f
				INNER JOIN DataSet as dataset
				ON Vec3f.id_DataSet=DataSet.id
			)"//,
			//Poco::Data::Keywords::range(0,1)
		;
		stmt.execute();
		Poco::Data::RecordSet rs(stmt);
		for(auto rsit=rs.begin();rsit!=rs.end();++rsit){
			Poco::Data::Row& r=*rsit;
			std::cout<<r.valuesToString();//<<std::endl;
		}
	}

	SQLite::Connector::unregisterConnector();
}
