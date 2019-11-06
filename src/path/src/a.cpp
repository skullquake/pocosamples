#include<iostream>
#include<vector>
#include<Poco/Path.h>
#include<Poco/File.h>
#include<Poco/Timestamp.h>
#include<Poco/DateTime.h>
#include<Poco/DateTimeFormatter.h>
#include<Poco/DateTimeFormat.h>
int main(int argc, char** argv){
	{
		Poco::Path p(true);
		p.setNode("VMS001");
		p.setDevice("DSK001");
		p.pushDirectory("POCO");
		p.pushDirectory("INCLUDE");
		p.pushDirectory("POCO");
		p.setFileName("POCO.h");
		std::cout<<p.toString(Poco::Path::PATH_VMS)<<std::endl;
		p.clear();
	}
	{
		Poco::Path p(true);
		p.setNode("WIN001");
		p.setDevice("C");
		p.pushDirectory("POCO");
		p.pushDirectory("INCLUDE");
		p.pushDirectory("POCO");
		p.setFileName("POCO.h");
		std::cout<<p.toString(Poco::Path::PATH_WINDOWS)<<std::endl;
		p.clear();
	}
	{
		Poco::Path p(true);
		p.pushDirectory("projects");
		p.pushDirectory("poco");
		std::cout<<p.toString(Poco::Path::PATH_WINDOWS)<<std::endl;
		std::cout<<p.toString(Poco::Path::PATH_UNIX)<<std::endl;
		p.clear();
	}
	{
		Poco::Path p0("C:\\Windows\System32\\cmd.exe");
		Poco::Path p1("/bin/sh");
		p0="projects\\poco";
		p1="projects/poco";
		std::cout<<(p0.tryParse("/usr/*/stdio.h"))<<std::endl;
		std::cout<<(p0.tryParse("/usr/include/stdio.h",Poco::Path::PATH_UNIX))<<std::endl;
		std::cout<<(p0.tryParse("/usr/include/stdio.h",Poco::Path::PATH_WINDOWS))<<std::endl;
		std::cout<<(p0.tryParse("/usr/include/stdio.h",Poco::Path::PATH_GUESS))<<std::endl;
	}
	{
		Poco::Path p(true);
		p.setNode("VMS001");
		p.setDevice("DSK001");
		p.pushDirectory("POCO");
		p.pushDirectory("INCLUDE");
		p.pushDirectory("POCO");
		p.setFileName("POCO.h");
		std::cout<<p.toString(Poco::Path::PATH_VMS)<<std::endl;
		std::cout<<"\t"<<p.getNode()<<std::endl;
		std::cout<<"\t"<<p.getDevice()<<std::endl;
		for(int i=0;i<p.depth();i++)std::cout<<"\t"<<p.directory(i)<<std::endl;
		std::cout<<"\t"<<p.getFileName()<<std::endl;
		p.clear();
	}
	{
		Poco::Path p(true);
		p.pushDirectory("tmp");
		p.pushDirectory("test");
		p.setFileName("a.b");
		std::cout<<p.toString(Poco::Path::PATH_UNIX)<<std::endl;
		for(int i=0;i<p.depth();i++)std::cout<<"\t"<<p.directory(i)<<std::endl;
		std::cout<<"\t"<<p.getFileName()<<std::endl;
		std::cout<<"\t"<<p.getBaseName()<<std::endl;
		std::cout<<"\t"<<p.getExtension()<<std::endl;
		p.setBaseName("c");
		p.setExtension("d");
		std::cout<<p.toString(Poco::Path::PATH_UNIX)<<std::endl;
		for(int i=0;i<p.depth();i++)std::cout<<"\t"<<p.directory(i)<<std::endl;
		std::cout<<"\t"<<p.getFileName()<<std::endl;
		std::cout<<"\t"<<p.getBaseName()<<std::endl;
		std::cout<<"\t"<<p.getExtension()<<std::endl;
		p.clear();
	}
	{
		Poco::Path p("/usr/include");
		p=p.parent();
		std::cout<<p.toString(Poco::Path::PATH_UNIX)<<std::endl;
		for(int i=0;i<p.depth();i++)std::cout<<"\t"<<p.directory(i)<<std::endl;
		std::cout<<"\t"<<p.getFileName()<<std::endl;
		std::cout<<"\t"<<p.getBaseName()<<std::endl;
		std::cout<<"\t"<<p.getExtension()<<std::endl;
		p.clear();
	}
	{
		std::vector<Poco::Path> vp={
			Poco::Path::current(),
			Poco::Path::home(),
			Poco::Path::temp(),
			Poco::Path::null()
		};
		for(auto p:vp){
			std::cout<<p.toString(Poco::Path::PATH_UNIX)<<std::endl;
			for(int i=0;i<p.depth();i++)std::cout<<"\t"<<p.directory(i)<<std::endl;
			std::cout<<"\t"<<p.getFileName()<<std::endl;
			std::cout<<"\t"<<p.getBaseName()<<std::endl;
			std::cout<<"\t"<<p.getExtension()<<std::endl;
		}
	}
	{
		Poco::Path p(Poco::Path::expand("$HOME"));
		std::cout<<p.toString(Poco::Path::PATH_UNIX)<<std::endl;
		for(int i=0;i<p.depth();i++)std::cout<<"\t"<<p.directory(i)<<std::endl;
		std::cout<<"\t"<<p.getFileName()<<std::endl;
		std::cout<<"\t"<<p.getBaseName()<<std::endl;
		std::cout<<"\t"<<p.getExtension()<<std::endl;
	}
	{
		std::vector<std::string> vs;
		Poco::Path::listRoots(vs);
		for(auto s:vs){
			std::cout<<s<<std::endl;
		}
	}
	{
		Poco::Path p;
		if(Poco::Path::find("/usr/include","stdio.h",p)){
			std::cout<<"File found"<<std::endl;
			std::cout<<p.toString(Poco::Path::PATH_UNIX)<<std::endl;
			for(int i=0;i<p.depth();i++)std::cout<<"\t"<<p.directory(i)<<std::endl;
			std::cout<<"\t"<<p.getFileName()<<std::endl;
			std::cout<<"\t"<<p.getBaseName()<<std::endl;
			std::cout<<"\t"<<p.getExtension()<<std::endl;

		}else{
			std::cerr<<"File not found"<<std::endl;
		}
	}
	{
		Poco::File f("/tmp/a");
		if(!f.exists()){
			if(f.createFile()){
				std::cout<<"File created"<<std::endl;
				std::cout<<"exists():"<<f.exists()<<std::endl;
				std::cout<<"canRead():"<<f.canRead()<<std::endl;
				std::cout<<"canWrite():"<<f.canWrite()<<std::endl;
				std::cout<<"canExecute():"<<f.canExecute()<<std::endl;
				std::cout<<"isFile():"<<f.isFile()<<std::endl;
				std::cout<<"isDirectory():"<<f.isDirectory()<<std::endl;
				std::cout<<"isDevice():"<<f.isDevice()<<std::endl;
				std::cout<<"isHidden():"<<f.isHidden()<<std::endl;
				std::cout<<"created():"<<Poco::DateTimeFormatter::format(Poco::DateTime(f.created()),Poco::DateTimeFormat::ISO8601_FORMAT)<<std::endl;
				std::cout<<"getLastModified():"<<Poco::DateTimeFormatter::format(Poco::DateTime(f.getLastModified()),Poco::DateTimeFormat::ISO8601_FORMAT)<<std::endl;
				std::cout<<"getSize():"<<f.getSize()<<std::endl;
				f.remove();
				if(!f.exists()){
					std::cout<<"File removed"<<std::endl;
				}else{
					std::cout<<"File not removed"<<std::endl;
				}
			}else{
				std::cout<<"Could not creat file"<<std::endl;
			}
		}else{
			std::cout<<"File already exists"<<std::endl;
		}
	}
	return 0;
}
