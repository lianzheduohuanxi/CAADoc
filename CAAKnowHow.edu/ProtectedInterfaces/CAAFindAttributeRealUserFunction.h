#ifndef CAAFindAttributeRealUserFunction_H
#define CAAFindAttributeRealUserFunction_H

// COPYRIGHT DASSAULT SYSTEMES  2002


//==========================================================================
// ABSTRACT
//  
// CAAFindAttributeRealUserFunction is an example of user function which find 
// an attribute (for this example the parameter is an Real) under rulebase component.
// This attribute is use to parametrize the component.
// 
//==========================================================================
//  Usage:
//  ------
//		new CAAFindAttributeRealUserFunction()
//		Add().
//  
//==========================================================================
//  Inheritance:
//  ------------
//         Inherits from CATBaseUnknown.
//
//==========================================================================
//  Return Codes:
//  ------------
//         None
//
//==========================================================================

#include "CATBaseUnknown.h"
#include "CAACommonFunction.h"

class ExportedByCAACommonFunction CAAFindAttributeRealUserFunction : public CATBaseUnknown 
{
public :
	
	//---------------------------------------------------------------------------
	// The constructors below are not used
	// To create a CAALifDictionary, we use the CATICreateInstance implementation
	//---------------------------------------------------------------------------
	CAAFindAttributeRealUserFunction (){};
	CAAFindAttributeRealUserFunction (const CAAFindAttributeRealUserFunction&){};
	virtual ~CAAFindAttributeRealUserFunction (){};
	
	//---------------------------------------------------------------------------
	// Describe your user function with its signature, arguments and evaluator
	//---------------------------------------------------------------------------
	virtual void Add ();
	
	CATDeclareClass;
} ;

class ExportedByCAACommonFunction CAAFindAttributeRealUserFunctionExt : public CATBaseUnknown 
{
public :
	
	//-------------------------------
	// Constructors (not used)
	//-------------------------------
	CAAFindAttributeRealUserFunctionExt (){};
	CAAFindAttributeRealUserFunctionExt (const CAAFindAttributeRealUserFunctionExt&){};
	
	//-------------------------------
	// Destructor
	//-------------------------------
	virtual ~CAAFindAttributeRealUserFunctionExt (){};
	
	//-------------------------------
	// Create a CAALifDicoLibrary object and returns its pointer.
	//-------------------------------
	virtual HRESULT __stdcall CreateInstance (void **ppv);
	
	CATDeclareClass;
	
} ;
  
#endif
