#ifndef CAAGenerateResultsUserFunction_H
#define CAAGenerateResultsUserFunction_H

// COPYRIGHT DASSAULT SYSTEMES  2002


//==========================================================================
// ABSTRACT
//  
// CAAGenerateResultsUserFunction is an example of user function which test 
// licensing and send an error if license is not ok (simulation)
// 
//==========================================================================
//  Usage:
//  ------
//		new CAAGenerateResultsUserFunction()
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

class ExportedByCAACommonFunction CAAGenerateResultsUserFunction : public CATBaseUnknown 
{
public :
	
	//---------------------------------------------------------------------------
	// The constructors below are not used
	// To create a CAALifDictionary, we use the CATICreateInstance implementation
	//---------------------------------------------------------------------------
	CAAGenerateResultsUserFunction (){};
	CAAGenerateResultsUserFunction (const CAAGenerateResultsUserFunction&){};
	virtual ~CAAGenerateResultsUserFunction (){};
	
	//---------------------------------------------------------------------------
	// Describe your user function with its signature, arguments and evaluator
	//---------------------------------------------------------------------------
	virtual void Add ();
	
	CATDeclareClass;
} ;

class ExportedByCAACommonFunction CAAGenerateResultsUserFunctionExt : public CATBaseUnknown 
{
public :
	
	//-------------------------------
	// Constructors (not used)
	//-------------------------------
	CAAGenerateResultsUserFunctionExt (){};
	CAAGenerateResultsUserFunctionExt (const CAAGenerateResultsUserFunctionExt&){};
	
	//-------------------------------
	// Destructor
	//-------------------------------
	virtual ~CAAGenerateResultsUserFunctionExt (){};
	
	//-------------------------------
	// Create a CAALifDicoLibrary object and returns its pointer.
	//-------------------------------
	virtual HRESULT __stdcall CreateInstance (void **ppv);
	
	CATDeclareClass;
	
} ;
  
#endif
