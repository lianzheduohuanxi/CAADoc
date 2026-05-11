// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework 
#include "CAAEAfrCollection.h"
#include "CAAISysAccess.h"

// System Framework 
#include "CATCallbackManager.h" // To dispatch notification 
#include "CATErrorDef.h"        // To test the return code

// Visualization Framework 
#include "CATIModelEvents.h"    // 

// ApplicationFrame Framework 
#include "CATListOfCATBaseUnknown.h"

// CAASystem.edu Framework
#include "CAASysCollectionEmptyNotif.h"  // Notification sent by RemoveObject
#include "CAASysCollectionFilledNotif.h" // Notification sent by AddObject    
#include "CAASysCollectionModifNotif.h"  // Notification sent by AddObject/RemoveObject

// C++ Standard Library
#include "iostream.h"

//-----------------------------------------------------------------------------
// To create the TIE Object
#include "TIE_CAAISysCollection.h"
TIE_CAAISysCollection(CAAEAfrCollection);

//
// To declare that the class is a DataExtension of CAASysGeomCont and CAASysSampCont
// 
//
CATBeginImplementClass(CAAEAfrCollection,DataExtension,CATBaseUnknown,CAASysGeomCont);
CATAddClassExtension(CAASysSampCont) ;
CATEndImplementClass(CAAEAfrCollection);

// 
// To declare that CAAEAfrCollection implements CAAISysCollection,  
// insert these following lines in the interface dictionary:
//
//    CAASysSampCont        CAAISysCollection  libCAAAfrGeoModel
//    CAASysGeomCont        CAAISysCollection  libCAAAfrGeoModel
//
//-----------------------------------------------------------------------------

CAAEAfrCollection::CAAEAfrCollection()
{
  cout << "CAAEAfrCollection::CAAEAfrCollection" << endl;

  _pListe = new CATLISTP(CATBaseUnknown);
}

//------------------------------------------------------------------------------

CAAEAfrCollection::~CAAEAfrCollection()
{
  if (NULL != _pListe)
  {
    cout << "CAAEAfrCollection::~CAAEAfrCollection=" << _pListe->Size() << endl;

    for ( int i=1 ; i <= _pListe->Size() ;i++)
    {
      CATBaseUnknown * pListe_i = (*_pListe)[i];
      if ( NULL != pListe_i )
      {
        pListe_i -> Release();
        pListe_i = NULL;
        ((*_pListe)[i])= NULL ;
      }
    }
  }
  
  delete _pListe ;
  _pListe = NULL ;
}


//-------------------------------------------------------------------------------

HRESULT CAAEAfrCollection::GetNumberOfObjects(int * oCount)
{
  cout << "CAAEAfrCollection::GetNumberOfObjects" << endl;
  
  if ((0 == oCount) || (NULL == _pListe)) return E_FAIL;
  
  *oCount = _pListe->Size();
  
  return S_OK;
}

//---------------------------------------------------------------------------------

HRESULT CAAEAfrCollection::GetObject    (int              iRank,
                                         CATBaseUnknown **oObject)
{
  cout << "CAAEAfrCollection::GetObject" << endl;

  if ((NULL == oObject) || (NULL == _pListe)) return E_FAIL;
  
  if ( (iRank < 1 ) || ( iRank > _pListe->Size() ) )
  {
    // Bad iRank value
    return E_FAIL;
  }
  else
  {
    *oObject = (*_pListe)[iRank];    
    if ( NULL != *oObject) 
    {
      // After the GetObject, Release your object
      (*oObject) -> AddRef();
      return S_OK;
    }
    else 
      return E_FAIL;
  }
}

//-----------------------------------------------------------------------------------

HRESULT CAAEAfrCollection::AddObject    (CATBaseUnknown * iObject)
{
  cout << "CAAEAfrCollection::AddObject" << endl;

  if ( (NULL == iObject) || (NULL == _pListe) )
     return E_FAIL ;

  //--------------------------------
  // Sets a link for the display 
  //--------------------------------
  if ( 0 != _pListe->Size() )
  {
    // There is at least one object. 
    // The first element of the container is the UI activable object.
    // The link is between the UI active object and it.
    //  
    CATIModelEvents * piModelEvent = NULL;                
    CATBaseUnknown * pListe_1 = (*_pListe)[1];
    HRESULT rc = E_FAIL;
    if (pListe_1) rc = pListe_1 ->QueryInterface(IID_CATIModelEvents, 
                                               (void**)&piModelEvent);
    if (SUCCEEDED(rc))
    {
      piModelEvent->ConnectTo(iObject);
      piModelEvent->Release();
      piModelEvent = NULL ;
    }
  }

  //--------------------------------
  // Sets a link with container 
  //--------------------------------
  CAAISysAccess * piSysAccess = NULL;                
  HRESULT rc = iObject ->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
  if (SUCCEEDED(rc))
  {
    piSysAccess->SetContainer(this);
    piSysAccess->Release();
    piSysAccess = NULL ;

    // New element in the list 
    _pListe->Append(iObject);
    iObject -> AddRef();
   
    // See CAAAfrDumpCommandHeader in CATAfrGeoCommands.m
    // This header receives this notification to render
    // accessible the command  
    //
    if ( 2 == _pListe->Size()  )
    {
      CAASysCollectionFilledNotif  * pNotifFilled = new CAASysCollectionFilledNotif();

      ::GetDefaultCallbackManager(this)->DispatchCallbacks(pNotifFilled,this);
      
      pNotifFilled->Release() ;
      pNotifFilled = NULL ;
    }

    CAASysCollectionModifNotif * pNotifModif = new CAASysCollectionModifNotif();

    ::GetDefaultCallbackManager(this)->DispatchCallbacks(pNotifModif,this);
      
    pNotifModif->Release() ;
    pNotifModif = NULL ;

    
  }

  return S_OK;
}

