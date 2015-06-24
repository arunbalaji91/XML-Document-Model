#include "XMLParser.h"
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
using namespace XmlProcessing;
using namespace std;


/* ------------------------------- Get the Xml string from Executive ----------------------------------*/
shared_ptr < AbstractXmlElement > XMLParser::Get_from_XMLR(string input_text){
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	size_t s = 0, e = 0;
	XmlReader xrd(input_text);	xrd.reset();
	docEl = makeDocElement(NULL);
	if (xrd.xml().size() == 0){
		cout << "empty xml tree" << endl;
	}
	else{
		while (xrd.next())
		{		
			if (xrd.tag() == "?xml")
			{
				makeXmlDeclareNode(xrd, docEl);
			}			
			else if (xrd.tag() == "!--")
			{
				makeCommentNode(xrd, docEl);
			}			
			else if ((xrd.tag()[0] == '?') && (xrd.tag() != "?xml"))//is proc
			{
				makeProcInstrNode(xrd, docEl);
			}
			else
			{
				s = xrd.xml().find("<", xrd.position());
				e = xrd.xml().find(">", xrd.position());
				if (xrd.xml()[e - 1] == '/')
				{
					sPtr child = makeTaggedElement(xrd.tag());
					containsAttribute(xrd, child);
					child->selfCloseTag(1);
					docEl->addChild(child);
				}
				else 
				{	break;	}
			}
		}
		Generate_Tree(xrd);
	}
	return docEl;
}

/* ------------------------------- To manually get the attributes from the line ----------------------------------*/
vector<string> XMLParser::getManualAttre(string text){
	size_t s = 0, e = 0, pos = 0;
	vector<string> v;
	while (pos < text.size())	{
		e = text.find("=", s);
		v.push_back(getString(s, e - 1, text));
		s = e + 2;
		e = text.find("\"", s);
		v.push_back(getString(s, e - 1, text));
		s = e + 2;
		pos = e + 1;
	}
	return v;
}

/* ------------------------------- To process The Process Instruction Elements ----------------------------------*/
void XMLParser::makeProcInstrNode(XmlReader xrdPtr, shared_ptr < AbstractXmlElement > srd_ptr)
{
	string str = xrdPtr.tag();
	cout << "inside proc declare" << endl;
	shared_ptr<AbstractXmlElement> child;
	child = makeProcInstrElement(xrdPtr.tag());

	size_t s = xrdPtr.position() + xrdPtr.tag().size() + 1;
	size_t e = xrdPtr.xml().find("?>", s);

	vector<string> attrvalue = getManualAttre(getString(s, e - 1, xrdPtr.xml()));
	for (size_t i = 0; i < attrvalue.size(); i += 2){
		child->addAttrib(attrvalue[i], attrvalue[i + 1]);
	}
	child->selfCloseTag(1);
	srd_ptr->addChild(child);
	std::cout << " aftr addin proc declaration \n " << srd_ptr->toString() << endl;
}

/* ------------------------------- To process the XML Declaration Elements ----------------------------------*/
void XMLParser::makeXmlDeclareNode(XmlReader xrdPtr, shared_ptr < AbstractXmlElement > srd_ptr)
{
	shared_ptr<AbstractXmlElement> child;
	child = makeXmlDeclarElement(xrdPtr.tag());
	size_t s = xrdPtr.tag().size() + 1;
	size_t e = xrdPtr.element().find("?>");
	vector<string> attrvalue = getManualAttre(getString(s, e - 1, xrdPtr.element()));
	for (size_t i = 0; i < attrvalue.size(); i += 2)
	{		child->addAttrib(attrvalue[i], attrvalue[i + 1]);	}
	child->selfCloseTag(1);
	srd_ptr->addChild(child);
}


/* ------------------------------- To process the comment Elements ----------------------------------*/

void XMLParser::makeCommentNode(XmlReader xrdPtr, shared_ptr < AbstractXmlElement > srd_ptr){
	string str = xrdPtr.tag();
	using sPtr = shared_ptr < AbstractXmlElement >;

	str = xrdPtr.element();
	int s = str.find("<!--");
	int e = str.find("-->");
	sPtr child = makeCommentElement(getString(s + 4, e - 1, xrdPtr.element()));
	child->selfCloseTag(1);
	srd_ptr->addChild(child);
}

/* ------------------------------- To check if the element has attributes ----------------------------------*/

void XMLParser::containsAttribute(XmlReader xrdPtr, shared_ptr < AbstractXmlElement > srd_ptr)
{
	XmlReader::attribElems attribs = xrdPtr.attributes();

	if (attribs.size() > 0)	{
		for (size_t i = 0; i < attribs.size(); ++i)
		{		srd_ptr->addAttrib(attribs[i].first, attribs[i].second);	}
	}
}

/* ------------------------------- To check if elements has text ----------------------------------*/

