#ifndef CAALicensingUserFunction_H
#define CAALicensingUserFunction_H

// COPYRIGHT DASSAULT SYSTEMES  2002


//==========================================================================
// ABSTRACT
//  
// CAALicensingUserFunction is an example of user function which test 
// licensing and send an error if license is not ok (simulation)
// 
//==========================================================================
//  Usage:
//  ------
//		new CAALicensingUserFunction()
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


class CAALicensingUserFunction : public CATBaseUnknown 
{
public :
	
	//---------------------------------------------------------------------------
	// The constructors below are not used
	// To create a CAALifDictionary, we use the CATICreateInstance implementation
	//---------------------------------------------------------------------------
	CAALicensingUserFunction (){};
	CAALicensingUserFunction (const CAALicensingUserFunction&){};
	virtual ~CAALicensingUserFunction (){};
	
	//---------------------------------------------------------------------------
	// Describe your user function with its signature, arguments and evaluator
	//---------------------------------------------------------------------------
	virtual void Add ();
	
	CATDeclareClass;
} ;

class CAALicensingUserFunctionExt : public CATBaseUnknown 
{
public :
	
	//-------------------------------
	// Constructors (not used)
	//-------------------------------
	CAALicensingUserFunctionExt (){};
	CAALicensingUserFunctionExt (const CAALicensingUserFunctionExt&){};
	
	//-------------------------------
	// Destructor
	//-------------------------------
	virtual ~CAALicensingUserFunctionExt (){};
	
	//-------------------------------
	// Create a CAALifDicoLibrary object and returns its pointer.
	//-------------------------------
	virtual HRESULT __stdcall CreateInstance (void **ppv);
	
	CATDeclareClass;
	
} ;
  
#endif
