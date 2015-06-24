///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes               //
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
#include <iostream>
#include "XmlDocument.h"


using namespace XmlProcessing;

using sPtr = shared_ptr<AbstractXmlElement>;


/* ------------------------------------------  Constructor for XmlDocument  --------------------------------------*/
XmlProcessing::XmlDocument::XmlDocument()
{
	pDocElement_ = NULL; 
}

/* ------------------------------------------  To call the XMlParser to start processing and generating the tree  --------------------------------------*/
void XmlDocument::generateXMLTree(std::string input_text)
{
	XMLParser xmlp;
	pDocElement_ = xmlp.Get_from_XMLR(input_text);
}

/* ------------------------------------------  TO display the tree  --------------------------------------*/
sPtr XmlDocument::displayXMLTree()
{
	return pDocElement_;
}


/* ------------------------------------------  To implement move constructor  --------------------------------------*/
TaggedElement XmlDocument::moveTaggedElements_a()
{
	TaggedElement newtagged("Professor");
	std::vector<std::string>newElementAttributes = { "Name", "Jim Fawcett", "college", "Syracuse University" };
	for (size_t i = 0; i < newElementAttributes.size(); i += 2)
		newtagged.addAttrib(newElementAttributes[i], newElementAttributes[i + 1]);
	cout <<endl<< "newly created tagged element inside a function :\n" << newtagged.toString() << endl;
	return newtagged;
}


/* ------------------------------------------  To demonstrate requirement 5  --------------------------------------*/

shared_ptr <AbstractXmlElement> XmlDocument::R5(std::string attribute)
{
	sPtr element = DFSforR5(pDocElement_, attribute);
	return element;
}

/* ------------------------------------------  using DFS for requirement 5  --------------------------------------*/
shared_ptr<AbstractXmlElement> XmlDocument::DFSforR5(sPtr docEl, std::string attribute)
{
	std::stack<sPtr> nodeStack;
	nodeStack.push(docEl);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0){
		pCurrentNode = nodeStack.top();
		nodeStack.pop();
		for (auto attr : pCurrentNode->attributes()){
			if (attr.first == attribute)
				return pCurrentNode;
		}
		size_t numChildren = pCurrentNode->children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}
	return pCurrentNode;
}

/* ------------------------------------------  To demonstrate requirement 6  --------------------------------------*/

vector<shared_ptr<AbstractXmlElement>> XmlDocument::R6(std::string tagName)
{
	DFSforR6(pDocElement_, tagName);
	return found_;
}

/* ------------------------------------------  using DFS for requirement 6  --------------------------------------*/

void XmlDocument::DFSforR6(shared_ptr<AbstractXmlElement> docEl, std::string tagName)
{
	found_.empty();
	std::stack<sPtr> nodeStack;
	nodeStack.push(docEl);
	while (nodeStack.size() > 0){
		sPtr pCurrentNode = nodeStack.top();
		nodeStack.pop();
		if (pCurrentNode->value() == tagName)
		{	found_.push_back(pCurrentNode);		}
		size_t numChildren = pCurrentNode->children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->children()[numChildren - i - 1]);
	}
}

/* ------------------------------------------  To demonstrate requirement 7  --------------------------------------*/

bool XmlDocument::R7a(std::string attribute, std::string newChildName, std::string newChildText, std::vector<std::string> newChildAttributes)
{
	bool result = false;
	sPtr element = DFSforR5(pDocElement_, attribute);
	if ((element != NULL) && (!element->isSelfClose())){
		sPtr newChild = makeTaggedElement(newChildName);
		if (!newChildText.empty())
			newChild->addChild(makeTextElement(newChildText));
		if (!newChildAttributes.empty()){
			for (size_t i = 0; i < newChildAttributes.size(); i += 2)
			{		newChild->addAttrib(newChildAttributes[i], newChildAttributes[i + 1]);		}
		}
		cout << "\n " << newChild->toString() << endl;
		cout << "before adding new child...\n " << element->toString() << endl;
		cout << "before adding new child size...\n " << element->children().size() << endl;

		element->addChild(newChild);
		cout << "after adding new child...\n " << element->toString() << endl;
		cout << "after adding new child size...\n " << element->children().size() << endl;
		result = true;
	}
	return result;
}

