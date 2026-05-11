
// COPYRIGHT Dassault Systemes 2004
//============================================================================================
// CAAGsiServices.h
// Header definition of CAAGsiServices
//===================================================================
//
// Usage notes:
//
//===================================================================
//

#ifndef CAAGsiServices_h_
#define CAAGsiServices_h_


#include "CAAGsiServices.h"
#include "CAAGsiServicesExportedBy.h"


#include "CATBoolean.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

class CATIContainer_var ; 
class CATISpecObject_var ; 
class CATIPrtPart_var ; 
class CATIGSMTool_var ; 
class CATICkeParm_var ; 


// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / GeometricalSets ==============
// ----------------------------------------------------------------------------------------------
/** 
 * Creates Geometric Feature Sets. 
 * @param iType 
 *   iType   = 0 / GS
 *   iType   = 1 / OGS
 *   iType   = 2 / HybridBody 
 * @param iTopLevel
 *   iTopLevel = 1 / UNDER Part 
 *   iTopLevel = 0 / UNDER Current feature  if spParentForTool not specify 
 *   iTopLevel = 0 / UNDER  spParentForTool if spParentForTool  is specify
 * @param spInputParentTool 
 *   Define parent tool for New tool
 * @param oDiag 
 *   oDiag = 0 or -1  OK 
 *   oDiag = 1  A GS  can only be inserted under another GS or directly under the part
 *   oDiag = 2  A Body or an OGS can only be inserted under another Body or OGS  or directly under the part
 *   oDiag = 3  Input Parent for tool is not a GS, OGS or Body
*/

ExportedByCAAGsiServices HRESULT  CAAGsiCreateGeometricFeatureSets (
  const CATIContainer_var &ispCont, const CATUnicodeString& iName, 
  const CATISpecObject_var & spInputParentTool , 
  CATISpecObject_var  & spSpecTool,  int & oDiag, int iTopLevel=1, int iType=0  );

/** 
 *  Gets current GS or OGS ,  create one  GS  under Part if none found 
 */
ExportedByCAAGsiServices CATIGSMTool_var  
CAAGsiGetCurrentSurfacicFeatureSet (
  const CATIContainer_var &ispCont, const CATUnicodeString& iName,int iSetAsCurrent);



// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / Object                ==============
// ----------------------------------------------------------------------------------------------

/**
 * Insert a Shape Design feature  in PartDocument. 
 * <br> ie: Feaure derivating fron GSMGeom 
 */ 
ExportedByCAAGsiServices HRESULT    CAAGsiInsertInProceduralView(const CATISpecObject_var  ispObjectToAppend,
		       CATISpecObject_var  ispInputParent);


/**
 * Insert a geometrical feature in PartDocument.
 * <br> ie: Feature derivating from GeometricalElement3D 
 */ 
ExportedByCAAGsiServices HRESULT    CAAGsiInsertGeometricalElement(const CATIContainer_var ispCont, const CATISpecObject_var ispObjectToAppend,
                       CATISpecObject_var ispInputParent);


/**
 * Update of a feature. 
 * <br> note: this method encapsulates the standard update, in order to catch if needed update errors 
 */
ExportedByCAAGsiServices HRESULT     CAAGsiObjectUpdate(const CATISpecObject_var & ispSpec);


/**
 * Gets NLS name of a Feature.  
 */
ExportedByCAAGsiServices CATUnicodeString CAAGsiGetSpecDisplayName(const CATBaseUnknown_var& CurrentSpec);


// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / FeatureSearch   ==============
// ----------------------------------------------------------------------------------------------
/**
 * Retrieve element in current openned  Part document (Scans Geometric sets )  
 */
ExportedByCAAGsiServices  CATISpecObject_var CAAGsiSearchFeatureFromName(CATIPrtPart_var & spPrtPart, CATUnicodeString  SearchedFeatName);

// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / Remove spec        ==============
// ----------------------------------------------------------------------------------------------

/**
 * Remove Spec Object.
 */
ExportedByCAAGsiServices HRESULT              CAAGsiRemove ( CATISpecObject_var SpecToRemove) ;

// ----------------------------------------------------------------------------------------------
// ========= CAAGsiServices / Knowledge       ==============
// ----------------------------------------------------------------------------------------------
/**
 * Instanciate Litteral.
 * <ul> 
 * <li> "Length" </li>
 * <li> "Angle"</li>
 * <li>  "Integer" </li>
 * <li>  "Real"</li>
 * <li>  "Booleen" </li>
 * </ul> 
 */
ExportedByCAAGsiServices CATICkeParm_var 
CAAGsiInstanciateLitteral (CATUnicodeString  NomLitteral, CATIContainer_var  Cont,CATUnicodeString Name);

#endif 
