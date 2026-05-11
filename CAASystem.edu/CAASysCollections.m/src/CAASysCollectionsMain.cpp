
// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract:
//  ---------
//
//  Batch program which creates and uses different types of collections.
//    
//  Illustrates:
//     Creation and use of lists of basic types
//     Creation and use of lists of pointers
//     Creation and use of lists of values
//     Creation and use of sets.
//     Creation and use of hashtables.
//    
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//     CAASysCollections
//
//=============================================================================

// C++ Standard library
#include <iostream.h>

// Prototype declaration.
void CAAListsSample();          // Defined in CAASysLists.cpp
void CAASetsSample();           // Defined in CAASysSets.cpp
void CAAHashtablesSample();     // Defined in CAASysHashTables.cpp

int main()
{
   cout << "=================================================================" << endl;
   cout << "==                CAASysCollections sample                     ==" << endl;
   cout << "=================================================================" << endl;

   // -------------------------------------------------------
   // Creation and use of lists (basic types,pointers,values)
   // -------------------------------------------------------

   CAAListsSample();

   // -------------------------------------------------------
   // Creation and use of sets
   // -------------------------------------------------------

   CAASetsSample();

   // -------------------------------------------------------
   // Creation and use of hash tables
   // -------------------------------------------------------

   CAAHashtablesSample();

   cout << endl;
   cout << "===============================" << endl;
   cout << "==        End of sample      ==" << endl;
   cout << "===============================" << endl;
   cout << endl;

   return 0;
}
