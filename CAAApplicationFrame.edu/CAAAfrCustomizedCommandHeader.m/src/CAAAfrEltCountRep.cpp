// COPYRIGHT DASSAULT SYSTEMES 2003

// Local framework
#include "CAAAfrEltCountRep.h"
#include "CAAISysCollection.h"
#include "CAAISysPoint.h"
#include "CAAISysLine.h"
#include "CAAISysAccess.h"  //To get the container of each object   

// ApplicationFrame framework
#include "CATFrmEditor.h"

// Visualization Framework
#include <CATPathElement.h>

// Dialog framework
#include "CATDialog.h"
#include "CATDlgEditor.h"

// System framework
#include "CATString.h"
#include "CATUnicodeString.h"

#include "iostream.h"
//----------------------------------------------------------------------------

CAAAfrEltCountRep::CAAAfrEltCountRep(const CATDialog * iParent,CATString & iCommandName): 
                 CATAfrCommandHeaderRep(iParent,iCommandName),
                 _piSysCollection(NULL),_pEdtPoint(NULL),_pEdtLine(NULL)
{
   cout <<" CAAAfrEltCountRep::CAAAfrEltCountRep" << iCommandName.ConvertToChar() << endl;

   // Retrieve the container of the CAAGeometry Model
   CATFrmEditor * pEditor   = CATFrmEditor::GetCurrentEditor();
   if ( NULL != pEditor )
   {
       // Retrieves the root object of the CAAGeometry Model
       CATPathElement path = pEditor->GetUIActiveObject();
       if ( 0 != path.GetSize() ) 
       {
          CATBaseUnknown * pUIActiveObject= NULL ;
          pUIActiveObject = path[path.GetSize()-1];

          if ( NULL != pUIActiveObject )
          {
             CAAISysAccess * piSysAccess = NULL;                
             HRESULT rc = pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
             if (SUCCEEDED(rc))
             {
                CATBaseUnknown * pContainer = NULL ;
                piSysAccess->GetContainer(&pContainer) ;

                piSysAccess-> Release();
                piSysAccess= NULL ;

                if ( NULL != pContainer)
                {               
                   rc = pContainer->QueryInterface(IID_CAAISysCollection, (void**)&_piSysCollection);

                   pContainer -> Release();
                   pContainer= NULL ;
                }
             }
          }
       }
   }

   // Callback to be advised when someone
   // add / delete element into the CAAGeometry 
   // data model
   //
   if ( NULL != _piSysCollection )
   {
      ::AddCallback(this,
               _piSysCollection,
	           "CAASysCollectionModifNotif",
	            (CATSubscriberMethod)&CAAAfrEltCountRep::ModifiedCB,
	            NULL);
   }
}

//----------------------------------------------------------------------------

CAAAfrEltCountRep::~CAAAfrEltCountRep()
{
  cout <<" CAAAfrEltCountRep::~CAAAfrEltCountRep" <<  endl;

  if ( NULL != _piSysCollection )
  {
    // Callback set in the constructor
    ::RemoveSubscriberCallbacks(this, _piSysCollection);

    _piSysCollection->Release();
    _piSysCollection = NULL ;
  }

  const CATDialog * pParent = NULL ;
  GetDialogParent(&pParent);
  if ( NULL != pParent )
  {
    if (((CATDialog *)pParent)->GetChildCount() > 0)
    {
      if ( NULL != _pEdtPoint )
      {
         _pEdtPoint->RequestDelayedDestruction();
         _pEdtPoint = NULL ;
      }

      if ( NULL != _pEdtLine )
      {
         _pEdtLine->RequestDelayedDestruction();
         _pEdtLine = NULL ;
      }
    }
  }
}

//----------------------------------------------------------------------------

HRESULT  CAAAfrEltCountRep::Build()
{
   cout <<" CAAAfrEltCountRep::Build" << endl;

   // Creation of the dialog object
   const CATDialog * pParent = NULL ;
   GetDialogParent(&pParent);

   _pEdtPoint = new CATDlgEditor((CATDialog *)pParent, "CAAAfrEdtPoint", CATDlgEdtReadOnly);
   _pEdtLine  = new CATDlgEditor((CATDialog *)pParent, "CAAAfrEdtLine", CATDlgEdtReadOnly);
   
   // Sets the value in the editors
   ValuateEditors();

   return S_OK ;
}


//----------------------------------------------------------------------------

void CAAAfrEltCountRep::ModifiedCB(CATCallbackEvent, 
                              void *, 
                              CATNotification *iNotification,
                              CATSubscriberData,
                              CATCallback)
{
   cout <<" CAAAfrEltCountRep::ModifiedCB"  << endl;

   ValuateEditors();
}

//----------------------------------------------------------------------------

HRESULT CAAAfrEltCountRep::ValuateEditors()
{
    cout <<" CAAAfrEltCountRep::ValuateEditors()" << endl; 
    HRESULT rc = S_OK ;

    if ( NULL !=  _piSysCollection )
    {
       int nbeltcont = 0 ;
       _piSysCollection->GetNumberOfObjects(&nbeltcont);
   
       int NbPoint = 0 ;
       int NbLine  = 0 ;

       for (int i=1 ; i <=  nbeltcont ; i++)
       { 
          CATBaseUnknown * pObject = NULL ;
          rc = _piSysCollection->GetObject(i,&pObject);
          if (SUCCEEDED(rc))
          {
              CAAISysPoint * piSysPoint  = NULL;                
              rc = pObject ->QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);
              if (SUCCEEDED(rc))
              {
                 // it's a point
                 NbPoint ++ ;
                 piSysPoint -> Release();
                 piSysPoint = NULL ;
              } 

              CAAISysLine * piSysLine  = NULL;                
              rc = pObject ->QueryInterface(IID_CAAISysLine, (void**)&piSysLine);
              if (SUCCEEDED(rc))
              {
                    // it's a line
                    NbLine ++ ;
                    piSysLine -> Release();
                    piSysLine= NULL ;
              }

              pObject->Release();
              pObject = NULL ;
          }
       }

       CATUnicodeString stNbPoint ;
       stNbPoint.BuildFromNum(NbPoint) ;
       CATUnicodeString stNbLine ;
       stNbLine.BuildFromNum(NbLine) ;

       _pEdtPoint->SetText(stNbPoint);
       _pEdtLine ->SetText(stNbLine);
    
    }

   return rc ;
}
