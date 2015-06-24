#ifndef DISPLAY_H
#define DISPLAY_H

///////////////////////////////////////////////////////////////////////
// Display.h - Display XML Tree                                      //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Platform:    Lenovo_Z510, Core i5, Windows 8                      //
// Application: Spring Projects, 2015                                //
// Author:      Arunbalaji Sivakumar, MS-CE, Syracuse University     //
//              (845) 453-5920, asivak01@syr.edu                     //
///////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* The package gets the generated XML tree and Displays it in Tree format.
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
* Ver 1.0 : 20 Mar 15
* - Added the display function
*/

#include <iostream>
#include "../XmlReader/XmlReader.h"
#include "../XMLDocument/XmlElement.h"
#include "../XMLDocument/XmlDocument.h"



namespace XmlProcessing
{
	class Display
	{
	public:
		void displayXMLTree(shared_ptr < AbstractXmlElement >);
	};
}

#endif