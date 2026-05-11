// COPYRIGHT Dassault Systemes 2004
//==========================================================================
//
//	Abstract: This sample shows how to retrieve root files in one directory and identify
//           all their associated files.
//            
//
//  Steps :
//    1.   Check the argument
//    2.   Opens the session
//    3.   Identify roots in the given directory
//    4.   Define consistent set of items for each root
//    5.   Deletes the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAxPDMRetrieveConsistentSet DirectoryPath  
//
//          
// Return code :
//   0 successful execution 
//   1 otherwise
//
//
//===================================================================

// System Framework 
#include "CATError.h"

// ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session

// CATxPDMInterface Framework
#include "CATxPDMFileServices.h"

// C++ Standard Library
#include <iostream.h>  


//-----------------------------------------------------------------------------
int main(int iArgc, char *argv[])        
{
   //---------------------
   //1- Checks arguments
   //---------------------

   CATUnicodeString directory  ;
   CATBoolean RecursiveScan = FALSE ;

   if ((3 != iArgc) && ( 2 != iArgc) )
   {
     cout << endl;
     cout << "CAAxPDMRetrieveConsistentSet DirectoryPath [-r]"<< endl;
     cout << "with : DirectoryPath : a directory path"<< endl;
     cout <<"        -r: recursive scan, by default not recursive"<<endl;
     cout << endl;
     return 1;
   }

   if ( iArgc == 3 )
   {
       CATUnicodeString opt1 = argv[1] ;
       CATUnicodeString opt2 = argv[2] ;
       if ( opt1 == "-r" )
       {
           directory  = argv[2] ;
           RecursiveScan = TRUE ;
       }else if (opt2 == "-r" )
       {
          directory  = argv[1] ;
          RecursiveScan = TRUE ;
       }else
       {
          cout << endl;
          cout << "CAAxPDMRetrieveConsistentSet DirectoryPath [-r]"<< endl;
          cout << "with : DirectoryPath : a directory path"<< endl;
          cout <<"        -r: recursive scan, by default not recursive"<<endl;
          cout << endl;
          return 1;
       }
   }else
   {
      directory  = argv[1] ;
   }


   cout << "The CAAxPDMRetrieveConsistentSet main program begins ...."<< endl << endl;

  
   
   //------------------------------------------------------------------
   //2 - Creates Session
   //------------------------------------------------------------------
   //
   HRESULT rc=S_OK;
   char * pSessionName = "CAA_Sample_Session";
   CATSession *pSession = NULL;
   rc = ::Create_Session(pSessionName,pSession);
   if (FAILED(rc) )
      return 2;
   cout <<" A session is created" << endl;

   //------------------------------------------------------
   //3- Identify roots in the given directory
   //------------------------------------------------------
   cout << " Identifying roots in directory : " << directory.ConvertToChar() << endl;
   if ( RecursiveScan == TRUE )
   {
      cout <<" Recursive way" << endl;
   }else
   {
      cout <<" Not Recursive way" << endl;
   }

   CATListOfCATUnicodeString iListOfDirectory;
   CATListValCATIxPDMItem_var oListOfRootItem;
   iListOfDirectory.Append(directory);
    
   HRESULT hr = CATxPDMFileServices::SearchRootItems(iListOfDirectory,RecursiveScan,oListOfRootItem);
   
   if (FAILED(hr))
   {
       
      CATError * pError = CATError::CATGetLastError(hr);
      if ( NULL != pError )
      {
         CATUnicodeString ErrorMessage = pError->GetNLSMessage() ;
         cout <<"ERROR: "<< ErrorMessage.ConvertToChar()<<endl;
      }
      //Always deleting session before exiting
      Delete_Session(pSessionName);
      return 1;
   }
   cout << " There are " << oListOfRootItem.Size() << " root(s) in this directory" << endl << endl;

   //------------------------------------------------------
   //4- Define consistent set of items for each root
   //------------------------------------------------------
   int size = oListOfRootItem.Size();
   CATUnicodeString FileName;
   for (int i=1;i<=size;i++)
   {
      CATIxPDMItem_var spCurrentRootItem  =  oListOfRootItem[i];
      if (!!spCurrentRootItem)
      {
         spCurrentRootItem ->GetDocFileName(FileName);
         cout << "  " << i << " " << FileName.ConvertToChar() << endl;

         CATListValCATIxPDMItem_var oListOfPointedItem;
         CATListValCATIxPDMItem_var oListOfMissingItem;
         if (SUCCEEDED(CATxPDMFileServices::GetConsistentSetOfItems(spCurrentRootItem,oListOfPointedItem,oListOfMissingItem)))
         {
            int sizeListOfPointedItem =oListOfPointedItem.Size();
            int sizeListOfMissingItem =oListOfMissingItem.Size();
            cout << "      Number of items in consistent set:" << sizeListOfPointedItem+sizeListOfMissingItem << endl;

            if (sizeListOfPointedItem)
            {
               cout << "      -Found items:" << sizeListOfPointedItem << endl;
               for (int j=1;j<=sizeListOfPointedItem;j++)
               {
                  CATIxPDMItem_var spCurrentPointedItem = oListOfPointedItem[j];
                  if (!!spCurrentPointedItem)
                  {
                     spCurrentPointedItem->GetDocFileName(FileName);
                     cout << "       " << j << "  " <<FileName.ConvertToChar() << endl<<flush;
                  }
               }
            }

            if (sizeListOfMissingItem)
            {
               cout << "      -Missing items:" << sizeListOfMissingItem << endl;
               for (int j=1;j<=sizeListOfMissingItem;j++)
               {
                  CATIxPDMItem_var spCurrentMissingItem = oListOfMissingItem[j];
                  if (!!spCurrentMissingItem)
                  {
                     spCurrentMissingItem->GetDocFileName(FileName);
                     cout << "       " << j << "  " <<FileName.ConvertToChar() << endl<<flush;
                  }
               }
            }

         }
         else
         {
            cout << "      Impossible to compute Consitent Set of Items for this root" << endl;
         }
         cout << endl;
      }
   }

   //-------------------
   //5- Deletes session
   //-------------------
   Delete_Session(pSessionName);
   cout<<" The session is deleted"<< endl << endl;
   
   cout <<"The CAAxPDMRetrieveConsistentSet main program is ended."<< endl << endl;
   return 0 ;   
}
