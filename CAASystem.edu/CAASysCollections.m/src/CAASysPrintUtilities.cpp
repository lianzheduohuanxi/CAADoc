// COPYRIGHT DASSAULT SYSTEMES 1999

#include <iostream.h>

/*
 * A utility function to print the contents of a set
 * to the standard output
 */
#include <CAASysPrintUtilities.h>
#include <CATString.h>

void printSet(CATSetOfCATString& iSet) 
{
   cout << "[ ";
   for (unsigned int i = 1 ; i <= iSet.Size(); i++ ) 
   {
      if (i > 1) 
      {
         cout << ", ";
      }
      cout << iSet[i].ConvertToChar();
   }
   cout << " ]";
}

/*
 * A utility function to print the contents of a hashtable
 * to the standard output
 */

#include "CATBoolean.h"

void printHashtable(CATHTAB(CAASysPoint2D)& iHashtable) 
{
   cout << "[ ";
   CAASysPoint2D* pt = NULL;
   do 
   {
      CATBoolean first = (pt == NULL);
      pt = iHashtable.Next(pt);
      if ( NULL != pt ) 
      {
         if ( FALSE == first) 
         {
            cout << ", ";
         }
         cout << "{ " << pt->GetX() << " ; " << pt->GetY() << " }";
      }
   } while ( NULL != pt );
   cout << " ]";
}
