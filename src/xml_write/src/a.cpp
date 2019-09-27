#include"util/range.h"
#include"Poco/DOM/Document.h"
#include"Poco/DOM/Element.h"
#include"Poco/DOM/Text.h"
#include"Poco/DOM/AutoPtr.h"
#include"Poco/DOM/DOMWriter.h"
#include"Poco/XML/XMLWriter.h"
#include<iostream>
using Poco::XML::Document;
using Poco::XML::Element;
using Poco::XML::Text;
using Poco::XML::AutoPtr;
using Poco::XML::DOMWriter;
using Poco::XML::XMLWriter;
int main(int argc,char** argv){
	AutoPtr<Document> pDoc=new Document;
	AutoPtr<Element> pRoot=pDoc->createElement("root");
	pDoc->appendChild(pRoot);
	for(char a:util::rangeE('a','z',1)){
		AutoPtr<Element> pChild1=pDoc->createElement(std::string(1,a));
		for(char b:util::rangeE('a','z',1)){
			pChild1->setAttribute(std::string(1,b),std::string(1,b));
		}
		for(float b:util::rangeE<float, float>(0,1,0.2)){
			AutoPtr<Element> pChild2 = pDoc->createElement(std::string(1,a));
			AutoPtr<Text> pText3 = pDoc->createTextNode(std::to_string(b));
			pChild2->appendChild(pText3);
			pChild1->appendChild(pChild2);
		}
		pRoot->appendChild(pChild1);
	}
	DOMWriter writer;
	writer.setNewLine("\n");
	writer.setOptions(XMLWriter::PRETTY_PRINT);
	writer.writeNode(std::cout, pDoc);
	return 0;
}


