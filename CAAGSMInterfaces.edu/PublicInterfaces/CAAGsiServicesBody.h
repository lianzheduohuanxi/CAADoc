
// COPYRIGHT Dassault Systemes 2004

//
// CAAGsiServicesBody.h
// Header definition of CAAGsiServicesBody
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//

#ifndef CAAGsiServicesBody_h_
#define CAAGsiServicesBody_h_

#include "CAAGsiServicesExportedBy.h"
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATBody.h"
#include "CATDomain.h"

class CATIContainer_var ;
class CATGeoFactory_var ; 
class CATIGSMFactory_var ; 
class CATISpecObject_var ;



// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServicesBody / Body Access             ==============
// ----------------------------------------------------------------------------------------------
/**
 * Gets Current container. 
 */
ExportedByCAAGsiServices CATIContainer_var   CAAGsiGetCurrentContainer();

/**
 * Gets Generative Shape Design factory.  
 */
ExportedByCAAGsiServices CATIGSMFactory_var  CAAGsiGetGSMFactory (CATBaseUnknown *ipiFeature ) ;

/**
 * Gets Geometric Factory.
 */
ExportedByCAAGsiServices CATGeoFactory_var   CAAGsiGetGeoFactory(const CATISpecObject_var& spec);

/**
 * Gets Geometric body.
 */
ExportedByCAAGsiServices CATBody_var         CAAGsiGetFirstBody(const CATISpecObject_var& spec);

/**
 * Gets higher dim from body.
 */
ExportedByCAAGsiServices int                 CAAGsiGetHigherDimFromBody(const CATBody_var & Body);



#endif 