//-----------------------------------------------------------------------------------

HRESULT CAAEAfrCollection::RemoveObject (CATBaseUnknown * iObject)
{
  cout << "CAAEAfrCollection::RemoveObject" << endl;

  if ( (NULL == iObject) || (NULL == _pListe) )
     return E_FAIL ;

  //--------------------------------
  // Unset the link for the display
  //--------------------------------
  if ( 0 != _pListe->Size() )
  {
    // There is at least one object. 
    // The first element of the container is the UI activable object.
    // The link is between the UI active object and it.
    //  
    CATIModelEvents * piModelEvent = NULL;                
    CATBaseUnknown * pListe_1 = (*_pListe)[1];
    HRESULT rc = E_FAIL;
    if (pListe_1) rc = pListe_1 ->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
    if (SUCCEEDED(rc))
    {
      piModelEvent->DeconnectFrom(iObject);
      piModelEvent->Release();
      piModelEvent = NULL ;
    }
  }

  //--------------------------------
  // Unset link with container 
  //--------------------------------
  CAAISysAccess * piSysAccess = NULL;                
  HRESULT rc = iObject ->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
  if (SUCCEEDED(rc))
  {
     piSysAccess->SetContainer(NULL);
     piSysAccess->Release();
     piSysAccess = NULL ;
  
    // iObject remove from the list
     _pListe->RemoveValue(iObject);
     iObject -> Release();
     iObject = NULL ;
   
    // See CAAAfrDumpCommandHeader in CATAfrGeoCommands.m
    // This header receives this notification to render
    // not accessible the command  
    if ( 1 == _pListe->Size() )
    {  
      CAASysCollectionEmptyNotif * pNotifEmpty = new CAASysCollectionEmptyNotif();
      ::GetDefaultCallbackManager(this)->DispatchCallbacks(pNotifEmpty,this);
      pNotifEmpty->Release();
      pNotifEmpty = NULL ;

    }
    
    CAASysCollectionModifNotif * pNotifModif = new CAASysCollectionModifNotif();
    ::GetDefaultCallbackManager(this)->DispatchCallbacks(pNotifModif,this);
    pNotifModif->Release();
    pNotifModif = NULL ;
  }

  return S_OK;
}

//-----------------------------------------------------------------------------------

HRESULT CAAEAfrCollection::Empty()
{
  cout << "CAAEAfrCollection::Empty"<< endl;

  if (NULL == _pListe) return E_FAIL;

  //--------------------------------
  // Unsets links, for the display
  //--------------------------------

  CATIModelEvents * piModelEvents = NULL;                
  CATBaseUnknown * pListe_1 = (*_pListe)[1];
  HRESULT rc = E_FAIL;
  if (pListe_1) rc = pListe_1->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvents);
  if (SUCCEEDED(rc))
  {
    // The first element of the container is the UI activable object.
    // Deconnection with this object of all another
    for ( int i=2 ; i <= _pListe->Size() ;i++)
    {
       piModelEvents->DeconnectFrom((*_pListe)[i]);
    }
    piModelEvents -> Release();
    piModelEvents = NULL ;
  }
  
  //--------------------------------
  // Unsets links with the container  
  //--------------------------------

  for ( int i=1 ; i <= _pListe->Size() ;i++)
  {
    CAAISysAccess * piSysAccess = NULL;                
    CATBaseUnknown * pListe_i = (*_pListe)[i];
    rc = E_FAIL;
    if (pListe_i) rc =  pListe_i->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      piSysAccess->SetContainer(NULL);
      piSysAccess->Release();
      piSysAccess = NULL ;
    }
  }

  //--------------------------------
  // Empties the list 
  //--------------------------------
  while ( 0 != _pListe->Size() )
  {
    CATBaseUnknown * pObject = ((*_pListe)[1]) ;
    if ( NULL != pObject )
    {
       _pListe->RemoveValue(pObject);
       pObject-> Release();
       pObject = NULL ;
    }
  }

  return S_OK;
}







