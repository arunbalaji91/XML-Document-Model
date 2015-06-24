#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 2.2                                                       //
// ------------------------------------------------------------- //
// copyright © Jim Fawcett, 2012                                 //
// All rights granted provided that this notice is retained      //
// ------------------------------------------------------------- //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// ------------------------------------------------------------- //
// Author:      Jim Fawcett, CST 4-187, Syracuse University      //
//              (315) 443-3948, jfawcett@twcny.rr.com            //
// ------------------------------------------------------------- //
// Modified by: Arunbalaji Sivakumar, MS-CE, Syracuse University //
//              (845) 453-5920, asivak01@syr.edu                 //
// ------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2010                   //
// Platform:    Lenovo_Z510, Core i5, Windows 8                  //
// Application: Spring Projects, 2015                            //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*
* Required Files:
* ---------------
*   -  XmlDocument.h, XmlDocument.cpp,
*   -  XmlElement.h, XmlElement.cpp
*   -  XMLParser.h, XMLParser.cpp
*
* Build Process:
* --------------
*   devenv AST.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 2.2 : 26 Mar 15
* - Added function to satisfy requirements 7,8,9
* ver 2.1 : 22 Mar 15
* - Added function to satisfy requirements 4,5,6
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*
*/

#include <memory>
#include <string>
#include <stack>
#include <vector>
#include "XmlElement.h"
#include "../XMLParser/XMLParser.h"
using namespace std;

namespace XmlProcessing
{
	class XmlDocument
	{
	public:
		using sPtr = shared_ptr<AbstractXmlElement>;

		XmlDocument();
		
		void generateXMLTree(std::string);
		sPtr displayXMLTree();

		TaggedElement moveTaggedElements_a();

		sPtr R5(std::string);
		sPtr DFSforR5(sPtr, std::string); // returns specified attribute's element

		std::vector<sPtr> R6(std::string);
		void DFSforR6(sPtr, std::string); //returns vector of elements that have specified tag

		bool R7a(std::string, std::string, std::string, std::vector<std::string>);
		
		bool R7b(std::string, std::string, std::string, std::vector<std::string>);
		sPtr DFSforR7b(sPtr, std::string); // returns first element with specified tag

		bool R7c(std::string, std::string);

		bool R7d(std::string, std::string);

		sPtr R7eNewElement(std::string, std::string, std::vector<std::string>);
		bool R7eChildElements(sPtr, std::string, std::string, std::vector<std::string>);
		bool R7eCreateNewTree(sPtr);

		std::vector<std::pair<std::string, std::string>> R8a(sPtr);
		std::vector<sPtr> R8b(sPtr);

		bool R9a(std::string, std::vector<std::string>);
		bool R9b(std::string, std::string);

	private:
		sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
		std::vector<sPtr> found_;  // query results
		
	};
}
#endif
