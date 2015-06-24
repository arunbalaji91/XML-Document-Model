#ifndef XMLPARSER_H
#define XMLPARSER_H
///////////////////////////////////////////////////////////////////
// XMLParser.h - To Create XML Tree                              //
//                                                               //
// ver 1.2                                                       //
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
* The package gets the parsed XML elements from the XMLReader and builds a tree 
* using those elements. This package uses the STL Stack to implement the tree.
*
* Required Files:
* ---------------
*   - XmlParser.h, XmlParser.cpp
*   - XmlElement.h, XmlElement.cpp
*   - XmlReader.h, XmlReader.cpp
*
* Required Files:
* ---------------
*   - XmlElement.h, XmlElement.cpp
*
* Build Process:
* --------------
*   cd compile
*
* Maintenance History:
* --------------------
* ver 1.2 : 26 mar 15
* - Added STL Stack to to arrange the nodes of the tree
* ver 1.1 : 24 Mar 15
* - Added functions to process XMLDeclaration, Process Instruction, Comment instruction and Root element
* Ver 1.0 : 20 Mar 15
* - first release
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include "../XmlReader/XmlReader.h"
#include "../XMLDocument/XmlElement.h"

using namespace std;


namespace XmlProcessing
{
	class XMLParser
	{
	public:
		XMLParser(){ docEl = NULL; counter = 0; }
		shared_ptr < AbstractXmlElement > Get_from_XMLR(string);
		void Generate_Tree(XmlReader);
		string Check_String_Body(string);
		void makeCommentNode(XmlReader, shared_ptr < AbstractXmlElement >);
		void containsAttribute(XmlReader, shared_ptr < AbstractXmlElement >);
		bool containsTagsText(XmlReader, shared_ptr < AbstractXmlElement >);
		void makeProcInstrNode(XmlReader, shared_ptr <AbstractXmlElement>);
		void makeXmlDeclareNode(XmlReader, shared_ptr <AbstractXmlElement>);
		int numOfSubTags(string, XmlReader);
		vector<string> numOfChildren(string);
		void numOfChildren_Pop(string, stack<string>&, vector<string>&);
		void numOfChildren_SelfClose(string, stack<string>&, vector<string>&);

		vector<string> getManualAttre(string);
		string getString(size_t, size_t, string);
		void bigStackPush(XmlReader, stack<shared_ptr <AbstractXmlElement>>&, string);
		int bigStackPop(stack<shared_ptr <AbstractXmlElement>>&, string, string);
		void handleSelfCloseTags(XmlReader, stack<shared_ptr <AbstractXmlElement>>&, string, string, size_t);
		void handleComments(XmlReader, stack<shared_ptr <AbstractXmlElement>>&, string, string, size_t);
		void handleProcInstr(XmlReader, stack<shared_ptr <AbstractXmlElement>>&, string, string, size_t);

	private:
		shared_ptr < AbstractXmlElement > docEl;
		int counter;
	};
}
#endif