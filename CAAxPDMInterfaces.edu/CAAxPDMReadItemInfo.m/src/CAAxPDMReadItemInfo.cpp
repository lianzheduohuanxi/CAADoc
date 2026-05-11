// COPYRIGHT Dassault Systemes 2005
//==========================================================================
//
//	Abstract: This sample shows how to read all information on one item
//            
//
//  Steps :
//    1.   Check the argument
//    2.   Opens the session
//    3.   Open item
//    4.   Read information recursively
//    5.   Deletes the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAxPDMReadItemInfo FileNameWithPath
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
#include "CATIAlias.h"
// CATxPDMInterface Framework
#include "CATxPDMFileServices.h"
#include "CATxPDMSessionServices.h"
#include "CATIxPDMItem.h"

// C++ Standard Library
#include <iostream.h>  


void Tabul(int tabul)
{
	for (int i=0;i<tabul;++i)
		cout << " ";
}

HRESULT DisplayItemInformation(CATIxPDMItem_var& pIxPDMItem, int tabul)
{
   HRESULT rc=E_FAIL;
   if (!!pIxPDMItem)
   {
      //1. Display Name, Type and Version
      CATUnicodeString ItemName,ItemType,ItemVersion;
      if (SUCCEEDED(pIxPDMItem->GetDocFileName(ItemName)))
      {
         Tabul(tabul-2); cout << "--" << ItemName.ConvertToChar() << endl;
      }
      if (SUCCEEDED(pIxPDMItem->GetItemType(ItemType)))
      {
         Tabul(tabul); cout << "Type       :" << ItemType.ConvertToChar() << endl;
      }
      if (SUCCEEDED(pIxPDMItem->GetLastSaveVersion(ItemVersion)))
      {
         Tabul(tabul); cout << "Version    :" << ItemVersion.ConvertToChar() << endl;
      }

      //2. Load Selected item
      CATIxPDMItem_var hxPDMItem;
      rc = CATxPDMSessionServices::LoadItemInSession(pIxPDMItem,hxPDMItem);
      if (SUCCEEDED(rc) && !!hxPDMItem)
      {
         CATIAlias_var alias = hxPDMItem;
         if (!!alias)
         {
            Tabul(tabul); cout << "DisplayName:" << alias->GetAlias().ConvertToChar() << endl;
         }
         //3. Display Property Values
         CATListOfCATUnicodeString oPropertyList;
         if (SUCCEEDED(hxPDMItem->GetPropertyNames(oPropertyList)))
         {
            Tabul(tabul); cout << "List of properties"<< endl;
            CATUnicodeString propertyvalue;
            int nbprop = oPropertyList.Size();
            for (int i=1;i<=nbprop;i++)
            {
               if (SUCCEEDED(hxPDMItem->GetProperty(oPropertyList[i],propertyvalue)))
               {
                  Tabul(tabul+1); cout << i << " " << oPropertyList[i].ConvertToChar() <<  " = " << propertyvalue.ConvertToChar() << endl;
               }
               else
               {
                  Tabul(tabul+1); cout << i << " " << oPropertyList[i].ConvertToChar() <<  " = Impossible to read value." << endl;
               }
            }
         }

         //4. Launch recursivity on children
         CATListValCATIxPDMItem_var oChildrenList;
         CATLISTP(CATMathTransformation) oChildrenLocation;
         if (SUCCEEDED(hxPDMItem->GetChildrenItems(oChildrenList,oChildrenLocation)))
         {
            int nbchild = oChildrenList.Size();
            if (nbchild)
            {
               Tabul(tabul); cout << "List of children"<< endl;
               for (int i=1;i<=nbchild;i++)
               {
                  CATIxPDMItem_var child = oChildrenList[i]; 
                  Tabul(tabul+1); cout << "Child " << i << endl;
                  DisplayItemInformation(child,tabul+3);
               }
            }
         }
         
         //5. Unload Selected item
         //unload only if it was not loaded before
         if (pIxPDMItem!=hxPDMItem)
            CATxPDMSessionServices::UnLoadItemFromSession(hxPDMItem);
      }
   }
   return rc;
}




//-----------------------------------------------------------------------------
int main(int iArgc, char *argv[])        
{
   //---------------------
   //1- Checks arguments
   //---------------------
   //
   CATUnicodeString filename  ;
   if ( 2 != iArgc) 
   {
     cout << endl;
     cout << "CAAxPDMReadItemInfo FilePath"<< endl;
     cout << "with : FilePath : a file path"<< endl;
     cout << endl;
     return 1;
   }
   filename  = argv[1] ;
   cout << "The CAAxPDMReadItemInfo main program begins ...."<< endl << endl;
   
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
   //3- Retrieve Item on Root File
   //------------------------------------------------------
   //
   cout << " Read all information on file : " << filename.ConvertToChar() << endl;
   CATIxPDMItem_var pIxPDMItem;
   rc = CATxPDMFileServices::GetItemFromFile(filename,pIxPDMItem);
   if (FAILED(rc))
   {
      CATError * pError = CATError::CATGetLastError(rc);
      if ( NULL != pError )
      {
         CATUnicodeString ErrorMessage = pError->GetNLSMessage() ;
         cout <<"ERROR: "<< ErrorMessage.ConvertToChar()<<endl;
      }
      //Always deleting session before exiting
      Delete_Session(pSessionName);
      return 1;
   }

   //------------------------------------------------------
   //4- Display Information
   //------------------------------------------------------
   //
   rc = DisplayItemInformation(pIxPDMItem,3);
   if (FAILED(rc))
   {
      CATError * pError = CATError::CATGetLastError(rc);
      if ( NULL != pError )
      {
         CATUnicodeString ErrorMessage = pError->GetNLSMessage() ;
         cout <<"ERROR: "<< ErrorMessage.ConvertToChar()<<endl;
      }
      //Always deleting session before exiting
      Delete_Session(pSessionName);
      return 1;
   }

   //-------------------
   //5- Deletes session
   //-------------------
   //
   Delete_Session(pSessionName);
   cout<<" The session is deleted"<< endl << endl;
   
   cout <<"The CATxPDMtstCheckDocType main program is ended."<< endl << endl;
   return 0 ;   
}
