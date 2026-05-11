// COPYRIGHT DASSAULT SYSTEMES 1999

// System Framework
#include "CATSetOfCATString.h"
#include "CATString.h"

// C++ standard library
#include <iostream.h>       

// Local Framework
#include <CAASysPrintUtilities.h>

/*
 * Function which creates and uses sets. Only sets of CATString
 * and sets of CATUnicodeStrings are available.
 * This sample demonstrates the use of CATSetOfCATString.
 * CATSetOfCATUnicodeString supports the same functionalities.
 */

void CAASetsSample() {

	cout << "==========================================" << endl;
	cout << "==          Create an empty set.        ==" << endl;
	cout << "==========================================" << endl;

	CATSetOfCATString	set1;
	cout << "set1 = ";
	printSet(set1);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "==     Add a few elements to the set.   ==" << endl;
	cout << "==========================================" << endl;

	set1.Add( CATString("A") );
	set1.Add( CATString("B") );
	set1.Add( CATString("D") );
	cout << "set1 = ";
	printSet(set1);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== Count the elements of the set.       ==" << endl;
	cout << "==========================================" << endl;

	cout << "set1.Size() = " << set1.Size() << endl;

	cout << "==========================================" << endl;
	cout << "== CATSetOfCATStrings have no duplicate ==" << endl;
	cout << "== elements.                            ==" << endl;
	cout << "==========================================" << endl;

	set1.Add( CATString("A"));
	cout << "set1 = ";
	printSet(set1);

	cout << endl;
	cout << "==========================================" << endl;
	cout << "== CATSetOfCATStrings use lexicographic ==" << endl;
	cout << "== order.                               ==" << endl;
	cout << "==========================================" << endl;

	set1.Add( CATString("C") );
	cout << "set1 = ";
	printSet(set1);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== CATSetOfCATStrings can be accessed   ==" << endl;
	cout << "== sequentially (caution: the first     ==" << endl;
	cout << "== item has an index equal to 1).       ==" << endl;
	cout << "==========================================" << endl;

	cout << "set1[2] = " << set1[2].ConvertToChar() << endl;

	cout << "==========================================" << endl;
	cout << "== Create a set and initialize it with  ==" << endl;
	cout << "== a C++ array of CATStrings.           ==" << endl;
	cout << "==========================================" << endl;  

	CATString *iArray = new CATString[4];
	iArray[0] = "C";
	iArray[1] = "B";
	iArray[2] = "E";
	iArray[3] = "D";
	CATSetOfCATString set2(iArray, 4);
	cout << "set2 = ";
	printSet(set2);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== Basic operations on sets: union.     ==" << endl;
	cout << "==========================================" << endl;

	CATSetOfCATString set3(set1);
	set3.Add(set2);
	cout << "set3 = ";
	printSet(set3);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== Basic operations on sets:            ==" << endl;
	cout << "== intersection.                        ==" << endl;
	cout << "==========================================" << endl;

	CATSetOfCATString set4;
	CATSetOfCATString::Intersection(set1, set2, set4);
	cout << "set4 = ";
	printSet(set4);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== Basic operations on sets:            ==" << endl;
	cout << "== difference.                          ==" << endl;
	cout << "==========================================" << endl;

	CATSetOfCATString set5(set1);
	set5.Remove(set2);
	cout << "set5 = ";
	printSet(set5);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== CATSetOfCATStrings can be converted  ==" << endl;
	cout << "== to C++ arrays.                       ==" << endl;
	cout << "==========================================" << endl;

	CATString* ioArray = new CATString[set1.Size()];
	set1.Array(ioArray);
	cout << "ioArray[2] = " << ioArray[2].ConvertToChar() << endl;
	
    delete[] ioArray;
	ioArray = NULL ;
    delete[] iArray;
    iArray = NULL ;

}

