#ifndef CAALifValuatorFeatureDef_H
#define CAALifValuatorFeatureDef_H
//COPYRIGHT DASSAULT SYSTEMES  1994 2000
// =============================================================================
//
// ABSTRACT
// --------
// A class for holding the methods that create the CAALifFeature.
//
// =============================================================================
//  Usage:
//  ------
//	CAALifValuatorFeatureDef::Start(...), creates the Startup of the feature.
//  CAALifValuatorFeatureDef::GetInstance(...) returns aninstance of the
// feature.
// CAALifValuatorFeatureDef::End(...), clean the class.
//   
// 	
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================
//  Main Method:
//  ------------
//				None
//
//===========================================================================

//ObjectModeler
#include "CATISpecObject.h"

//LiteralFeatures
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"

//CAALiteralFeatures
#include "CAALifServices.h"
#include "CAALifReturnCodes.h"

class CATOsmSUHandler;

class CAALifValuatorFeatureDef
{
public:
	/**
	*	Creates the startup feature.
	* @param ispFact The Parameter factory.
	* @return CAALifReturnCodes
	*/
  static int Start (CATIContainer* ipiContainer, const char* iCatalogName);
	/**
	*	Returns the startup of the CAALifFeature feature.
	* @return the feature.
	*/
  static CATISpecObject_var GetStartUp () ;
	
	/**
	*	Instanciates the CAALifFeature.
	* @param ispFact the parameteres factory.
	* @param iInParameter the input parameter.
	* @param iOutParam the output parameter.
	*/
  static CATISpecObject_var GetInstance ( const CATICkeParmFactory_var &ispFact,
	                                      const CATICkeParm_var &iInParameter,
										  const CATICkeParm_var &iOutParameter);
  
	/**
	*	Cleans this class.
	*/
  static void End ();

private :

  static CATISpecObject_var _spCAAFeature;
  static CATOsmSUHandler *_spSUHandler;
};




#endif


