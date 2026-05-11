// COPYRIGHT DASSAULT SYSTEMES 2003

// Local framework
#include "CAAAfrMRURep.h"
#include "CAAAfrGetMRUManager.h"
#include "CAAIAfrMRUManagement.h"

// ApplicationFrame framework
#include <CATAfrCommandHeaderServices.h>

// Dialog framework
#include "CATDialog.h"
#include "CATDlgPushItem.h"

// System framework
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

// Standard library
#include "iostream.h"

//----------------------------------------------------------------------------

CAAAfrMRURep::CAAAfrMRURep(const CATDialog * iParent,CATString & iCommandName): 
                CATAfrCommandHeaderRep(iParent,iCommandName), 
               _pIAfrMRUManagement(NULL)
{
   cout <<" CAAAfrMRURep::CAAAfrMRURep"  << endl;
   
   // Initializes the dialog objects
   for ( int i = 0 ; i < MRU_MAX_SIZE ; i++ )
   {
      _pItemList[i] = NULL ;
   }

   // Retrieves the interface which manages the contents of the MRU manager 
   HRESULT rc = ::CAAAfrGetMRUManager(IID_CAAIAfrMRUManagement, (void**)&_pIAfrMRUManagement);

   
   if ( SUCCEEDED(rc) )
   {
      ::AddCallback(this,
               _pIAfrMRUManagement,
	           "CAAAfrMRUManagerNotification",
	            (CATSubscriberMethod)&CAAAfrMRURep::ModifiedCB,
	            NULL);
   }
  
}

//----------------------------------------------------------------------------

CAAAfrMRURep::~CAAAfrMRURep()
{
    cout <<" CAAAfrMRURep::~CAAAfrMRURep" << endl;

   if ( NULL != _pIAfrMRUManagement )
   {
       ::RemoveSubscriberCallbacks(this, _pIAfrMRUManagement);
       _pIAfrMRUManagement->Release();
       _pIAfrMRUManagement = NULL ;

   }

   for ( int i=0 ; i < MRU_MAX_SIZE ; i++)
   {  
       if ( NULL != _pItemList[i] )
       {
           _pItemList[i]->RequestDelayedDestruction();
           _pItemList[i] = NULL ;
       }
   }
}

//----------------------------------------------------------------------------

HRESULT  CAAAfrMRURep::Build()
{
   cout <<" CAAAfrMRURep::Build" << endl;

   ModifyListItem() ;

   return S_OK ;
}

//----------------------------------------------------------------------------

HRESULT CAAAfrMRURep::ModifyListItem()
{
  cout <<" CAAAfrMRURep::ModifyListItem"  << endl;

  const CATDialog * pParent = NULL ;
  GetDialogParent(&pParent);

  if ( (NULL != _pIAfrMRUManagement ) && (NULL != pParent) )
  {
      // Retrieves the list of element
      CATListOfCATUnicodeString List ;
      _pIAfrMRUManagement->GetElementList(List);

      int SizeList = List.Size();

      if ( SizeList > MRU_MAX_SIZE ) 
      {
         SizeList = MRU_MAX_SIZE ;
      }

      for ( int i= 0 ; i < SizeList ; i++ )
      {
         CATUnicodeString num;
         num.BuildFromNum(i+1);

         // Builds the dialog object if necessary
         if ( _pItemList[i] == NULL )
         { 

            CATUnicodeString ItemName("MRUItem_");
            ItemName.Append(num) ;
             
            _pItemList[i] = new CATDlgPushItem((CATDialog *)pParent,
                                                ItemName.ConvertToChar());
              
            AddAnalyseNotificationCB(_pItemList[i],
                                     _pItemList[i]->GetMenuIActivateNotification(),
                                    (CATCommandMethod)&CAAAfrMRURep::SelectCB,
                                    (CATCommandClientData) CATINT32ToPtr(i));

            // Mandatory to receive the notification
            _pItemList[i]->SetFather(this);
         }

         // Modifies the title of the dialog object
         num.Append(" ");
         num.Append(List[i+1]);
         _pItemList[i]->SetTitle(num);
         
      }    
  }

  cout <<" fin de ModifyListItem" << endl;

  return S_OK ;
}

//----------------------------------------------------------------------------

void CAAAfrMRURep::SelectCB(CATCommand      * iPublishingCommand, 
                            CATNotification * iNotification,
			                CATCommandClientData iData)
{
  cout <<" CAAAfrMRURep::SelectCB" << CATPtrToINT32(iData) << endl;

  // The indice of the selected element
  int SelElement = CATPtrToINT32(iData) + 1;
  
  // Retrieves the name of the selected element
  if ( NULL != _pIAfrMRUManagement )
  {    
         // The MRU manager must be advised of this selection.
         // This instruction must be done before to launch the command
         // because the command launched by CAAAfrMRUSelElementHdr
         // displays the first element of the list kept by the MRU manager
         //
         HRESULT rc = _pIAfrMRUManagement->SelectElement(SelElement);

         if ( SUCCEEDED(rc) )
         {
            // Launches the command
            CATCommand * pCmd = NULL ;
            ::CATAfrStartCommand("CAAAfrMRUSelElementHdr",pCmd);
         }
  }

}

//----------------------------------------------------------------------------

void CAAAfrMRURep::ModifiedCB(CATCallbackEvent, 
                              void *, 
                              CATNotification * iNotification,
			                        CATSubscriberData, 
                              CATCallback)
{
   cout <<" CAAAfrMRURep::ModifiedCB"  << endl;

   ModifyListItem();
}
