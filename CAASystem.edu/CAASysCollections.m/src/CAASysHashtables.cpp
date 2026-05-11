// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAASysPoint2D.h"
#include <iostream.h>        

// Loval Framework
#include  "CAASysHashTableOfCAASysPoint2D.h"   // To manage the Hash table od CAASysPoint2D

// Local Framework
#include <CAASysPrintUtilities.h>

/*
 * Function which creates and uses hashtables of CAASysPoint2Ds. 
 * In order to be able to put an element in a hashtable, 
 * a hashing function and a comparison function for the
 * element must be provided. These functions are defined in the 
 * CAASysPoint2D class.
 */

void CAAHashtablesSample() 
{
	cout << "==========================================" << endl;
	cout << "== Create an empty hashtable            ==" << endl;
	cout << "==========================================" << endl;

	// The pointer to the hashing and a comparison functions
	// must be passed to the constructor.
	CATHTAB(CAASysPoint2D) hashtable(&CAASysPoint2D::Hash, &CAASysPoint2D::Compare);
	
    cout << "hashtable = ";
	printHashtable(hashtable);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "==   Add a few elements to the hashtable.   ==" << endl;
	cout << "==========================================" << endl;
	
    CAASysPoint2D pt1(1.0f, 2.0f);
	CAASysPoint2D pt2(-4.0f, 3.0f);
	CAASysPoint2D pt3(6.0, 7.0f);
	hashtable.Insert( &pt1 );
	hashtable.Insert( &pt2 );
	hashtable.Insert( &pt3 );
	
    cout << "hashtable = ";
	printHashtable(hashtable);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== Count the elements of the hashtable. ==" << endl;
	cout << "==========================================" << endl;
	
    cout << "hashtable.Size() = " << hashtable.Size() << endl;

	cout << "==========================================" << endl;
	cout << "== CATHTABs have no duplicate elements. ==" << endl;
	cout << "==========================================" << endl;
	
    hashtable.Insert( &pt1 );
	cout << "hashtable = ";
	printHashtable(hashtable);
    cout << endl;
	
    cout << "==========================================" << endl;
	cout << "== CATHTABs are not ordered.            ==" << endl;
	cout << "==========================================" << endl;
	
    CAASysPoint2D pt4(7.0, 8.0f);
	hashtable.Insert( &pt4 );
	cout << "hashtable = ";
	printHashtable(hashtable);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== Remove an element from the hashtable.==" << endl;
	cout << "==========================================" << endl;
	
    hashtable.Remove( &pt1 );
	cout << "hashtable = ";
	printHashtable(hashtable);
	cout << endl;

	cout << "==========================================" << endl;
	cout << "== Retrieve the bucket and position     ==" << endl;
	cout << "== of a given element in the hashtable. ==" << endl;
	cout << "==========================================" << endl;
	
    int	oBucket = 0 ;
	int	oPosition = 0 ;
	hashtable.LocatePosition( &pt3, oBucket, oPosition );
	cout << "Bucket:" << oBucket << endl;
	cout << "Position:" << oPosition << endl;

	cout << "==========================================" << endl;
	cout << "== Access an element by its bucket and  ==" << endl;
	cout << "== position.                            ==" << endl;
	cout << "==========================================" << endl;
	
    CAASysPoint2D *pt5 = NULL;
	pt5 = hashtable.Retrieve(oBucket, oPosition );
	if ((pt5 != NULL) && (pt3 == *pt5)) {
		cout << "{ " << pt5->GetX() << " ; " << pt5->GetY() << " }" << endl;
	} else {
		cout << "Retrieve fails." << endl;
	}

	cout << "==========================================" << endl;
	cout << "== Retrieve the first element of the    ==" << endl;
	cout << "== hashtable which has a give hash      ==" << endl;
	cout << "== value.                               ==" << endl;
	cout << "==========================================" << endl;
	
    CAASysPoint2D *pt6 = NULL;
	pt6 = hashtable.KeyLocate(CAASysPoint2D::Hash( &pt3));
	if (pt6 != NULL) {
		cout << "{ " << pt6->GetX() << " ; " << pt6->GetY() << " }" << endl;
	} else {
		cout << "KeyLocate fails." << endl;
	}
}


