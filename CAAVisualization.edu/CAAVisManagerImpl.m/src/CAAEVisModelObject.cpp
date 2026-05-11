// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVisModelObject.h"

// Visualization Framework
#include "CATMathPointf.h"
#include "CATIModelEvents.h"

// System Framework
#include "CATErrorDef.h" // for the SUCCEEDED macro

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CAAIVisModelObject.h"
TIE_CAAIVisModelObject(CAAEVisModelObject);

// To declare that the class is a data extension of CAAVisModelObject
//
CATImplementClass(CAAEVisModelObject,DataExtension,CATBaseUnknown,CAAVisModelObject);

// 
// To declare that CAAEVisModelObject implements CAAIVisModelObject, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelObject CAAIVisModelObject  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------

CAAEVisModelObject::CAAEVisModelObject():_Type(NULL)
{
  cout << "CAAEVisModelObject::CAAEVisModelObject" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVisModelObject::~CAAEVisModelObject()
{
  cout <<"CAAEVisModelObject::~CAAEVisModelObject()"<< endl; 
  
  if (NULL != _Type)
  {
     delete [] _Type;
     _Type = NULL;
  }
}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelObject::AddChild(CATBaseUnknown *iObject)
{
   if  ( ( NULL!=iObject) && ( 0 == _Children.ismember(iObject)) )
   {
      _Children.fastadd(iObject);
      iObject->AddRef();

      // We add the current object as a parent of the input object
      CAAIVisModelObject * pVMO = NULL;
      HRESULT rc1 = iObject->QueryInterface(IID_CAAIVisModelObject,(void **)&pVMO);
      if ( SUCCEEDED(rc1) )
      {
         pVMO->AddParent(this);
         pVMO->Release();
         pVMO = NULL ;
      }

      // we connect child to its parent in order to get the ability to send visualization event.
      CATIModelEvents *pME=NULL;
      HRESULT rc= this->QueryInterface(IID_CATIModelEvents,(void **)&pME);
      if (rc ==S_OK) 
      {
         pME->ConnectTo(iObject);
         pME->Release();
         pME = NULL ;
      }
         
         return S_OK;
   }
   else
   {
      return E_FAIL;
   }
}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelObject::RemChild(CATBaseUnknown *iObject)
{
   if  ( ( NULL != iObject)  && ( 1 == _Children.ismember(iObject) ) )
   {
      // We remove the current object as a parent of the input object
      CAAIVisModelObject * pVMO = NULL;
      HRESULT rc1 = iObject->QueryInterface(IID_CAAIVisModelObject,(void **)&pVMO);
      if ( SUCCEEDED(rc1) )
      {
         pVMO->RemParent(this);
         pVMO->Release();
         pVMO = NULL ;
      }
      
      // we disconnect child from its parent so that child cannot send visualization event to 
      // the current object anymore.
      CATIModelEvents *pME=NULL;
      HRESULT rc= this->QueryInterface(IID_CATIModelEvents,(void **)&pME);
      if (rc ==S_OK) 
      {
         pME->DeconnectFrom(iObject);
         pME->Release();
         pME = NULL ;
      }

      // the child is removewd from the children list 
      _Children -= iObject;
      iObject->Release();
      iObject = NULL ;

      return S_OK;
   }
   else
   {
      return E_FAIL;
   }
}

//----------------------------------------------------------------------------

list<CATBaseUnknown> *CAAEVisModelObject::GetChildren()
{
  return &_Children;
}

//----------------------------------------------------------------------------
	  
list<CATBaseUnknown> *CAAEVisModelObject::GetParents()
{
  return &_Parents;
}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelObject::GetType(char ** oType)
{
   HRESULT rc = E_FAIL ;

   if ( (NULL != oType) && (NULL !=_Type) )
   {
      *oType = new char [strlen(_Type)+1];
      strcpy(*oType,_Type) ;
      rc = S_OK;
   }

   return rc ;
}

HRESULT CAAEVisModelObject::SetType(const char * iType)
{
   HRESULT rc = E_FAIL ;

   if ( (NULL != iType) && (0 != strlen(iType)) ) 
   {
      if ( NULL != _Type )  delete [] _Type ;
         
      _Type = new char [strlen(iType)+1];
      strcpy(_Type,iType) ;
      
      rc = S_OK;
   }

   return rc ;
}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelObject::AddParent(CATBaseUnknown *iObject)
{
   if ( (NULL != iObject) &&  ( 0 == _Parents.ismember(iObject)) )
   {
      _Parents.fastadd (iObject);
      iObject->AddRef();
      return S_OK;
   }
   else
   {
      return E_FAIL;
   }
}

//----------------------------------------------------------------------------

HRESULT CAAEVisModelObject::RemParent(CATBaseUnknown *iObject)
{
   if ( (NULL != iObject) &&  ( 1 == _Parents.ismember(iObject)) )
   {
      _Parents -= iObject;
      iObject->Release();
      iObject = NULL ;

      return S_OK;
   }
   else
   {
      return E_FAIL;
   }
}
//----------------------------------------------------------------------------
