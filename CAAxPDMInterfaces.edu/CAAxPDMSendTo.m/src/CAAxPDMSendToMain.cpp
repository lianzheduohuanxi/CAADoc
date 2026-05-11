// COPYRIGHT Dassault Systemes 2005
//==========================================================================
//
//	Abstract: This sample shows how to use the Send To API.
//            
//
//  Steps :
//    1.   Read and Check the argument.
//    2.   Open the session.
//    3.   Retreive the input file items.
//    4.   Compute the cumulated consistent Set of the input file items.
//    5.   Create a SendTo Instance. 
//    6.   Add all input file items. 
//    7.   Rename all pointed items of the consitent set
//    8.   Remove all items which are not CATProduct or CATPart
//    9.   Simulate Send To operation.
//   10.   Run Send To operation.
//   11.   Delete the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAxPDMSendTo TargetDirectory FileName1 [FileName2 FileName3 ...]
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
#include "CATxPDMSessionServices.h"
#include "CATIxPDMItem.h"
#include "CATListOfCATIxPDMItem.h"
#include "CATIxPDMSendToService.h"

// C++ Standard Library
#include <iostream.h>  

#ifdef _WINDOWS_SOURCE
#define SEPARATOR "\\"
#else
#define SEPARATOR "/"
#endif

void PrintError(HRESULT rc)
{
  CATError * pError = CATError::CATGetLastError(rc);
  if ( NULL != pError )
  {
    CATUnicodeString ErrorMessage = pError->GetNLSMessage() ;
    cout <<"ERROR: "<< ErrorMessage.ConvertToChar()<<endl;
  }
}

