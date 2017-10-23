//-----------------------------------------------------------------------------
// Author: Natnael Tezera
// created date: 4/10/2017
// Last modified data: 4/21/2017
//
//-----------------------------------------------------------------------------
// Purpose: This file is a driver class. it is an entry file for this project. 
//			It includes bintree.h to access. it tests the different functions
//			that are implemented in bintree.cpp.
// Assumption: The buildTree method in this class is is provided with the 
//			assignment
//-----------------------------------------------------------------------------


// presumably bintree.h includes nodedata.h so the include is not needed here

#include "bintree.h"

#include <fstream>

#include <iostream>


using namespace std;


const int ARRAYSIZE = 100;		 // array size



								 //global function prototypes

void buildTree(BinTree&, ifstream&);     //  

void initArray(NodeData*[]);             // initialize array to NULL



int main() {





	// create file object infile and open it

	ifstream infile("inputdata.txt");

	if (!infile) {

		cout << "File could not be opened." << endl;


	}

	// the NodeData class must have a constructor that takes a string
	NodeData goatND("goat");

	NodeData lionND("lion");

	NodeData birdND("bird");

	NodeData foxND("fox");

	NodeData apeND("ape");

	NodeData snakeND("snake");

	NodeData zebraND("zebra");

	NodeData plantND("orange");

	NodeData wolfND("wolf");



	BinTree T, T2, dup;		// test default constructor

	NodeData* ndArray[ARRAYSIZE];

	initArray(ndArray);

	cout << "Initial data:" << endl << "  ";

	buildTree(T, infile);              // builds and displays initial data

	cout << endl;

	BinTree first(T);                  // test copy constructor

	dup = dup = T;                     // test operator=, self-assignment


	while (!infile.eof()) {

		cout << "Tree Inorder:" << endl << T; 	// operator<< does endl
		cout << endl;

		T.displaySideways();



		// test retrieve

		NodeData* p;                    // pointer of retrieved object


		bool found;                     // whether or not object was found 
										// in tree


		found = T.retrieve(goatND, p);

		cout << "Retrieve --> goat: " << (found ? "found" : "not found") << endl;
		found = T.retrieve(lionND, p);

		cout << "Retrieve --> lion: " << (found ? "found" : "not found") << endl;
		found = T.retrieve(plantND, p);

		cout << "Retrieve --> plant: " << (found ? "found" : "not found") << endl;



		// test getHeight

		cout << "Height   --> goat:  " << T.getHeight(goatND) << endl;
		cout << "Height   --> lion:  " << T.getHeight(lionND) << endl;
		cout << "Height   --> plant:  " << T.getHeight(plantND) << endl;
		cout << "Height   --> zebra:  " << T.getHeight(zebraND) << endl;
		cout << "Height   --> fox:  " << T.getHeight(foxND) << endl;
		cout << "Height   --> bird:  " << T.getHeight(birdND) << endl;


		// test ==, and !=

		T2 = T;

		cout << "T == T2?    " << (T == T2 ? "equal" : "not equal") << endl;
		cout << "T != first? " << (T != first ? "not equal" : "equal") << endl;
		cout << "T == dup?   " << (T == dup ? "equal" : "not equal") << endl;
		dup = T;



		// Checks if the tree is empty after the call to bsTreeToArray
		T.bsTreeToArray(ndArray);

		if (T.isEmpty()) {

			cout << "The tree is empty after call to bsTreeToArray function"
				<< endl << endl;

		}


		cout << "Test bsTreeToArray(ndArray): " << endl;

		cout << "Below are elements in the array before arrayToBST call:" << endl;
		for (int i = 0; i < ARRAYSIZE; i++) {

			if (ndArray[i] != NULL) {
				cout << *ndArray[i] << " ";

			}

		}

		cout << endl;



		// Checks if the array is filled with NULL after the call to arrayToBST
		T.arrayToBSTree(ndArray);

		T.displaySideways();

		bool isEmpty = true;
		// flag to show if the array is null

		for (int i = 0; i < ARRAYSIZE; i++) {

			if (ndArray[i] != NULL) {

				cout << *ndArray[i] << " ";
				isEmpty = false;

			}

		}

		if (isEmpty) {

			cout << "the array is empty. all values set to NULL.";
		}
		else {

			cout << "The array is not empty ";

		}
		cout << endl;





		T.makeEmpty();        // empty out the tree


		initArray(ndArray);             // empty out the array


		cout << "-------------------------------------------------------------"
			<< endl;


		cout << "Initial data:" << endl << "  ";

		buildTree(T, infile);

		cout << endl;


	}

	system("pause");

}




//------------------------------- buildTree ----------------------------------

// To build a tree, read strings from a line, terminating when "$$" is

// encountered. Since there is some work to do before the actual insert that is

// specific to the client problem, it's best that building a tree is not a

// member function. It's a global function.
//-----------------------------------------------------------------------------


void buildTree(BinTree& T, ifstream& infile) {

	string s;


	for (;;) {

		infile >> s;

		cout << s << ' ';

		if (s == "$$") break;                // at end of one line

		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
											 // would do a setData if there were more than a string



		bool success = T.insert(ptr);

		if (!success)

			delete ptr;                       // duplicate case, not inserted

	}

}



//------------------------------- initArray ----------------------------------

// initialize the array of NodeData* to NULL pointers

void
initArray(NodeData* ndArray[]) {

	for (int i = 0; i < ARRAYSIZE; i++)

		ndArray[i] = NULL;

}