/* ------------------------------------------  using DFS for requirement 7  --------------------------------------*/

sPtr XmlDocument::DFSforR7b(sPtr docEl, std::string tagName)
{
	std::stack<sPtr> nodeStack;
	nodeStack.push(docEl);
	sPtr pCurrentNode = NULL;
	while (nodeStack.size() > 0){
		pCurrentNode = nodeStack.top();
		nodeStack.pop();
		if (pCurrentNode->value() == tagName)
		{			return pCurrentNode;		}
		size_t numChildren = pCurrentNode->children().size();
		for (size_t i = 0; i < numChildren; ++i)
			nodeStack.push(pCurrentNode->children()[numChildren - i - 1]);
		pCurrentNode = NULL;
	}
	return pCurrentNode;
}

/* ------------------------------------------  To demonstrate requirement 7  --------------------------------------*/

bool XmlDocument::R7b(std::string elementName, std::string newChildName, std::string newChildText, std::vector<std::string> newChildAttributes)
{
	bool result = false;
	sPtr element = DFSforR7b(pDocElement_, elementName);
	if ((element != NULL) && (!element->isSelfClose()))	{
		sPtr newChild = makeTaggedElement(newChildName);
		if (!newChildText.empty())
			newChild->addChild(makeTextElement(newChildText));
		if (!newChildAttributes.empty())	{
			for (size_t i = 0; i < newChildAttributes.size(); i += 2)
			{	newChild->addAttrib(newChildAttributes[i], newChildAttributes[i + 1]);	}
		}
		cout << "\n " << newChild->toString() << endl;
		cout << "before adding new child...\n " << element->toString() << endl;
		cout << "before adding new child size...\n " << element->children().size() << endl;

		element->addChild(newChild);
		cout << "after adding new child...\n " << element->toString() << endl;
		cout << "after adding new child size...\n " << element->children().size() << endl;
		result = true;
	}
	return result;
}

/* ------------------------------------------  To demonstrate requirement 7  --------------------------------------*/

bool XmlDocument::R7c(std::string attribute, std::string elementName)
{
	bool result = false;
	sPtr element = DFSforR5(pDocElement_, attribute);
	if ((element != NULL) && (!element->isSelfClose()) && (element->children().size() != 0))
	{
		sPtr childElement = DFSforR7b(element, elementName);
		cout << "before removing child element   " << endl;
		cout << element->toString() << endl;
		element->removeChild(childElement);
		cout << "after removing child element   " << endl;
		cout << element->toString() << endl;
		result = true;
	}
	return result;
}

/* ------------------------------------------  To demonstrate requirement 7  --------------------------------------*/

bool XmlDocument::R7d(std::string parentElement, std::string childElement)
{
	bool result = false;
	sPtr element = DFSforR7b(pDocElement_, parentElement);
	if ((element != NULL) && (!element->isSelfClose()) && (element->children().size() != 0))
	{
		sPtr childElementNode = DFSforR7b(element, childElement);
		cout << "before removing child element   " << endl;
		cout << element->toString() << endl;
		element->removeChild(childElementNode);
		cout << "after removing child element   " << endl;
		cout << element->toString() << endl;
		result = true;
	}
	return result;
}

/* ------------------------------------------  To demonstrate requirement 7  --------------------------------------*/

sPtr XmlDocument::R7eNewElement(std::string elementName, std::string elementText, std::vector<std::string> newChildAttributes)
{
	sPtr newElement = makeTaggedElement(elementName);
	for (size_t i = 0; i < newChildAttributes.size(); i += 2)
	{
		newElement->addAttrib(newChildAttributes[i], newChildAttributes[i + 1]);
	}
	newElement->addChild(makeTextElement(elementText));
	return newElement;
}

