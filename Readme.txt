Purpose:
========
This project develops an XML parsing facility that reads XML strings or text files, builds a Document object that can be queried for information about the XML contents, supports programmatic modification of the Document and can write the revisions to another XML string or file. The project uses C++ packages to: parse the input, build a tree-based in-memory representation of the XML called a parse tree1, and support modifications of that representation. 
This facility also supports read and write operations. 
It will also support the programmatic creation of new XML strings and files.
STL containers used:
--------------------
      vector, shared_pointer, stack
      
1.	The XMLReader reads the .xml or text file and parses its content into individual identifiers. 
2.	The XMLParser recognizes each of the identifiers and generates the XML tree.

The XML tree is represented using shared_pointers and vectors.
The XML tree is constructed using stack, shared_pointer and keeping the count of number of sub tags within a tagged element.

1.	When a new element (open tag) is encountered it is pushed into the stack.
2.	When another new element is encountered it is also pushed into the stack.
3.	The attributes of pushed elements are also added to the element by popping it, adding those elements and again pushing it back.
4.	When an element with closing tag is encountered, two consecutive pops are made and the first popped element is added as the child of second popped element using shared_pointer and the second popped element is again pushed back. 

The XML tree can handle proc_instruction, comment and self_closing tags.
The tree is traversed through Depth First Searching algorithm.

Demonstrations:
===============
Requirement 4:
--------------
XMl elements are moved from one element to another using C++11 move constructors and move assignment operations.

Requirement 5:
--------------
The XML tree is searched for specific attributes.
Requirement 6:
--------------
The XML tree is searched to find collection of elements with the specified tag and returned in vector which contains pointers to those tags.
Requirement 7:
-------------
Child elements are added and removed from the XML tree.
Requirement 8:
-------------
Providing a pointer to an element returns the list of all name-value attributes of that element along with a vector containing pointer list of all the child elements.
Requirement 9:
-------------
Name-value attributes are added to any specified element that can hold attributes. 
