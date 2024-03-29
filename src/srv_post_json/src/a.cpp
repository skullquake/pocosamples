#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Stringifier.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Array.h"
#include <iostream>

using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;

class TimeRequestHandler:public HTTPRequestHandler{
	public:
		TimeRequestHandler(const std::string& format)
			:_format(format)
		{
		}
		void handleRequest(HTTPServerRequest& request,HTTPServerResponse& response){
			if(request.getMethod().compare("POST")==0){
				Application& app=Application::instance();
				app.logger().information("Request from "+request.clientAddress().toString());
				Timestamp now;
				response.setChunkedTransferEncoding(true);

				std::istream& is=request.stream();
				std::istreambuf_iterator<char> eos;
				std::string s(std::istreambuf_iterator<char>(is),eos);
				std::cout<<s<<std::endl;

				response.setContentType("application/json");
				Poco::JSON::Object objret;
				try{
					std::string json = s;//"{ \"name\" : \"Franky\", \"children\" : [ \"Jonas\", \"Ellen\" ]}";
					Poco::JSON::Parser parser;
					Poco::Dynamic::Var result = parser.parse(json);
					Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();
					if(object->has("name")){
						std::cout<<object->get("name").convert<std::string>()<<std::endl;
						objret.set("msg", "done");
					}else{
						std::cerr<<"no name specified"<<std::endl;
						objret.set("error", "no name specified");
					}
				}catch(std::exception e){
					objret.set("error", e.what());
					Poco::JSON::Stringifier::stringify(objret,response.send());
					std::cerr<<e.what()<<std::endl;
				}
				Poco::JSON::Stringifier::stringify(objret,response.send());


			}else{
				response.setContentType("application/json");
				Poco::JSON::Object obj;
				obj.set("error", "invalid method");
				Poco::JSON::Stringifier::stringify(obj,response.send());
				std::cerr<<"invalid method"<<std::endl;
			}
		}
	private:
		std::string _format;
};
class TimeRequestHandlerFactory: public HTTPRequestHandlerFactory{
	public:
		TimeRequestHandlerFactory(const std::string& format)
			:_format(format)
		{
		}

		HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
		{
//Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, "/echo");
			
			if(request.getURI()=="/")
				return new TimeRequestHandler(_format);
			return 0;
		}
	private:
		std::string _format;
};

class HTTPTimeServer: public Poco::Util::ServerApplication{
	public:
		HTTPTimeServer()
			:_helpRequested(false)
		{
		}

		~HTTPTimeServer()
		{
		}

	protected:
		void initialize(Application& self)
		{
			loadConfiguration();
			ServerApplication::initialize(self);
		}

		void uninitialize()
		{
			ServerApplication::uninitialize();
		}

		void defineOptions(OptionSet& options)
		{
			ServerApplication::defineOptions(options);

			options.addOption(
				Option("help","h","display argument help information")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<HTTPTimeServer>(this,&HTTPTimeServer::handleHelp))
			);
		}

		void handleHelp(const std::string& name,const std::string& value)
		{
			HelpFormatter helpFormatter(options());
			helpFormatter.setCommand(commandName());
			helpFormatter.setUsage("OPTIONS");
			helpFormatter.setHeader("A web server that serves the current date and time.");
			helpFormatter.format(std::cout);
			stopOptionsProcessing();
			_helpRequested=true;
		}

		int main(const std::vector<std::string>& args)
		{
			if (!_helpRequested)
			{
				unsigned short port=(unsigned short)config().getInt("HTTPTimeServer.port",8080);
				std::string format(config().getString("HTTPTimeServer.format", DateTimeFormat::SORTABLE_FORMAT));
				ServerSocket svs(port);
				HTTPServer srv(new TimeRequestHandlerFactory(format),svs,new HTTPServerParams);
				srv.start();
				waitForTerminationRequest();
				srv.stop();
			}
			return Application::EXIT_OK;
		}
	private:
		bool _helpRequested;
};
int main(int argc,char** argv){
	HTTPTimeServer app;
	return app.run(argc,argv);
}
