// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAADlgModel.h"
#include "CAADlgElement.h"
#include "CAADlgAddNotification.h"
#include "CAADlgRemoveNotification.h"
#include "CAADlgErrorNotification.h"

// System Framework
#include "CATBoolean.h"

// C++ Standard Library 
#include <iostream.h>

// -------------------------

CAADlgModel::CAADlgModel(CATCommand * iFather , char *iName): CATCommand(iFather),
                   _PositionToAdd(0),
                   _pTheLastElementManipulated(NULL)
{   
  // Keep the name of the model
  if ( NULL != iName )
  {
     _pModelName = new char [strlen(iName)+1];
     strcpy(_pModelName,iName);
  }
  else
  {
      _pModelName = new char [13];
      strcpy(_pModelName,"DefaultModel");
  }
  printf("The model, %s, is created.\n", _pModelName );

}

// ------------------------

CAADlgModel::~CAADlgModel() 
{
  printf("The model, %s, is deleted.\n", _pModelName );

  if ( NULL != _pModelName )
  {
     delete [] _pModelName;
     _pModelName = NULL;
  }

  if ( NULL != _pTheLastElementManipulated )
  {
      _pTheLastElementManipulated->Release();
      _pTheLastElementManipulated = NULL;
  }

  for ( int i= 0 ; i < _PositionToAdd ; i++ )
  {
     if ( NULL != _ElementList[i] )
     {
        _ElementList[i]->Release();
        _ElementList[i] = NULL;
     }
  }

  _PositionToAdd = 0;
}

// --------------------------------------

void CAADlgModel::Add(CAADlgElement * iNewElement) 
{
  if ( NULL != iNewElement )
  {
     // Adds the element at the end of the list
     _ElementList[_PositionToAdd] = iNewElement;
     _ElementList[_PositionToAdd]->AddRef();

     _PositionToAdd ++ ;

     if ( NULL != _pTheLastElementManipulated )
     {
      _pTheLastElementManipulated->Release();
     }

     _pTheLastElementManipulated = iNewElement;
     _pTheLastElementManipulated->AddRef();

     printf("The model, %s, adds the %s element.\n", GetModelName(), 
                                      iNewElement->GetElementName());
     
     // Notification used when an element is added to the model
     // No need to delete the notification, it's done automatically
     // because it was instantiated using CATNotificationDeleteOn
     
     CAADlgAddNotification * pAddNotification = new CAADlgAddNotification();
     SendNotification(GetFather(), pAddNotification);
     pAddNotification = NULL;
  }
  else
  {
     printf("The Command Model, %s, refused to add the element.\n", GetModelName());
                                                   
     // The notification can be created just before calling SendNotification
     // No need to delete the notification, it's done automatically
     // because it was instantiated using CATNotificationDeleteOn
     CAADlgErrorNotification * pErrorNotification = new CAADlgErrorNotification();     
     SendNotification(GetFather(), pErrorNotification);
     pErrorNotification = NULL;
  }
}

// -----------------------------------------

void CAADlgModel::Remove(CAADlgElement * iElementToRemove)
{
  int error = 1 ;

  if ( NULL != iElementToRemove )
  {
     // Search for the element in the list
     CATBoolean found (FALSE);
     int        index (0);
     while ( ( FALSE == found ) && ( index < _PositionToAdd) )
     {
        if ( _ElementList[index] == iElementToRemove )
           found = TRUE ;          
        else
           index++ ;
     }

     // Deletion of the element in the list 
     if ( TRUE == found )
     {
        if ( NULL != _pTheLastElementManipulated )
        {
           _pTheLastElementManipulated->Release();
        }

        _pTheLastElementManipulated = iElementToRemove;
        _pTheLastElementManipulated->AddRef();

        _ElementList[index]->Release();
        _ElementList[index] = NULL ;

        printf("The model, %s, removes the element %s.\n", GetModelName(), 
                                        iElementToRemove->GetElementName());
        
        // Notification used when an element is removed from the model
        // No need to delete the notification, it's done automatically
        // because it was instantiated using CATNotificationDeleteOn
        CAADlgRemoveNotification * pRemoveNotification = new CAADlgRemoveNotification();
        SendNotification(GetFather(), pRemoveNotification);
        pRemoveNotification = NULL;

        error = 0;
     }
  }

  if ( 1 == error )
  {
     printf("The model, %s, refused to remove the element.\n",
                                 GetModelName());
                                 

     // The notification can be created just before calling SendNotification
     // No need to delete the notification, it's done automatically
     // because it was instantiated using CATNotificationDeleteOn
     CAADlgErrorNotification * pErrorNotification = new CAADlgErrorNotification();
     SendNotification(GetFather(), pErrorNotification);
     pErrorNotification = NULL ;
  }
}

// -----------------------------------

void *CAADlgModel::SendCommandSpecificObject(const char      *iObjectClassNeeded, 
                                             CATNotification *iReceived) 
{

  void * pObjectToReturn = NULL ;

  if ( NULL != iReceived )
  {
     if ( ( 1 == iReceived->IsAKindOf("CAADlgAddNotification")) || 
          ( 1 == iReceived->IsAKindOf("CAADlgRemoveNotification")) ) 
     {
        if ( 1 == _pTheLastElementManipulated->IsAKindOf(iObjectClassNeeded) )
        {
           pObjectToReturn = _pTheLastElementManipulated ;
           _pTheLastElementManipulated->AddRef();
        }
     } 
  }
  return pObjectToReturn ;
}

//---------------------------------------------------------------------------

char * CAADlgModel::GetModelName() 
{
  return(_pModelName);
}
