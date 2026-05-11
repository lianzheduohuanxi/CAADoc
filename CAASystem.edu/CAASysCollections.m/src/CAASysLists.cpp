
// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//    
//  Illustrates:
//     1 - Creation and use of lists of basic types
//     2 - Creation and use of lists of pointers
//     3 - Creation and use of lists of values
//    
//=============================================================================

// C++ Standard library
#include <iostream.h>

// Local Framework
#include "CAASysPoint2D.h"		     // Class used for the lists of pointers and values
#include "CAAListPtrOfCAASysPoint2D.h" // To manage lists of pointers of CAASysPoint2D
#include "CAAListValOfCAASysPoint2D.h" // To manage lists of values   of CAASysPoint2D

// System Framework
#include  "CATListOfInt.h"	      // To manage lists of int


void CAAListsSample() 
{
  //-----------------------------------------------------------------
  // 1- Creation and use of lists of basic types
  //-----------------------------------------------------------------

	cout << "====================================================================" << endl;
	cout << "== Construct an empty collection of int, then append some items   ==" << endl;
	cout << "====================================================================" << endl;
	
    CATListOfInt listOfInt;
	int	i1 = 5;

	listOfInt.Append ( 0 );
	listOfInt.Append ( i1 );
	listOfInt.Append ( 6 );
	listOfInt.Append ( 77 );
	listOfInt.Append ( 888 );
	listOfInt.Append ( 9999 );
	listOfInt.Append ( 0 );
	listOfInt.Append ( 0 );
	listOfInt.Append ( 0 );	
	
	cout << "================================================" << endl;
	cout << "==  Replace items anywhere in the collection  ==" << endl;
	cout << "================================================" << endl;

	// Caution : the first item has an index equal to 1.
	listOfInt[5] = 92380; // Instead of 888
	listOfInt[7] = listOfInt[2] ;

	cout << "===========================================" << endl;
	cout << "==  Locate some items in the collection  ==" << endl;
	cout << "===========================================" << endl;

	cout << "Locate (9999)  == "	<< listOfInt.Locate (9999) << endl;
	cout << "Locate (0, 3)  == "    << listOfInt.Locate(0, 3) << endl;

	cout << "====================================" << endl;
	cout << "==  QuickSort  of the collection  ==" << endl;
	cout << "====================================" << endl;
	
    listOfInt.QuickSort();

	cout << "==========================================" << endl;
	cout << "==  RemoveDuplicates of the collection  ==" << endl;
	cout << "==========================================" << endl;
	
    listOfInt.RemoveDuplicates();

	cout << "==========================" << endl;
	cout << "==  Exchange positions  ==" << endl;
	cout << "==========================" << endl;
	
    listOfInt.Swap(1, 2);

	cout << "================================================" << endl;
	cout << "==  Copy items of the collection in an array  ==" << endl;
	cout << "================================================" << endl;

	// Create a new array of int from the list.
	int*	aArray = new int[listOfInt.Size()];
	listOfInt.FillArray(aArray , listOfInt.Size());

	// Create a new CATListOfInt from the array.
	CATListOfInt*	plistOfInt = new CATListOfInt(aArray, listOfInt.Size());
	
	// Clean up
	delete [] aArray ;
	
	cout << "==========================================" << endl;
	cout << "==  Remove/Insert items in a collection ==" << endl;
	cout << "==========================================" << endl;
	
        plistOfInt->RemovePosition(1);
	plistOfInt->RemovePosition(3);
	plistOfInt->InsertAt(2, 1313);
	plistOfInt->InsertAt(5, 12345);

	cout << "===============================" << endl;
	cout << "==  Intersecting collections ==" << endl;
	cout << "===============================" << endl;
	
        CATListOfInt	listOfIntInter;
	CATListOfInt::Intersection (*plistOfInt, listOfInt, listOfIntInter);

	// Clean up
        delete	plistOfInt ;

  //-----------------------------------------------------------------
  // 2- Creation and use of lists of pointers
  //-----------------------------------------------------------------

	cout << "=====================================================" << endl;
	cout << "==  Create a CATListP<CAASysPoint2D>  (named lpCAASysPoint2D)  ==" << endl;
	cout << "=====================================================" << endl;
	
        CATLISTP(CAASysPoint2D)	lpCAASysPoint2D ;
	
	cout << "======================================" << endl;
	cout << "==  Create several CAASysPoint2D objects  ==" << endl;
	cout << "==  and add them to lpCAASysPoint2D       ==" << endl;
	cout << "======================================" << endl;
	
        CAASysPoint2D p0(0, 1);
	CAASysPoint2D p1(1, 2);
	CAASysPoint2D p2(2, 3);
	CAASysPoint2D p3(3, 4);
	CAASysPoint2D p4(4, 5);
	lpCAASysPoint2D.Append(&p0);
	lpCAASysPoint2D.Append(&p1);
	lpCAASysPoint2D.Append(&p2);
	lpCAASysPoint2D.Append(&p3);
	lpCAASysPoint2D.Append(&p4);

	cout << "=======================================" << endl;
	cout << "==  Locate a pointer from lpCAASysPoint2D  ==" << endl;
	cout << "=======================================" << endl;
	
    int indexP2 = lpCAASysPoint2D.Locate(&p2);
	cout << "L1.Locate(&p2) == " << indexP2 << endl;
	
	// Get the value of the point.
	float xP2 = lpCAASysPoint2D[indexP2]->GetX();
	float yP2 = lpCAASysPoint2D[indexP2]->GetY();
	cout << "Value of lpCAASysPoint2D.Locate(&p2) == (" << xP2 << ", " << yP2 << ")" << endl;

	cout << "===========================================" << endl;
	cout << "==  Remove some pointers from lpCAASysPoint2D  ==" << endl;
	cout << "===========================================" << endl;
    
    lpCAASysPoint2D.RemoveValue(&p1);
    lpCAASysPoint2D.RemoveValue(&p3);

  //-----------------------------------------------------------------
  // 3- Creation and use of lists of values
  //-----------------------------------------------------------------

	cout << "=====================================================" << endl;
	cout << "==  Create a CATListV<CAASysPoint2D>  (named lpCAASysPoint2D)  ==" << endl;
	cout << "=====================================================" << endl;
	
    CATLISTV(CAASysPoint2D)	lvCAASysPoint2D ;
	
	cout << "======================================" << endl;
	cout << "==  Create several CAASysPoint2D objects  ==" << endl;
	cout << "==  and add them to lvCAASysPoint2D       ==" << endl;
	cout << "======================================" << endl;
	
    CAASysPoint2D value0(0, 1);
	CAASysPoint2D value1(1, 2);
	CAASysPoint2D value2(2, 3);
	CAASysPoint2D value3(3, 4);
	CAASysPoint2D value4(4, 5);
	lvCAASysPoint2D.Append(value0);
	lvCAASysPoint2D.Append(value1);
	lvCAASysPoint2D.Append(value2);
	lvCAASysPoint2D.Append(value3);
	lvCAASysPoint2D.Append(value4);

	cout << "=======================================" << endl;
	cout << "==  Locate a value from lvCAASysPoint2D  ==" << endl;
	cout << "=======================================" << endl;
	
    int indexValue3 = lvCAASysPoint2D.Locate(value3);
	cout << "L1.Locate(value3) == " << indexValue3 << endl;
	
	// Get the value of the point.
	float xValue3 = lvCAASysPoint2D[indexValue3].GetX();
	float yValue3 = lvCAASysPoint2D[indexValue3].GetY();
	cout << "Value of lpCAASysPoint2D.Locate(value3) == (" << xValue3 << ", " << yValue3 << ")" << endl;

	cout << "===========================================" << endl;
	cout << "==  Remove some values from lpCAASysPoint2D  ==" << endl;
	cout << "===========================================" << endl;
    
    lvCAASysPoint2D.RemoveValue(value1);
    lvCAASysPoint2D.RemoveValue(value3);

}
