// COPYRIGHT Dassault Systemes 2004
//==========================================================================
//
//	Abstract: This sample shows how to read,  
//                  - The type of the document independantly of its file extension,
//                  - The last save path 
//                  - The last save version 
//           
//            without loading document,
//
//
//  Steps :
//    1.   Check the argument
//    2.   Opens the session
//    3.   Retrieve CATIpIxPDMItem from file
//    4.   Read information from CATIpIxPDMItem
//    5.   Deletes the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAxPDMCheckDocType FilePath  
//
//   with     FilePath the file path 
//
//          
// Return code :
//   0 successful execution 
//   1 otherwise
//
// 
//===================================================================

// System FW
#include "CATError.h"

// ObjectModelerBase FW
#include "CATSessionServices.h"          // Create_Session and Delete_Session

// CATxPDMInterfaces Fw
#include "CATxPDMFileServices.h"

// C++ Standard Library
#include <iostream.h>  


//-----------------------------------------------------------------------------
int main(int iArgc, char *argv[])        
{
   //---------------------
   //1- Checks arguments
   //---------------------
   if (2 != iArgc) 
   {
      cout << endl;
      cout << "Usage: CAAxPDMCheckDocType FilePath"<< endl;
      return 1;
   }
   cout << "The CAAxPDMCheckDocType main program begins ...."<< endl << endl;

   CATUnicodeString filename  = argv[1] ;
   
   //------------------------------------------------------------------
   //2 - Creates Session
   //------------------------------------------------------------------
   
   //A session should always be created before using CATxPDM services.
   HRESULT rc=S_OK;
   char * pSessionName = "CAA_Sample_Session";
   CATSession *pSession = NULL;
   rc = ::Create_Session(pSessionName,pSession);
   if (FAILED(rc) )
      return 1;
   cout <<" A session is created" << endl;

   //------------------------------------------------------
   //3- Retrieve CATIpIxPDMItem from file
   //------------------------------------------------------

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
   //4- Read information from CATIpIxPDMItem
   //------------------------------------------------------
   CATUnicodeString LocalDocType;
   if (!!pIxPDMItem)
   {
      //Read Doc Type
      if (SUCCEEDED(pIxPDMItem->GetItemType(LocalDocType)))
      {
         cout << "     Type:" << LocalDocType.ConvertToChar() << endl;
         if (LocalDocType=="NotAV5File")
         {
            cout << "  This file has a V5 extension but is not a V5 file" << endl;
         }
      }

      //Read Last Save Path
      CATUnicodeString SavePath;
      if (SUCCEEDED(pIxPDMItem->GetLastSavePath(SavePath)))
         cout << "     Save Path:" << SavePath.ConvertToChar() << endl;

      //Read Last Save Version
      CATUnicodeString SaveVersion;
      if (SUCCEEDED(pIxPDMItem->GetLastSaveVersion(SaveVersion)))
         cout << "     Version:" << SaveVersion.ConvertToChar() << endl;

	  // Generate the preview image
      CATUnicodeString PathPreviewImage;
      CATUnicodeString  FormatPreviewImage="jpg" ;
      if (SUCCEEDED(pIxPDMItem->GeneratePreview(FormatPreviewImage, PathPreviewImage)))
         cout << "     Path Preview image (jpg):" << PathPreviewImage.ConvertToChar() << endl;

   }
   
   //-------------------
   //5- Deletes session
   //-------------------
   rc = ::Delete_Session(pSessionName);
   if (FAILED(rc) )
      return 1;
   cout<<" The session is deleted"<< endl << endl;
   
   cout <<"The CAAxPDMCheckDocType main program is ended."<< endl << endl;

   return 0 ;  

}
