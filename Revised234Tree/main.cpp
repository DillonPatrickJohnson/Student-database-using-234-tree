//	Author: Dillon Johnson
//	Date Started: December 2015
/*	PROJECT DESCRIPTION
*	Creating a 2-3-4 tree from scratch and processing standard commands via the cmd line
*	Availible Commands:
*		- add(student name,student_id)		//	Adds a student structure to the tree. The student name can contain any characters except for commas, parenthesis, and non displayable characters. The Student ID is used as the value of sorting whilst building the 234 tree itself.
*		- countLevels()						//	Displays an integer value indicating the number of levels in the tree, an empty tree has 0 levels.
*		- displayInOrder()					//	Displays the contents of the tree in order of ascending student ID number.
*		- getName(student_id)				//	Searches the tree for the student ID provided, if the name is found, the name is printed, else, print NOT FOUND.
*		- getLevel(student_id)				//	Finds the level on which the student with the specified ID number resides and prints it to the user.
*		- countValuesInNode(student_id)		//	Finds the student with the specified ID number and displays an integer representing the number of values that reside within the node.
*		- quit()
*/

// MULTIPLE TEST FILES CAN BE FOUND WITHIN THE PROJECT FILES, ALONG WITH THEIR EXPECTED OUTPUT.

#include "header.h"

int main (void)
{
	string line;

    //Instantiating the object.
    tree234 <Student>myTree;

	while (true)
	{
		getline (std::cin, line); //Gets the line from the user or file and places it into string line.

		if (0 == line.compare (0, 3, "add"))
		{
			//Retrieving the students ID number and Their name.
			int LP = line.find("(");
			int RP = line.find(")");
			int comma = line.find(",");

			string strName = line.substr(LP+1, (comma - LP - 1));
			string strID = line.substr(comma+1, (RP - comma));
			int studID = stoi(strID);

			Student SO(strName, studID);	//Calling the constructor for the Student class.

			//Call to the add function with the name of the Student and their ID number.
			myTree.add(SO);
		}
		
		else if (0 == line.compare (0, 11, "countLevels"))
		{
			int numberOfLevels;
			
			numberOfLevels = myTree.countLevels();
			
			cout << numberOfLevels << "\n";
		}
		
		else if (0 == line.compare (0, 7, "getName"))
		{
			int LP = line.find("(");
			int RP = line.find(")");

			string strID = line.substr(LP+1, (RP - LP - 1));
			int ID = stoi(strID);
			
			myTree.getName(ID);

		}
		
		else if (0 == line.compare (0, 8, "getLevel"))
		{
			int LP = line.find("(");
			int RP = line.find(")");

			string strID = line.substr(LP+1, (RP - LP - 1));
			int ID = stoi(strID);
			int level;
			
			level = myTree.getLevel(ID);

			cout << level << "\n";
		}
		
		else if (0 == line.compare (0, 14, "displayInOrder"))
		{
			myTree.displayInOrder(myTree.root);
			cout << "\n";
		}
		
		else if (0 == line.compare (0, 17, "countValuesInNode"))
		{
			int value;
			int LP = line.find("(");
			int RP = line.find(")");

			string strID = line.substr(LP+1, (RP - LP - 1));
			int ID = stoi(strID);
			value = myTree.countValuesInNode(ID);
			cout << value << "\n";
		}
		
		else if (0 == line.compare (0, 6, "remove"))
		{
			int LP = line.find("(");
			int RP = line.find(")");

			string strID = line.substr(LP+1, (RP - LP - 1));
			int ID = stoi(strID);
			
			myTree.remove(ID);

			cout << "\n";
		}

		else if (0 == line.compare (0, 4, "quit"))
		{
			cout << "Done" << '\n';
			return 0;
		}
	}
}
