#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../Display/Display.h"
#include "../XmlReader/XmlReader.h"
#include "../XMLDocument/XmlElement.h"
#include "../XMLDocument/XmlDocument.h"

using namespace XmlProcessing;
using namespace std;

#ifdef TEST_EXEC
int main(int argc, char* argv[])
{
	string temp,  input_text, ch;
	vector<string> user_input;
	using sPtr = std::shared_ptr < AbstractXmlElement >;
	user_input.assign(argv + 1, argv + argc);	
	if ((user_input[0].find(".xml") != string::npos) || (user_input[0].find(".txt") != string::npos))
	{
		ifstream readFile(user_input[0]);
		if (!readFile.is_open())
		{
			cout << "cannot open file ...." << endl;
		}
		while (getline(readFile, temp))
		{
			input_text += temp;
		}
		cout << input_text << endl;
	}
	else
	{
		input_text = "<?xml version = \"1.0\" encoding=\"utf-8\"?><!-- XML test case -->";
		input_text += "<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?><LectureNote course=\"CSE681\" class=\"SMA\">";
		input_text += "<title>XML Example #1</title><reference><title>Programming Microsoft .Net</title>";
		input_text += "<author>Jeff Prosise <note Company=\"Wintellect\"></note></author><publisher>Microsoft Press</publisher>";
		input_text += "<date>2002</date><child1 bobby=\"male\" may=\"female\"/><child2/><page>608</page></reference>";
		input_text += "<comment>Description of PCDATA</comment><!-- XML another test case --></LectureNote>";
		cout << input_text << endl;
	}
	
	XmlProcessing::XmlDocument xDoc;
	XmlProcessing::Display disp;
	/*  --------------------------------------------------------- generating tree ----------------------------------------------------  */
	xDoc.generateXMLTree(input_text);
	disp.displayXMLTree(xDoc.displayXMLTree());
	
	/*  --------------------------------------------------------- demonstrating Requirement 4 ----------------------------------------  */
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 4  --------------------------------------" << endl;
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 4a  --------------------------------------" << endl;

	TaggedElement tag (move(xDoc.moveTaggedElements_a()));
	cout << "tagged element outside the function  :" << tag.toString();

	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 4b  --------------------------------------" << endl;
	TaggedElement newtagged1("Professor");
	std::vector<std::string>newElementAttributes1 = { "Name", "Jim Fawcett", "college", "Syracuse University" };
	for (size_t i = 0; i < newElementAttributes1.size(); i += 2)
		newtagged1.addAttrib(newElementAttributes1[i], newElementAttributes1[i + 1]);

	TaggedElement newtagged2("Student");
	std::vector<std::string>newElementAttributes2 = { "Name", "Arunbalaji Sivakumar ", "semester", "III" };
	for (size_t i = 0; i < newElementAttributes2.size(); i += 2)
		newtagged2.addAttrib(newElementAttributes2[i], newElementAttributes2[i + 1]);

	cout << "before  :" << newtagged1.toString()<<endl;
	newtagged1 = move(newtagged2);
	cout << "after   :" << newtagged1.toString() << endl;
	

	/*  --------------------------------------------------------- demonstrating Requirement 5 ----------------------------------------  */
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 5  --------------------------------------" << endl;
	string attribute = "course";
	sPtr element = xDoc.R5(attribute);
	if (element == NULL)
	{		cout << "no element with attribute name :" << attribute << " exists in the tree" << endl;	}
	else
	{		cout << element->toString() << endl;	}

	/*  --------------------------------------------------------- demonstrating Requirement 6 ----------------------------------------  */
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 6  --------------------------------------" << endl;
	string tagName = "title";
	vector<sPtr> elements = xDoc.R6(tagName);
	if (!elements.empty()){
		for (auto tag : elements){
			cout << endl;
			cout << tag->toString();
		}
	}
	else
	{		cout << "no element with tag name :" << tagName << " exists in the tree" << endl;	}

	/*  --------------------------------------------------------- demonstrating Requirement 7 ----------------------------------------  */
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 7  --------------------------------------" << endl;
	cout << "\n --------------  7a. Adding a child node to an element based on element's attribute name ----------------" << endl;
	string attribute7a = "Company";
	string newChildName = "book";
	string newChildText = "Programming Windows with MFC";
	vector<string> newChildAttributes = {"price", "$39.69", "year", "1999"};
	//vector<string> newChildAttributes;//newChildAttributes.empty();

	bool result = xDoc.R7a(attribute7a, newChildName, newChildText, newChildAttributes);

	if (!result)
	{
		cout << "Unable to add new child to the tree based on the attribute :" << attribute7a << endl;
	}
	else	
	{
		cout << "added a new child to the tree based on the attribute :" << attribute7a << endl;
	}

	cout << "\n --------------  7b. Adding a child node to an element based on element's name ----------------" << endl;
	string elementName7b = "LectureNote";
	string newChildName7b = "Professor";
	string newChildText7b = "Software Modeling and Analysis";
	vector<string> newChildAttributes7b = { "Name", "Jim Fawcett", "college", "Syracuse University" };
	//vector<string> newChildAttributes;//newChildAttributes.empty();

	bool result7b = xDoc.R7b(elementName7b, newChildName7b, newChildText7b, newChildAttributes7b);

	if (!result7b)
	{
		cout << "Unable to add new child to the tree based on the element name :" << elementName7b << endl;
	}
	else
	{
		cout << "added a new child to the tree based on the element name :" << elementName7b << endl;
	}

	cout << "\n --------------  7c. Removing a child node of an element based on element's attribute name ----------------" << endl;
	string attribute7c = "course";
	string elementName7c = "Professor";
	bool result7c = xDoc.R7c(attribute7c, elementName7c);
	if (!result7c)
	{
		cout << "Unable to remove child from the tree based on the attribute name :" << attribute7c << " and element name :" << elementName7c << endl;
	}
	else
	{
		cout << "Removed child from the tree based on the attribute name :" << attribute7c << " and element name :" << elementName7c << endl;
	}

	cout << "\n --------------  7d. Removing a child node of an element based on element's name ----------------" << endl;
	string parentElement = "note";
	string childElement = "book";
	result = xDoc.R7d(parentElement, childElement);
	if (!result)
	{		cout << "Unable to remove child from the tree based on the parent element name :" << parentElement << " and child element name :" << childElement << endl;	}
	else
	{		cout << "Removed child from the tree based on the parent element name :" << parentElement << " and child element name :" << childElement << endl;	}


	cout << "\n --------------  7e. Creating a new document pointer and adding root pointer to it ----------------" << endl;
	XmlProcessing::XmlDocument xDocNew;
	
	string elementName7e = "LectureNote";
	vector<string> elementAttributes = { "course", "CSE687", "class", "OOD" };
	string elementText = "Object Oriented Design";
	sPtr newNode = xDocNew.R7eNewElement(elementName7e, elementText, elementAttributes);
	cout << "\ncreating root element\n" << newNode->toString() << endl;
	string newChildName7e = "Professor";
	string newChildText7e = "Two sessions";
	vector<string> newChildAttributes7e = { "Name", "Jim Fawcett", "college", "Syracuse University" };
	bool result7e = xDocNew.R7eChildElements(newNode, newChildName7e, newChildText7e, newChildAttributes7e);
	if (!result7e)
	{		cout << "Unable to add new child to the tree"<< endl;	}
	else
	{		cout << "added a new child to the tree"<< endl;			}
	result7e = xDocNew.R7eCreateNewTree(newNode);
	if (!result7e)
	{		cout << "Unable to add root element as child of document" << endl;	}
	else
	{		cout << "added root element as child of document \n" << endl;	}
	disp.displayXMLTree(xDocNew.displayXMLTree());

	/*  --------------------------------------------------------- demonstrating Requirement 8 ----------------------------------------  */
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 8  --------------------------------------" << endl;
	cout << "\n --------------  8a. Displaying the name-value attribute pairs of the element ----------------" << endl;
	sPtr element8a = xDoc.DFSforR7b(xDoc.displayXMLTree(), "LectureNote");
	std::vector<std::pair<std::string, std::string>> attributes = xDocNew.R8a(element8a);
	if (attributes.empty())
	{		cout << "No attributes present in the given element name \n" << endl;	}
	else
	{
		for (auto attr : attributes)
		{			cout << attr.first << " : " << attr.second << endl;		}
	}

	cout << "\n --------------  8b. Displaying the children of the element ----------------" << endl;
	std::vector<sPtr> children;
	children.empty();
	sPtr element8b = xDoc.DFSforR7b(xDoc.displayXMLTree(), "LectureNote");

	children = xDocNew.R8b(element8b);
	if (children.empty())
	{
		cout << "No children present in the given element name \n" << endl;
	}
	else
	{
		for (auto child : children)
		{
			cout << child->toString() << endl;
		}
	}

	/*  --------------------------------------------------------- demonstrating Requirement 9 ----------------------------------------  */
	cout << "\n\n -----------------------------  DEMONSTRATING REQUIREMENT 9  --------------------------------------" << endl;
	cout << "\n --------------  9a. Adding the name-value attribute pairs of the element ----------------" << endl;
	string elementName9a = "?xml-stylesheet";
	vector<string>elementAttributes9a = { "course", "CSE686", "class", "IP" };
	bool result9a = xDoc.R9a(elementName9a, elementAttributes9a);
	if (!result9a)
	{
		cout << "Unable to add attributes to the element of the tree" << endl;	
	}
	else
	{		cout << "added attributes to the element of the tree" << endl;	
			disp.displayXMLTree(xDoc.displayXMLTree());
	}
	
	cout << "\n --------------  9b. Removing the name-value attribute pairs of the element ----------------" << endl;
	string elementName9b = "LectureNote";
	string attribute9b = "course";
	result = xDoc.R9b(elementName9b, attribute9b);
	if (!result9a)
	{
		cout << "Unable to delete specified attribute from the element of the tree" << endl;
	}
	else
	{
		cout << "deleted specified attribute from the element of the tree" << endl;
		disp.displayXMLTree(xDoc.displayXMLTree());
	}
	getchar();
}
#endif