//-----------------------------------------------------------------------------
int main(int iArgc, char *argv[])        
{
  //---------------------
  //1- Read and Checks arguments
  //---------------------
  //
  CATUnicodeString filename  ;
  if (iArgc<2) 
  {
    cout << endl;
    cout << "CAAxPDMSendTo TargetDir FilePath [FilePath1 FilePath2 ...] "<< endl;
    cout << "with : TargetDIr : The destination directory where the sent files will be copied."<< endl;
    cout << "with : FilePath : a file path"<< endl;
    cout << endl;
    return 1;
  }
  int NbFiles=iArgc-2;
  CATUnicodeString TargetDir=argv[1];
  
  cout << "The CAAxPDMSendTo main program begins ...."<< endl << endl;
  
  //------------------------------------------------------------------
  //2 - Creates Session
  //------------------------------------------------------------------
  //
  HRESULT rc=S_OK;
  char * pSessionName = "CAA_Sample_Session";
  CATSession *pSession = NULL;
  rc = ::Create_Session(pSessionName,pSession);
  if(FAILED(rc)) return 2;
  cout <<" A session is created" << endl;
  
  //------------------------------------------------------
  //3-  Retreive the input file items.
  //------------------------------------------------------
  //
  CATListValCATIxPDMItem_var  ItemList;
  CATUnicodeString FileName;
  int i = 1;
  for(;i<=NbFiles;i++)
  {
    FileName=argv[i+1];
    CATIxPDMItem_var Item=NULL_var;
    cout << " Read all information on file : " << FileName.ConvertToChar() << endl;
    
    rc =  CATxPDMFileServices::GetItemFromFile(FileName,Item);
    if (FAILED(rc))
    {
      PrintError(rc);
      //Always deleting session before exiting
      Delete_Session(pSessionName);
      return 1;
    }
    ItemList.Append(Item);
  }
  
  //------------------------------------------------------
  //4- Compute the cumulated consistent Set of the input file items.
  //------------------------------------------------------
  CATListValCATIxPDMItem_var oListOfPointedItem;
  CATListValCATIxPDMItem_var oListOfMissingItem;
  for(i=1;i<=NbFiles;i++)
  {   
    CATIxPDMItem_var It= ItemList[i];
    if(!!It) It->GetDocFileName(FileName);
    cout << " Compute Consistent set of " <<FileName.ConvertToChar() << endl;
    CATListValCATIxPDMItem_var oLp;
    CATListValCATIxPDMItem_var oLm;
    if (SUCCEEDED(CATxPDMFileServices::GetConsistentSetOfItems(ItemList[i],oLp,oLm)))
    {
      int sizeListOfPointedItem =oLp.Size();
      int sizeListOfMissingItem =oLm.Size();
      cout << "      Number of items in consistent set:" << sizeListOfPointedItem+sizeListOfMissingItem << endl;
      
      if (sizeListOfPointedItem)
      {
        cout << "      -Found items:" << sizeListOfPointedItem << endl;
        for (int j=1;j<=sizeListOfPointedItem;j++)
        {
          CATIxPDMItem_var spCurrentPointedItem = oLp[j];
          if (!!spCurrentPointedItem)
          {
            oListOfPointedItem.Append(spCurrentPointedItem);
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
          CATIxPDMItem_var spCurrentMissingItem = oLm[j];
          if (!!spCurrentMissingItem)
          {
            oListOfMissingItem.Append(spCurrentMissingItem);
            spCurrentMissingItem->GetDocFileName(FileName);
            cout << "       " << j << "  " <<FileName.ConvertToChar() << endl<<flush;
          }
        }
      }  
    }
    else
    {
      //Always deleting session before exiting
      cout << "      Impossible to compute Consitent Set of Items." << endl;
      Delete_Session(pSessionName);
      return 1;   
    }
  }

  //-----------------------------
  //5- Create a Send to Instance
  //-----------------------------
  CATIxPDMSendToService_var SendTo=NULL_var;
  CATUnicodeString Report=TargetDir+SEPARATOR+"CAAxPDMSendToReport.txt";
  rc=CATxPDMFileServices::CreateSendToService(SendTo,TargetDir,FALSE,Report);
  if(FAILED(rc))
  {
    //Always deleting session before exiting
    PrintError(rc);
    Delete_Session(pSessionName);
    return 1;   
  }
  //----------------------------
  //    6.   Add all file items 
  //----------------------------
  for(i=1;i<=NbFiles;i++)
  {
    // This method adds the input items,and recursively adds the pointed items (but not the missing ones)
    rc=SendTo->Add(ItemList[i]);
    if(FAILED(rc))     
    {
      //Always deleting session before exiting
      PrintError(rc);
      Delete_Session(pSessionName);
      return 1;   
    }
  }
  //------------------------------------------------------
  //    7.   Rename all file items of the cumulated consistency set
  //------------------------------------------------------
  int NbPointed=oListOfPointedItem.Size();
  for(i=1;i<=NbPointed;i++)
  {
    CATUnicodeString Num;
    Num.BuildFromNum(i);
    CATUnicodeString NewName="Send_To_CATIA_Document_"+Num;
    rc=SendTo->Rename(oListOfPointedItem[i],NewName);
    if(FAILED(rc))     
    {
      //Always deleting session before exiting
      PrintError(rc);
      Delete_Session(pSessionName);
      return 1;   
    }
  }
  //----------------------------------------------------------------------
  //    8.   Remove all file items which are not CATProduct or CATPart
  //-----------------------------------------------------------------------
  for(i=1;i<=NbPointed;i++)
  {
    CATUnicodeString Type;
    CATIxPDMItem_var PointedIt=oListOfPointedItem[i];
    PointedIt->GetItemType(Type);
    if(Type!="CATPart" && Type!="CATProduct")
    {  
      rc=SendTo->Remove(PointedIt);
      if(FAILED(rc))     
      {
        //Always deleting session before exiting
        PrintError(rc);
        Delete_Session(pSessionName);
        return 1;   
      }
    }
  }
  //----------------------------
  //    9.   Simulate the Send To
  //----------------------------
  CATListOfInt LStatus;
  CATListValCATIxPDMItem_var LInput;
  CATListValCATIxPDMItem_var LOutput;
  
  rc=SendTo->Simulate(LStatus,LInput,LOutput);
  if(FAILED(rc))     
  {
    //Always deleting session before exiting
    PrintError(rc);
    Delete_Session(pSessionName);
    return 1;   
  }
  //
  // Display the simulation result
  //
  int NbSimu=LStatus.Size();
  for(i=1;i<=NbSimu;i++)
  {
    CATIxPDMItem_var It=LInput[i];
    FileName="";
    if(!!It) It->GetDocFileName(FileName);
    if(LStatus[i]==0)
    {
      // Item will be Send to  
      cout<<" Item "<<FileName.ConvertToChar()<<" will be send to :"<<endl;
      It=LOutput[i];
      if(!!It) It->GetDocFileName(FileName);
      cout<<"      "<<FileName.ConvertToChar()<<endl;
    }
    else if(LStatus[i]==-1)
    {
      // Item will be removed
      cout<<" Item "<<FileName.ConvertToChar()<<" has been removed."<<endl;
    }
    else if(LStatus[i]==1)
    {
      // Missing item
      cout<<" Item "<<FileName.ConvertToChar()<<" is missing."<<endl;
    }
  }
  //----------------------------
  //    10.   Run the Send To
  //----------------------------
  SendTo->Run(oListOfMissingItem);
  if(FAILED(rc))     
  {
    //Always deleting session before exiting
    PrintError(rc);
    Delete_Session(pSessionName);
    return 1;   
  } 
  //-------------------
  //    11- Deletes session
  //-------------------
  //
  Delete_Session(pSessionName);
  cout<<" The session is deleted"<< endl << endl;
  
  cout <<"The CAAxPDMSendTo main program is ended."<< endl << endl;

  return 0 ;   
}
