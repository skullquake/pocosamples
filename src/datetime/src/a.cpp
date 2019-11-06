#include<iostream>
#include<ctime>
#include<Poco/Timestamp.h>
#include<Poco/DateTime.h>
#include<Poco/LocalDateTime.h>
#include<Poco/Timespan.h>
#include<Poco/DateTimeFormatter.h>
#include<Poco/DateTimeFormat.h>
#include<Poco/DateTimeParser.h>
int main(int argc, char** argv){
	{
		Poco::Timestamp ts0;
		std::time_t tt0=ts0.epochTime();
		Poco::Timestamp ts1(Poco::Timestamp::fromEpochTime(tt0));
		for(int i=0;i<100000;++i);
		Poco::Timestamp::TimeDiff td=ts0.elapsed();
		std::cout<<td<<std::endl;
		Poco::Timestamp ts2(ts0);
		ts0.update();
		td=ts0-ts2;
		std::cout<<td<<std::endl;
	}
	{
		Poco::DateTime dt0;
		int yr=dt0.year();
		int mon=dt0.month();
		int day=dt0.day();
		int dow=dt0.dayOfWeek();
		int doy=dt0.dayOfYear();
		int hr=dt0.hour();
		int hr12=dt0.hourAMPM();
		int min=dt0.minute();
		int sec=dt0.second();
		int ms=dt0.millisecond();
		int us=dt0.microsecond();
		double jd=dt0.julianDay();
		std::cout<<"["
		         <<yr<<","
		         <<mon<<","
		         <<day<<","
		         <<dow<<","
		         <<doy<<","
		         <<hr<<","
		         <<hr12<<","
		         <<min<<","
		         <<sec<<","
		         <<ms<<","
		         <<us<<","
		         <<jd
		         <<"]"
		         <<std::endl;
		Poco::Timestamp ts0=dt0.timestamp();
		Poco::DateTime dt1(1990,1,1);
		Poco::Timespan ts1=dt1-dt0;
		std::cout<<dt1.isAM()<<std::endl;
		std::cout<<dt1.isPM()<<std::endl;
		std::cout<<Poco::DateTime::isLeapYear(1990)<<std::endl;
		std::cout<<Poco::DateTime::daysOfMonth(1990,1)<<std::endl;
		std::cout<<Poco::DateTime::isValid(1990,1,1)<<std::endl;
		dt1.assign(1992,2,2);
		dt1.assign(1992,Poco::DateTime::FEBRUARY,2);
		switch(dt0.dayOfWeek()){
			case Poco::DateTime::MONDAY:std::cout<<"Poco::DateTime::MONDAY"<<std::endl;break;
			case Poco::DateTime::TUESDAY:std::cout<<"Poco::DateTime::TUESDAY"<<std::endl;break;
			case Poco::DateTime::WEDNESDAY:std::cout<<"Poco::DateTime::WEDNESDAY"<<std::endl;break;
			case Poco::DateTime::THURSDAY:std::cout<<"Poco::DateTime::THURSDAY"<<std::endl;break;
			case Poco::DateTime::FRIDAY:std::cout<<"Poco::DateTime::FRIDAY"<<std::endl;break;
			case Poco::DateTime::SATURDAY:std::cout<<"Poco::DateTime::SATURDAY"<<std::endl;break;
			case Poco::DateTime::SUNDAY:std::cout<<"Poco::DateTime::SUNDAY"<<std::endl;break;
			default:
				break;
		}
	}
	{
		Poco::LocalDateTime dt0;
		int yr=dt0.year();
		int mon=dt0.month();
		int day=dt0.day();
		int dow=dt0.dayOfWeek();
		int doy=dt0.dayOfYear();
		int hr=dt0.hour();
		int hr12=dt0.hourAMPM();
		int min=dt0.minute();
		int sec=dt0.second();
		int ms=dt0.millisecond();
		int us=dt0.microsecond();
		double jd=dt0.julianDay();
		std::cout<<"["
		         <<yr<<","
		         <<mon<<","
		         <<day<<","
		         <<dow<<","
		         <<doy<<","
		         <<hr<<","
		         <<hr12<<","
		         <<min<<","
		         <<sec<<","
		         <<ms<<","
		         <<us<<","
		         <<jd
		         <<"]"
		         <<std::endl;
	}
	{
		Poco::Timespan ts0(0,0,0,0,0);
		Poco::Timespan ts1(30*Poco::Timespan::MILLISECONDS);
		Poco::Timespan ts2(30*Poco::Timespan::SECONDS);
		Poco::Timespan ts3(30*Poco::Timespan::MINUTES);
		int days=ts3.days();
		int hours=ts3.hours();
		int totalHours=ts3.totalHours();
		int minutes=ts3.minutes();
		int totalMinutes=ts3.totalMinutes();
		int seconds=ts3.seconds();
		int totalSeconds=ts3.totalSeconds();
		std::cout<<"["
		         <<days<<","
		         <<hours<<","
		         <<totalHours<<","
		         <<minutes<<","
		         <<totalMinutes<<","
		         <<seconds<<","
		         <<totalSeconds
		         <<"]"
		         <<std::endl;
		Poco::LocalDateTime ldt0;
		Poco::LocalDateTime ldt1=ldt0+Poco::Timespan(10*Poco::Timespan::DAYS);
		std::cout<<Poco::DateTimeFormatter::format(ldt0,"%e %b %Y %H:%M")<<std::endl;
	}
	{
		Poco::DateTime dt0(1990,1,1);
		Poco::DateTime dt1(2000,2,2);
		std::cout<<Poco::DateTimeFormatter::format(dt0,"%e %b %Y %H:%M")<<std::endl;
		std::cout<<Poco::DateTimeFormatter::format(dt1,"%e %b %Y %H:%M")<<std::endl;
		std::cout<<Poco::DateTimeFormatter::format(dt0,Poco::DateTimeFormat::ISO8601_FORMAT)<<std::endl;
		std::cout<<Poco::DateTimeFormatter::format(dt1,Poco::DateTimeFormat::ISO8601_FORMAT)<<std::endl;
		std::cout<<Poco::DateTimeFormatter::format(dt0,Poco::DateTimeFormat::RFC1123_FORMAT)<<std::endl;
		std::cout<<Poco::DateTimeFormatter::format(dt1,Poco::DateTimeFormat::RFC1123_FORMAT)<<std::endl;
		std::cout<<Poco::DateTimeFormatter::format(dt0,Poco::DateTimeFormat::SORTABLE_FORMAT)<<std::endl;
		std::cout<<Poco::DateTimeFormatter::format(dt1,Poco::DateTimeFormat::SORTABLE_FORMAT)<<std::endl;
	}
	{
		std::string sd("Sat, 1 Jan 1990 00:00:00 GMT");
		Poco::DateTime dt;
		int tzd;
		if(Poco::DateTimeParser::tryParse(sd,dt,tzd)){
			Poco::DateTimeParser::parse(Poco::DateTimeFormat::RFC1123_FORMAT,sd,dt,tzd);
			Poco::Timestamp ts=dt.timestamp();
			Poco::LocalDateTime ldt(tzd,dt);
			std::cout<<Poco::DateTimeFormatter::format(dt,"%e %b %Y %H:%M")<<std::endl;
			std::cout<<Poco::DateTimeFormatter::format(ldt,"%e %b %Y %H:%M")<<std::endl;
		}else{
			std::cerr<<"Failed to parse date"<<std::endl;
		}
		sd=("ABC, D EFG 1990 00:00:00 GMT");
		if(Poco::DateTimeParser::tryParse(sd,dt,tzd)){
			std::cout<<"Date parsed"<<std::endl;
		}else{
			std::cerr<<"Failed to parse date"<<std::endl;
		}

	}

	return 0;
}
