
///////////////////////////////////////////////////////////////////////
// Display.h - Display XML Tree                                      //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Platform:    Lenovo_Z510, Core i5, Windows 8                      //
// Application: Spring Projects, 2015                                //
// Author:      Arunbalaji Sivakumar, MS-CE, Syracuse University     //
//              (845) 453-5920, asivak01@syr.edu                     //
///////////////////////////////////////////////////////////////////////
#include "Display.h"
#include <iostream>
using namespace std;
using namespace XmlProcessing;
/*  ---------------------------------  To display the XML Tree  -----------------------------------  */
void Display::displayXMLTree(shared_ptr < AbstractXmlElement > sPtr)
{
	cout<<endl<<sPtr->toString()<<endl;
}


#ifdef TEST_DISPLAY
int main()
{
	using ptr = shared_ptr < AbstractXmlElement >;
	cout << "testing Dispaly package" << endl;
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
	Display disp;
	disp.displayXMLTree(doc);
}
#endif