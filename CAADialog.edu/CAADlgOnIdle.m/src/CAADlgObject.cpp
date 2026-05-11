// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAADlgObject.h"
#include "CAADlgModifNotification.h"

//System Framework : to send a notification
#include "CATCallbackManager.h"

//C++ standard library
#include <iostream.h>

//----------------------------------------------------------------------------

CATImplementClass(CAADlgObject, Implementation, CATBaseUnknown, CATNull);

//----------------------------------------------------------------------------

CAADlgObject::CAADlgObject(char * iObjectName) 
{

  // Keep the name of the object
  if ( NULL != iObjectName )
  {
     _pObjectName = new char [strlen(iObjectName)+1];
     strcpy(_pObjectName,iObjectName);
  }else
  {
      _pObjectName = new char [5];
      strcpy(_pObjectName,"Line");
  }

  cout << "The " << _pObjectName << " is constructed" << endl;
}

//----------------------------------------------------------------------------

CAADlgObject::~CAADlgObject()
{

  cout << "The " << _pObjectName << " is deleted" << endl;

  if ( NULL != _pObjectName )
  {
     delete [] _pObjectName ;
     _pObjectName = NULL ;
  }

}

//---------------------------------------------------------------------------

void CAADlgObject::Modification() 
{
  cout << "The Object " << _pObjectName << " is Modified" << endl;
 
  CATCallbackManager * pCBManager = ::GetDefaultCallbackManager(this) ;
  if ( NULL != pCBManager )
  {
     CAADlgModifNotification * pNotification = new CAADlgModifNotification();
     pCBManager->DispatchCallbacks(pNotification, this);
     pNotification->Release();
  }
}

//---------------------------------------------------------------------------

char *CAADlgObject::GetName() 
{
  return(_pObjectName);
}
