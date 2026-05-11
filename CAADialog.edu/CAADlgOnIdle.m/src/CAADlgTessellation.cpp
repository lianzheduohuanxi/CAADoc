// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAADlgTessellation.h"
#include "CAADlgObject.h"

//C++ Standrad Library 
#include <iostream.h>

//-----------------------------------------------------------------------

CAADlgTessellation::CAADlgTessellation(char * iTessellationType) 
{

  _pObject=NULL;

  // Keep the type of tessellation
  if ( NULL != iTessellationType )
  {
     _pTessellationType = new char [strlen(iTessellationType)+1];
     strcpy(_pTessellationType,iTessellationType);
  }else
  {
      _pTessellationType = new char [15];
      strcpy(_pTessellationType,"Rought");
  }

  cout << "The Tessellation of type=" << _pTessellationType << " is created" << endl; 
}

//-----------------------------------------------------------------------

CAADlgTessellation::~CAADlgTessellation() 
{
  cout << "The Tessellation of type=" << _pTessellationType << " is deleted" << endl; 

  if ( NULL != _pObject) 
  {
    ::RemoveSubscriberCallbacks(this, _pObject);
    _pObject=NULL;
  };
  delete [] _pTessellationType ;
  _pTessellationType = NULL  ;
  
}

//-----------------------------------------------------------------------

void CAADlgTessellation::Init(CAADlgObject *iObject) 
{
  if ( iObject !=  _pObject )
  {
     if ( NULL != _pObject) 
     {
       
        ::RemoveSubscriberCallbacks(this, _pObject);
     };

     _pObject=iObject;
  
     if ( NULL !=  iObject )
     {
        // I want to be prevent when the object has changed
        CATCallback idCB ;
        idCB = ::AddCallback(this,
                   iObject,
                   "CAADlgModifNotification",
                   (CATSubscriberMethod)&CAADlgTessellation::Tessellate,
                   NULL);
        
        // In this sample idCB is not used, but you can keep this value
        // as data member and reused it to make the destruction of this callback:
        // RemoveSubscriberCallbacks(_pObject,idCB)

        cout <<"Set CB on the " << iObject->GetName() << endl;

     }  
  }

}

//-----------------------------------------------------------------------

void CAADlgTessellation::Tessellate(CATCallbackEvent  iEventObject,
                            void             *iObject,
                            CATNotification  *iNotifObject,
                            CATSubscriberData iUsefulData,
                            CATCallback       iCallBack ) 
{
  CAADlgObject * pModifiedObject = (CAADlgObject *)iObject;
  
  if ( NULL != pModifiedObject )
  {
     cout <<"The " <<pModifiedObject->GetName() << " is Tessellated" << endl;
  }
}

