#define HTML_INDENTATION 2
#define HTML_ENDLINE "\n" 
#include <HTML/HTML.h>
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

class HTMLRequestHandler:public HTTPRequestHandler{
	public:
		HTMLRequestHandler(const std::string& format)
		{
		}
		void handleRequest(HTTPServerRequest& request,HTTPServerResponse& response){
			Application& app=Application::instance();
			app.logger().information("Request from "+request.clientAddress().toString());
			std::ostream& ostr=response.send();
			response.setChunkedTransferEncoding(false);
			response.setContentType("text/html");
			HTML::Document document("Welcome to HTML");
			document.addAttribute("lang", "en");
			// Head
			document.head() << HTML::Meta("utf-8")
				<< HTML::Meta("viewport", "width=device-width, initial-scale=1, shrink-to-fit=no");
			document.head() << HTML::Rel("stylesheet", "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css")
				.integrity("sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T").crossorigin("anonymous");
			document.head() << HTML::Style(".navbar{margin-bottom:20px;}");
			// Body
			document.body().cls("bg-light");
			// Navbar
			HTML::List navList(false, "navbar-nav mr-auto");
			navList << std::move(HTML::ListItem().cls("nav-item active") << HTML::Link("Home", "#").cls("nav-link"));
			navList << std::move(HTML::ListItem().cls("nav-item") << HTML::Link("Link", "#").cls("nav-link"));
			navList << std::move(HTML::ListItem().cls("nav-item") << HTML::Link("Disabled", "#").cls("nav-link disabled"));
			navList << std::move(HTML::ListItem().cls("nav-item dropdown")
				<< HTML::Link("Dropdown", "#").cls("nav-link dropdown-toggle").id("dropdown01").addAttribute("data-toggle", "dropdown").addAttribute("aria-haspopup", "true").addAttribute("aria-expanded", "false")
				<< (HTML::Div("dropdown-menu").addAttribute("aria-labelledby", "dropdown01")
					<< HTML::Link("Action", "#").cls("dropdown-item")
					<< HTML::Link("Another", "#").cls("dropdown-item")
				)
			);
			document << (HTML::Nav("navbar navbar-expand navbar-dark bg-dark") << (HTML::Div("collapse navbar-collapse") << std::move(navList)));
			// Content in a container
			HTML::Div main("container");
			main << HTML::Header1("Welcome to HTML").id("anchor_link_1");
			main << "Text directly in the body.";
			main << HTML::Text("Text directly in the body. ") << HTML::Text("Text directly in the body.") << HTML::Break()
				<< HTML::Text("Text directly in the body.");
			main << HTML::Paragraph("This is the way to go for a big text in a multi-line paragraph.");
			main << HTML::Link("Google", "http://google.com").cls("my_style");
			main << (HTML::Paragraph("A paragraph. ").style("font-family:arial")
				<< HTML::Text("Text child.") << HTML::Break() << HTML::Text("And more text."));
			main << (HTML::List()
				<< (HTML::ListItem("Text item"))
				<< (HTML::ListItem() << HTML::Link("Github Link", "http://srombauts.github.io").title("SRombaut's Github home page"))
				<< (HTML::ListItem() << (HTML::List()
						<< HTML::ListItem("val1")
						<< HTML::ListItem("val2"))));
			main << (HTML::Table().cls("table table-hover table-sm")
				<< HTML::Caption("Table caption")
				<< (HTML::Row() << HTML::ColHeader("A") << HTML::ColHeader("B"))
				<< (HTML::Row() << HTML::Col("Cell_11") << HTML::Col("Cell_12"))
				<< (HTML::Row() << HTML::Col("Cell_21") << HTML::Col("Cell_22"))
				<< (HTML::Row() << HTML::Col("") << HTML::Col("Cell_32")));
			main << HTML::Small("Copyright Sebastien Rombauts @ 2017-2019");
			main << HTML::Link().id("anchor_link_2");
			document << std::move(main);
			// Javascript at the end of the body
			document << HTML::Script("https://code.jquery.com/jquery-3.3.1.slim.min.js")
				.integrity("sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo").crossorigin("anonymous");
			document << HTML::Script("https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js")
				.integrity("sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1").crossorigin("anonymous");
			document << HTML::Script("https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js")
				.integrity("sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM").crossorigin("anonymous");
			ostr<< document;
		}
	private:
};
class HTMLRequestHandlerFactory: public HTTPRequestHandlerFactory{
	public:
		HTMLRequestHandlerFactory(const std::string& format)
			:_format(format)
		{
		}

		HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
		{
			if(request.getURI()=="/")
				return new HTMLRequestHandler(_format);
			return 0;
		}
	private:
		std::string _format;
};

class MyHTTPServer: public Poco::Util::ServerApplication{
	public:
		MyHTTPServer()
			:_helpRequested(false)
		{
		}

		~MyHTTPServer()
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
				.callback(OptionCallback<MyHTTPServer>(this,&MyHTTPServer::handleHelp))
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
				unsigned short port=(unsigned short)config().getInt("MyHTTPServer.port",8080);
				std::string format(config().getString("MyHTTPServer.format", DateTimeFormat::SORTABLE_FORMAT));
				ServerSocket svs(port);
				HTTPServer srv(new HTMLRequestHandlerFactory(format),svs,new HTTPServerParams);
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
	MyHTTPServer app;
	return app.run(argc,argv);
}



