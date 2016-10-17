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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <array>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;

typedef class Student
{
	public:
		Student(string strName, int studID)	//Constructor
		{
			studentName = strName;			//Populating the current class with data entered by the user.
			studentID = studID;

		}
		Student();
		Student(Student& copy)
		{
			studentName = copy.studentName;
			studentID = copy.studentID;
		}
		~Student()							//Destructor
		{
		}

		int studentID;						//Holds the Student ID Number.
		string studentName;					//Holds the student's name.

}Student;

template<typename T> class tree234
{
	public:
		struct Node							//Creating the node struct containing 3 spaces for ID and names, as well as 4 pointers to other nodes.
		{
			public:
											//A, B, and C hold Student nodes.
				T* A;
				T* B;
				T* C;

				Node* left;					//Pointers to the subnodes.
				Node* m1;
				Node* m2;
				Node* right;

											//Creating a constructor that will fill the node all NULL values.
				Node()
				{
					A = NULL;
					B = NULL;
					C = NULL;
					left = m1 = m2 = right = NULL;
				}
											//Destructor for Node
				~Node()
				{
				}
											//Overloaded assignment operator.
				Node(T* valueForA)
				{
					A = new Student(valueForA->studentName, valueForA->studentID);
					B = NULL;
					C = NULL;
					left = m1 = m2 = right = NULL;
				}
											//Function to check if the tree is empty, if yes -> true.
				bool isTreeEmpty ()	
				{
					return ((A == NULL) && (B == NULL) && (C == NULL));
				}
											//Function to check if the tree is full, if yes -> true.
				bool isNodeFull ()	
				{
					return ((A != NULL) && (B != NULL) && (C != NULL));
				}
											//Function to check if the node is a leaf
				bool isLeafNode ()
				{
											//return ((left == NULL) && (m1 == NULL) && (m2 == NULL) && (right == NULL));
					if (left == NULL)
					{
						if (m1 == NULL)
						{
							if (m2 == NULL)
							{
								if (right == NULL)
								{
									return true;
								}
							}
						}
					}
					else
					{
						return false;
					}
				}
		};

		Node* root;							//Root node of the entire Tree

		tree234()	//Constructor for the tree.
		{
			root = new Node();
		}
		
		
		//Function to split the node into a parent node with 2 children. This is called when the node has 3 values.
		Node* split (Node* pCur, Node* parent)
		{
		
			if (pCur == root)
			{
				Node* newLevel = new Node(pCur->B);	//Making a new node and setting the A value to pCur->B.
				newLevel->left = new Node(pCur->A);	//Setting the left subtree to pCurs A value.
				newLevel->m1   = new Node(pCur->C);	//Setting thr m1 subtree to pCurs C value.
			
				newLevel->left->left = pCur->left;	//Filling the children of the new nodes.
				newLevel->left->m1   = pCur->m1;
				newLevel->m1  ->left = pCur->m2;
				newLevel->m1  ->m1   = pCur->right;
				
				root = newLevel;					//newLevel now becomes the new root since pCur was the old root.
				return root;						//Split the node
			}
			
			else									//There is already a parent node.
			{
				if (!parent->B)						//Parent->B is NULL
				{
					if (parent->A->studentID < pCur->B->studentID)	//Insert pCur->B into parent->B
					{
						parent->B = new T(pCur->B->studentName, pCur->B->studentID);
						delete pCur->B;
					}
					else							//parent->A > pCur->B so move parent->A to parent->B and insert pCur->B into parent->A
					{
						parent->B = new T(parent->A->studentName, parent->A->studentID);
						delete parent->A;
						parent->A = new T(pCur->B->studentName, pCur->B->studentID);
						delete pCur->B;
					}
				}
				else								//Parent->B is not NULL
				{
					if (parent->B->studentID < pCur->B->studentID)	//Insert B pCur->B into parent->C.
					{
						parent->C = new T(pCur->B->studentName, pCur->B->studentID);
						delete pCur->B;
					}
					else if (parent->A->studentID < pCur->B->studentID)	//Shift parent->B to parent->C and then insert in B.
					{
						parent->C = new T(parent->B->studentName, parent->B->studentID);
						delete parent->B;
						parent->B = new T(pCur->B->studentName, pCur->B->studentID);
						delete pCur->B;
					}
					else							//pCur->B is the smallest value so shift both parent->A and parent->B over.
					{
						parent->C = new T(parent->B->studentName, parent->B->studentID);
						delete parent->B;
						parent->B = new T(parent->A->studentName, parent->A->studentID);
						delete parent->A;
						parent->A = new T(pCur->B->studentName, pCur->B->studentID);
						delete pCur->B;
					}
				}
				
				if (parent->left == pCur)
				{
					parent->right = parent->m2;
					parent->m2 = parent->m1;
					parent->left = new Node(pCur->A);
					parent->left->left = pCur->left;
					parent->left->m1 = pCur->m1;
					parent->m1 = new Node(pCur->C);
					parent->m1->left = pCur->m2;
					parent->m1->m1 = pCur->right;
				}
				else if (parent->m1 == pCur)
				{
					parent->right = parent->m2;
					parent->m2 = new Node(pCur->C);
					parent->m2->left = pCur->m2;
					parent->m2->m1 = pCur->right;
					parent->m1 = new Node(pCur->A);
					parent->m1->left = pCur->left;
					parent->m1->m1 = pCur->m1;
				}
				else
				{
					parent->m2 = new Node(pCur->A);
					parent->m2->left = pCur->left;
					parent->m2->m1 = pCur->m1;
					parent->right = new Node(pCur->C);
					parent->right->left = pCur->m2;
					parent->right->m1 = pCur->right;
				}
				
			}
			return parent;
		}
		
		void printRoot ()
		{
			cout << "PRINTING THE ROOT" << endl;
			if (root->A != NULL) {cout << "A: " << root->A->studentID << endl;}
			if (root->B != NULL) {cout << "B: " << root->B->studentID << endl;}
			if (root->C != NULL) {cout << "C: " << root->C->studentID << endl;}
		}

		bool add (T& studentToAdd)					//Function for adding a node to the 234 tree.
		{
			Node* pCur = NULL;
			Node* parent = NULL;
			Node* tempSwap = NULL;
			pCur = root;							//Setting our current to root, we transend from there.
			T* copy = new T(studentToAdd);			//Creating a copy variable using the copy constructor.
			
													//Checking to see if the Tree is empty, if it is we insert a root node.
			if (root->isTreeEmpty())				//Tree is empty	
			{
				Node* temp = new Node(copy);		//Calling the OVERLOADED constructor for Node to set temp.A to STA
				root = temp;
				parent = pCur;
			}
			else									//Tree is not empty
			{
				while(1)
				{
					if (pCur->isNodeFull())			//The Node is full. We perform a preemptive split.
					{
						pCur = split (pCur, parent);
					}
					
													//Checks to make sure that no duplicates are able to be added.
					if (copy->studentID == pCur->A->studentID)
					{
						delete copy;				//Deleting the copy object.
						return false;
					}
					if (pCur->B != NULL && copy->studentID == pCur->B->studentID)
					{
						delete copy;				//Deleting the copy object.
						return false;
					}
					if (pCur->C != NULL && copy->studentID == pCur->C->studentID)
					{
						delete copy;				//Deleting the copy object.
						return false;
					}
					
													//Now the Student is not a duplicate, and the current level of the tree is not full.
													//Therefore we procede with normal addition to the tree.
					if (!pCur->isLeafNode())		//Checking if the Node is NOT a leaf node.
					{
						if (copy->studentID < pCur->A->studentID)
						{
							parent = pCur;			//Set the parent Node to pCur
							pCur = pCur->left;		//Setting pCur to its L pointer.
						}
						else if (pCur->B == NULL)
						{
							parent = pCur;			//Set the parent Node to pCur
							pCur = pCur->m1;		//Setting pCur to its M1 pointer.
						}
						else if (copy->studentID < pCur->B->studentID)
						{
							parent = pCur;			//Set the parent Node to pCur
							pCur = pCur->m1;		//Setting pCur to its M1 pointer.
						}
						else if (pCur->C == NULL)
						{
							parent = pCur;			//Set the parent Node to pCur
							pCur = pCur->m2;		//Setting pCur to its M2 pointer.
						}
						else if (copy->studentID < pCur->C->studentID)
						{
							parent = pCur;			//Set the parent Node to pCur
							pCur = pCur->m2;		//Setting pCur to its M2 pointer.
						}
						else
						{
							parent = pCur;			//Set the parent Node to pCur
							pCur = pCur->right;		//Setting pCur to its R pointer.
						}
					}
					else
					{
																	//Less than A so we insert in A and move A->B.
						if (copy->studentID < pCur->A->studentID)	//Inserting at A
						{
							if (pCur->B != NULL)
							{
								pCur->C = new T(pCur->B->studentName, pCur->B->studentID);
								delete pCur->B;
								pCur->B = new T(pCur->A->studentName, pCur->A->studentID);
								delete pCur->A;
							}
							else
							{
								pCur->B = new T(pCur->A->studentName, pCur->A->studentID);
								delete pCur->A;
							}
							pCur->A = new T(copy->studentName, copy->studentID);
							return true;
						}
						
						//If pCur->B is NULL we insert into B, since we already know that copy > A since our first if didn't exec.
						else if (copy->studentID > pCur->A->studentID && pCur->B == NULL)
						{
							//cout << "B is NULL, we will now insert copy into B.\n";
							pCur->B = new T(copy->studentName, copy->studentID);
							return true;
						}	
						
						//Greater than A and Less than B so we insert in B and move B->C.
						else if (copy->studentID > pCur->A->studentID && copy->studentID < pCur->B->studentID)	//Inserting at B
						{
							//cout << "We will move B to C and insert in the new B.\n";
							pCur->C = new T(pCur->B->studentName, pCur->B->studentID);
							delete pCur->B;
							pCur->B = new T(copy->studentName, copy->studentID);
							return true;
						}
						
						//Greater than A and B, so we insert into C and don't move anything.
						else if (copy->studentID > pCur->B->studentID)
						{
							pCur->C = new T(copy->studentName, copy->studentID);
							return true;
						}
						else
						{
							return true;
						}
					}
				}
			}
			return true;
		}
		
		//Function to count the number of levels in the current 234 tree.
		//I am going to simply count the levels by traveling down the left side of the tree as far as possible.
		//This is viable since the tree must have all pointers on the same level.
		int countLevels (void)
		{
			Node* pCur = NULL;
			pCur = root;								//Starting pCur at the root of the tree. AKA the top.
			int count = 0;								//Starting count is set to 0.
		
			if (pCur == NULL)
			{
				return count;
			}
			else if (pCur->left == NULL)
			{
				return (count+1);						//Exit if NULL since we have reached the final level.
			}
			while(pCur != NULL)
			{
				count++;								//Increment count since the current pCur level is not NULL.
				pCur = pCur->left;						//Set pCur to it's left Node, therefore dropping down a level.
			}
			return count;
		}
		
		//Going to parse through the tree in order to find the correct ID. Return the Name.
		void getName (int requestedID)
		{
			Node* pCur = NULL;
			pCur = root;
			int found = 0;
			
			if (root == NULL)	//Incase the tree is empty.
			{
				cout << "student not found\n";
				return;
			}
		
			while (found == 0)
			{
				if (pCur == NULL)
				{
					cout << "student not found\n";
					return;
				}
				else if ((pCur->A != NULL) && (pCur->A->studentID == requestedID))	//Best scenario
				{
					cout << pCur->A->studentName << "\n";
					found = 1;
				}
				else if ((pCur->B != NULL) && (pCur->B->studentID == requestedID))	//Best scenario
				{
					cout << pCur->B->studentName << "\n";
					found = 1;
				}
				else if ((pCur->C != NULL) && (pCur->C->studentID == requestedID))	//Best scenario
				{
					cout << pCur->C->studentName << "\n";
					found = 1;
				}
				
				if ((pCur->A != NULL) && (requestedID < pCur->A->studentID))	//Branch left
				{
					pCur = pCur->left;
				}
				else if (pCur->B == NULL)	//Branch m1
				{
					pCur = pCur->m1;
				}
				else if (requestedID < pCur->B->studentID)
				{
					pCur = pCur->m1;
				}
				else if (pCur->C == NULL)	//Branch m2
				{
					pCur = pCur->m2;
				}
				else if (requestedID < pCur->C->studentID)
				{
					pCur = pCur->m2;
				}
				else
				{
					pCur = pCur->right;
				}
			}
			return;
		}
		
		//Returns the Level of the entered ID number.
		int getLevel (int requestedID)
		{
			Node* pCur = NULL;
			pCur = root;
			int found = 0;
			int level = 0;
			
			if (root == NULL)	//Incase the tree is empty.
			{
				return -1;
			}
		
			while (found == 0)
			{
				if (pCur == NULL)
				{
					return -1;
				}
				else if ((pCur->A != NULL) && (pCur->A->studentID == requestedID))	//Best scenario
				{
					found = 1;
				}
				else if ((pCur->B != NULL) && (pCur->B->studentID == requestedID))	//Best scenario
				{
					found = 1;
				}
				else if ((pCur->C != NULL) && (pCur->C->studentID == requestedID))	//Best scenario
				{
					found = 1;
				}
				
				if ((pCur->A != NULL) && (requestedID < pCur->A->studentID))	//Branch left
				{
					pCur = pCur->left;
					level++;
				}
				else if (pCur->B == NULL)	//Branch m1
				{
					pCur = pCur->m1;
					level++;
				}
				else if (requestedID < pCur->B->studentID)
				{
					pCur = pCur->m1;
					level++;
				}
				else if (pCur->C == NULL)	//Branch m2
				{
					pCur = pCur->m2;
					level++;
				}
				else if (requestedID < pCur->C->studentID)
				{
					pCur = pCur->m2;
					level++;
				}
				else
				{
					pCur = pCur->right;
					level++;
				}
			}
			return level-1;
		}
		
		//Displays the contents of the tree in order from least to greatest.
		void displayInOrder (Node* temp)
		{
			if (temp == NULL)
			{
				return;
			}
			else
			{
				displayInOrder (temp->left);
				if (temp->A != NULL)
				{
					cout << temp->A->studentName << "," << temp->A->studentID << ";";
				}
				displayInOrder (temp->m1);
				if (temp->B != NULL)
				{
					cout << temp->B->studentName << "," << temp->B->studentID << ";";
				}
				displayInOrder (temp->m2);
				if (temp->C != NULL)
				{
					cout << temp->C->studentName << "," << temp->C->studentID << ";";
				}
				displayInOrder (temp->right);
			}
		}
		
		//Displays the number of valeus in the node. if the node is empty AKA NULL return -1;
		int countValuesInNode(int requestedID)
		{
			Node* pCur = NULL;
			pCur = root;
			int found = 0;
			int values = 0;
			
			if (root == NULL)	//Incase the tree is empty.
			{
				return -1;
			}
		
			while (found == 0)
			{
				if (pCur == NULL)
				{
					return -1;
				}
				else if ((pCur->A != NULL) && (pCur->A->studentID == requestedID))	//Best scenario
				{
					values++;
					if (pCur->B != NULL) { values++; }
					if (pCur->C != NULL) { values++; }
					found = 1;
				}
				else if ((pCur->B != NULL) && (pCur->B->studentID == requestedID))	//Best scenario
				{
					values++;
					if (pCur->A != NULL) { values++; }
					if (pCur->C != NULL) { values++; }
					found = 1;
				}
				else if ((pCur->C != NULL) && (pCur->C->studentID == requestedID))	//Best scenario
				{
					values++;
					if (pCur->A != NULL) { values++; }
					if (pCur->B != NULL) { values++; }
					found = 1;
				}
				
				if ((pCur->A != NULL) && (requestedID < pCur->A->studentID))	//Branch left
				{
					pCur = pCur->left;
				}
				else if (pCur->B == NULL)	//Branch m1
				{
					pCur = pCur->m1;
				}
				else if (requestedID < pCur->B->studentID)
				{
					pCur = pCur->m1;
				}
				else if (pCur->C == NULL)	//Branch m2
				{
					pCur = pCur->m2;
				}
				else if (requestedID < pCur->C->studentID)
				{
					pCur = pCur->m2;
				}
				else
				{
					pCur = pCur->right;
				}
			}
			return values;
		}
		
		
		void remove (int IDToRemove)
		{
			//Not implemented
			return;
		}
		
};