/* ------------------------------------------  To demonstrate requirement 7  --------------------------------------*/

bool XmlDocument::R7eChildElements(sPtr parent, std::string newChildName, std::string newChildText, std::vector<std::string> newChildAttributes)
{
	bool result = false;
	if ((parent != NULL) && (!parent->isSelfClose()))
	{
		sPtr newChild = makeTaggedElement(newChildName);
		if (!newChildText.empty())
			newChild->addChild(makeTextElement(newChildText));
		if (!newChildAttributes.empty())
		{
			for (size_t i = 0; i < newChildAttributes.size(); i += 2)
			{
				newChild->addAttrib(newChildAttributes[i], newChildAttributes[i + 1]);
			}
		}
		cout << "\n child for root element" << newChild->toString() << endl;
		cout << "parent's number of children before adding new child... " << parent->children().size() << endl;

		parent->addChild(newChild);
		cout << "after adding new child...\n " << parent->toString() << endl;
		cout << "parent's number of children before adding new child... " << parent->children().size() << endl;
		result = true;
	}
	return result;
}

/* ------------------------------------------  To demonstrate requirement 7  --------------------------------------*/

bool XmlDocument::R7eCreateNewTree(sPtr root)
{
	bool result = false;
	if (root != NULL)
	{
		pDocElement_ = makeDocElement(root);
		cout << "\n " << pDocElement_->toString() << endl;
		result = true;
	}
	return result;
}

/* ------------------------------------------  To demonstrate requirement 8  --------------------------------------*/

std::vector<std::pair<std::string, std::string>> XmlDocument::R8a(sPtr element)
{
	std::vector<std::pair<std::string, std::string>> attributes;
	attributes.empty();
	if (element != NULL)
	{
		attributes = element->attributes();
	}
	return attributes;
}

/* ------------------------------------------  To demonstrate requirement 8  --------------------------------------*/

std::vector<sPtr> XmlDocument::R8b(sPtr element)
{
	std::vector<sPtr> children;
	children.empty();
	if (element != NULL)
	{
		children = element->children();
	}
	return children;
}

/* ------------------------------------------  To demonstrate requirement 9  --------------------------------------*/

bool XmlDocument::R9a(std::string elementName, std::vector<std::string> elementAttributes)
{
	bool result = false;
	if (!elementName.empty())
	{
		sPtr element = DFSforR7b(pDocElement_, elementName);
		if (element == NULL)
			return result;
		std::string EtoS = element->toString();
		if ((EtoS.find("<!--") == EtoS.npos) && (EtoS.find("-->") == EtoS.npos) || (!element->isSelfClose()))
		{
			for (size_t i = 0; i < elementAttributes.size(); i += 2)
			{
				element->addAttrib(elementAttributes[i], elementAttributes[i + 1]);
			}
			result = true;
		}
	}
	return result;
}

/* ------------------------------------------  To demonstrate requirement 9  --------------------------------------*/

bool XmlDocument::R9b(std::string elementName, std::string attribute)
{
	bool result = false;
	if (!elementName.empty())
	{
		sPtr element = DFSforR7b(pDocElement_, elementName);
		if (element == NULL)
			return result;
		std::string EtoS = element->toString();
		if ((EtoS.find("<!--") == EtoS.npos) && (EtoS.find("-->") == EtoS.npos) || (!element->isSelfClose()))
		{
			for (auto attr :element->attributes())
			{
				if (attribute == attr.first)
				{
					element->removeAttrib(attr.first);
					break;
				}
			}
			result = true;
		}
	}
	return result;
}

#ifdef TEST_XMLDOCUMENT
int main()
{
	title("Testing XmlDocument class");

	XmlDocument doc("foobar");

	std::cout << "\n\n";
}
#endif