bool XMLParser::containsTagsText(XmlReader xrdPtr, shared_ptr < AbstractXmlElement > srd_ptr)
{
	string body = xrdPtr.body();
	string temp = "";
	string str = xrdPtr.tag();
	size_t endI = 0;
	if (body.size() == 0)
		return false;

	if (body[0] != '<')	{
		endI = body.find('<');
		if (endI != body.npos)	{
			temp = getString(0, endI - 1, body);
		}
		else {
			temp = body;
		}
	}
	else if (body[body.size() - 1] != '>')	{
		endI = body.rfind("</");
		endI = body.find('>', endI);
		temp = getString(endI + 1, body.size() - 1, body);
	}
	else	{
		while (endI != body.size())
		{
			endI = body.find("</", endI);
			endI = body.find('>', endI);
			if (body[endI + 1] != '<' && (endI + 1) != body.size())	{
				temp = getString(endI + 1, body.find('<', endI) - 1, body);
				break;
			}
			endI++;
		}
	}
	if (!temp.empty())	{
		srd_ptr->addChild(makeTextElement(temp));
		return true;
	}
	return false;
}

/* ------------------------------- To get substring based on index ----------------------------------*/

string XMLParser::getString(size_t s, size_t e, string str)
{
	string result = "";
	while (s <= e)
	{
		result += str[s++];
	}
	return result;
}

/* ------------------------------- To get the names of children of an element ----------------------------------*/

vector<string> XMLParser::numOfChildren(string body)//passing elements
{
	stack<string> impStack;
	vector<string> children;
	string str;
	size_t s = 0, e = 0, pos = 0, ne = 0;
	int numchild = 0;
	s = body.find("<", pos);e = body.find(">", pos);
	if (s == string::npos && e == string::npos)
	{		return children;	}
	while (pos < body.size())
	{
		s = body.find("<", pos);
		e = body.find(">", pos);
		pos = e + 1; ne = e;
		for (size_t i = s; i < e; i++)	{
			if (isspace(body[i]))	{
				ne = i;	break;
			}
		}
		if (body[s + 1] != '/' && body[e - 1] != '/' && body[e - 1] != '-' && body[e - 1] != '?'){
			str = getString(s + 1, ne - 1, body);
			impStack.push(str);
		}    //(stack<> impStack, string str, )
		else if (body[s + 1] == '/'){
			str = getString(s + 2, e - 1, body);
			numOfChildren_Pop(str, impStack, children);
		} 
		else if (body[e - 1] == '/' || body[e - 1] == '-' || body[e - 1] == '?'){
			if (impStack.size() == 1)
			{
				numchild++;
				children.push_back(getString(s + 1, ne - 1, body));
			}
		}
	}
	return children;
}


void XMLParser::numOfChildren_Pop(string str, stack<string> &impStack, vector<string> &children)
{
	if (impStack.size() != 0 && str.compare(impStack.top()) == 0){
		if (impStack.size() == 2){

			children.push_back(impStack.top());
			impStack.pop();
		}
		else
		{
			impStack.pop();
		}
	}
}


/* ------------------------------- To perform push operation on stack ----------------------------------*/

void XMLParser::bigStackPush(XmlReader newxrdPtr, stack<shared_ptr <AbstractXmlElement>> &impStack, string element)
{
	using sPtr = shared_ptr < AbstractXmlElement >;

	sPtr child = makeTaggedElement(newxrdPtr.tag());
	if (containsTagsText(newxrdPtr, child)){}
	containsAttribute(newxrdPtr, child);
	string tempelement = getString(newxrdPtr.position() - 1, element.find("</" + newxrdPtr.tag() + ">", newxrdPtr.position() - 1) + newxrdPtr.tag().size() + 2, element);
	child->getNumofChilds(numOfChildren(tempelement).size());
	impStack.push(child);
}

/* ------------------------------- To perform pop operation on stack ----------------------------------*/
int XMLParser::bigStackPop(stack<shared_ptr <AbstractXmlElement>> &impStack, string element, string temp)
{
	if (impStack.size() != 0 && temp.compare(impStack.top()->value()) == 0){
		using sPtr = shared_ptr < AbstractXmlElement >;
		sPtr pop1 = impStack.top();
		impStack.pop();
		if (impStack.size() == 0){
			docEl->addChild(pop1);
			return 0;
		}
		if (impStack.top()->numofChild() > 0){
			sPtr pop0 = impStack.top();
			impStack.pop();
			pop0->addChild(pop1);
			pop0->getNumofChilds(pop0->numofChild() - 1);
			impStack.push(pop0);
		}
		else
		{		impStack.push(pop1);		}
	}
	return 1;
}


