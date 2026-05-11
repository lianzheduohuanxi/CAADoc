// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
//
#include <iostream.h>

// ObjectModelerBase and System
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATDocumentServices.h"
#include "CATSession.h"
#include "CATSessionServices.h"
#include "CATInit.h"
#include "LifeCycleObject.h"
#include "CATObject.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATIDocRoots.h"

// This framework
#include "CAAPspBaseEnvProtected.h"
#include "CAAPspBaseEnv.h"

// CATPlantShipInterfaces
#include "CATIPspLightPart.h"
#include "CATIPspPhysical.h"
#include "CATIPspLogicalLine.h"
#include "CATIPspApplication.h"

// Product Structure
#include "CATIProduct.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspBaseEnvProtected::CAAPspBaseEnvProtected()
{
  cout << "CAAPspBaseEnvProtected::CAAPspBaseEnvProtected()" << endl;
  _pPspBaseEnv = NULL;
  _pPspBaseEnv = new CAAPspBaseEnv;
};

//=============================================================================
//  Destructor
//=============================================================================
CAAPspBaseEnvProtected::~CAAPspBaseEnvProtected()
{
  cout << "CAAPspBaseEnvProtected::~CAAPspBaseEnvProtected()" << endl;
  if (_pPspBaseEnv) delete _pPspBaseEnv;
  _pPspBaseEnv = NULL;
  cout << "CAAPspBaseEnvProtected::Done" << endl;
}

//=============================================================================
//  CATProduct Environment
//=============================================================================
void CAAPspBaseEnvProtected::CreateCATProductEnv(const CATUnicodeString &iFileNameToBeLoaded)
{
  if (_pPspBaseEnv) 
    _pPspBaseEnv->CreateCATProductEnv(iFileNameToBeLoaded);
}

//=============================================================================
//  Get Document
//=============================================================================
CATDocument * CAAPspBaseEnvProtected::GetDocument ()
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetDocument();
  else
    return NULL;
}

//=============================================================================
//  Get Root Container
//=============================================================================
CATIContainer * CAAPspBaseEnvProtected::GetRootContainer ()
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetRootContainer();
  else
    return NULL;
}

//=============================================================================
//  Initialize Piping Design application
//=============================================================================
void CAAPspBaseEnvProtected::ApplicationInit (const CATUnicodeString &iuApplicationContext)
{
  if (_pPspBaseEnv) 
    _pPspBaseEnv->ApplicationInit(iuApplicationContext);
}

//=============================================================================
//  Get root product in the document
//=============================================================================
CATIProduct * CAAPspBaseEnvProtected::GetRootProduct ()
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetRootProduct();
  else
    return NULL;
}

//=============================================================================
//  Get a child object
//=============================================================================
IUnknown * CAAPspBaseEnvProtected::GetChildObject (IUnknown * iObjectTestMethod(const CATBaseUnknown_var &ispObject), 
                                          const CATIProduct *ipiParentProduct)
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetChildObject(iObjectTestMethod, ipiParentProduct);
  else
    return NULL;
}

IUnknown * CAAPspBaseEnvProtected::GetChildObject (const IID &iIID, 
                                          const CATUnicodeString &iuObjectName, 
                                          const CATIProduct *ipiParentProduct)
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetChildObject(iIID, iuObjectName, ipiParentProduct);
  else
    return NULL;
}

CATIPspPhysical * CAAPspBaseEnvProtected::GetAPhysicalObject (const CATIProduct *ipiParentProduct)
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetAPhysicalObject(ipiParentProduct);
  else
    return NULL;
}

//=============================================================================
//  Get a physical light object in the document
//=============================================================================
CATIPspLightPart * CAAPspBaseEnvProtected::GetALightObject (const CATIProduct *ipiParentProduct)
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetALightObject(ipiParentProduct);
  else
    return NULL;
}

//=============================================================================
//  Get a bendable pipe object in the document
//=============================================================================
CATIPspPhysical * CAAPspBaseEnvProtected::GetABendablePipeObject (const CATIProduct *ipiParentProduct)
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetABendablePipeObject(ipiParentProduct);
  else
    return NULL;
}

//=============================================================================
//  Get a logical line object in the document
//=============================================================================
CATIPspLogicalLine * CAAPspBaseEnvProtected::GetALogicalLine (const CATIProduct *ipiParentProduct)
{
  if (_pPspBaseEnv) 
    return _pPspBaseEnv->GetALogicalLine(ipiParentProduct);
  else
    return NULL;
}

//=============================================================================
//  CleanupSession
//=============================================================================
void CAAPspBaseEnvProtected::CleanupSession ()
{
  if (_pPspBaseEnv) 
    _pPspBaseEnv->CleanupSession();
}