/* ------------------------------- To handle self closing tags on stack ----------------------------------*/
void XMLParser::handleSelfCloseTags(XmlReader newxrdPtr, stack<shared_ptr <AbstractXmlElement>> &impStack, string element, string temp, size_t s)
{
	using sPtr = shared_ptr < AbstractXmlElement >;
	if (impStack.size() != 0){
		sPtr pop0 = impStack.top();
		impStack.pop();
		newxrdPtr.position(s + 1);

		sPtr child = makeTaggedElement(newxrdPtr.tag());
		if (containsTagsText(newxrdPtr, child)){}
		containsAttribute(newxrdPtr, child);
		child->selfCloseTag(1);

		if (pop0->numofChild() > 0)	{
			pop0->addChild(child);
			pop0->getNumofChilds(pop0->numofChild() - 1);
			impStack.push(pop0);
		}
	}
}

/* ------------------------------- To handle comment elements ----------------------------------*/
void XMLParser::handleComments(XmlReader newxrdPtr, stack<shared_ptr <AbstractXmlElement>> &impStack, string element, string temp, size_t s)
{
	using sPtr = shared_ptr < AbstractXmlElement >;
	if (impStack.size() != 0){
		sPtr pop0 = impStack.top();
		impStack.pop();
		newxrdPtr.position(s + 1);
		sPtr child = makeCommentElement(temp);
		child->selfCloseTag(1);

		if (pop0->numofChild() > 0)	{
			pop0->addChild(child);
			pop0->getNumofChilds(pop0->numofChild() - 1);
			impStack.push(pop0);
		}
	}
}

/* ------------------------------- To handle Process Instructions ----------------------------------*/
void XMLParser::handleProcInstr(XmlReader newxrdPtr, stack<shared_ptr <AbstractXmlElement>> &impStack, string element, string temp, size_t s)
{
	using sPtr = shared_ptr < AbstractXmlElement >;
	if (impStack.size() != 0)	{
		sPtr pop0 = impStack.top();
		impStack.pop();

		newxrdPtr.position(s + 1);
		sPtr child = makeProcInstrElement(newxrdPtr.tag());
		s = newxrdPtr.tag().size() + 1;
		vector<string> attrvalue = getManualAttre(getString(s, temp.size() -1 , temp));
		for (size_t i = 0; i < attrvalue.size(); i += 2)
		{	child->addAttrib(attrvalue[i], attrvalue[i + 1]);	}
		child->selfCloseTag(1);
		if (pop0->numofChild() > 0){
			pop0->addChild(child);
			pop0->getNumofChilds(pop0->numofChild() - 1);
			impStack.push(pop0);
		}
	}
}

/* ------------------------------- To generate XML Tree ----------------------------------*/
void XMLParser::Generate_Tree(XmlReader xrdPtr)
{
	size_t s = 0, e = 0, ne = 0, opos = 0;
	using sPtr = shared_ptr < AbstractXmlElement >;
	int check = 1;
	XmlReader newxrdPtr(xrdPtr.element());
	newxrdPtr.reset(); newxrdPtr.next();
	opos = newxrdPtr.position() - 1;	
	string temp, element = newxrdPtr.element();
	stack<sPtr> impStack;
	vector<string> childs_count;	
	while (opos < newxrdPtr.xml().size()){
		s = element.find("<", opos);
		e = element.find(">", opos);
		opos = e + 1; ne = e;
		for (size_t i = s; i < e; i++){
			if (isspace(element[i]))
			{	ne = i;	break;	}
		}
		if (element[s + 1] != '/' && (element[e - 1] != '/' && element[e - 1] != '-' && element[e - 1] != '?')){
			newxrdPtr.position(s+1);
			bigStackPush(newxrdPtr, impStack, element);
			newxrdPtr.position(opos);
		}
		else if (element[s + 1] == '/'){
			temp = getString(s + 2, ne - 1, element);
			check = bigStackPop(impStack, element, temp);
			if (check == 0)
			{	break;	}
		}
		else if (element[e - 1] == '/')
		{
			temp = getString(s + 1, ne - 1, element);
			handleSelfCloseTags(newxrdPtr, impStack, element, temp, s);
		}
		else if (element[e - 1] == '-')
		{
			temp = getString(s + 4, e - 3, element);
			handleComments(newxrdPtr, impStack, element, temp, s);
		}
		else if (element[e - 1] == '?')
		{
			temp = getString(s + 2, e - 2, element);
			handleProcInstr(newxrdPtr, impStack, element, temp, s);
		}
	}
}

#ifdef TEST_XMLPARSER
int main()
{
	using ptr = shared_ptr < AbstractXmlElement >;
	cout<<"testing XML Parser"<<endl;
	stack<ptr> stk;

	ptr child1 = makeTaggedElement("child1");
	ptr child2 = makeTaggedElement("child2");
	ptr child3 = makeTaggedElement("child3");
	stk.push(child1);
	stk.push(child2);
	stk.push(child3);
	ptr doc = makeDocElement();
	for (size_t i = 0; i < stk.size(); i++)
	{
		ptr p = stk.top();
		stk.pop();
		doc->addChild(p);
	}
	cout << endl << doc->toString() << endl;

}
#endif