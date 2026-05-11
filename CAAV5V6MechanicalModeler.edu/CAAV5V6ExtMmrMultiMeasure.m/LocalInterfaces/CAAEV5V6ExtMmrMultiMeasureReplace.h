// COPYRIGHT DASSAULT SYSTEMES 2012

#ifndef CAAEV5V6ExtMmrMultiMeasureReplace_H
#define CAAEV5V6ExtMmrMultiMeasureReplace_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIReplace interface
//  which  manages the replacement of a Feature by another one for a given Role.   
//
//                   
//  This extension extends the MmrMultiMeasure Features.
//
//===========================================================================

#include "CATIReplace.h"


class CAAEV5V6ExtMmrMultiMeasureReplace : public CATIReplace
{
	CATDeclareClass;

public :

	CAAEV5V6ExtMmrMultiMeasureReplace();
	virtual ~CAAEV5V6ExtMmrMultiMeasureReplace();

	HRESULT IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
									const CATBaseUnknown_var& ispElement,
									CATUnicodeString& oMessage, 
									int& oElementValidity,
									const CATBaseUnknown_var& ispOldValue=NULL_var);

	HRESULT Replace(const CATUnicodeString& iNameOfRole,
					CATBaseUnknown_var& ispNewElement,
					const CATBaseUnknown_var& ispOldValue=NULL_var);


private:

	// Copy constructor, not implemented
	// Set as private to prevent from compiler automatic creation as public.
	CAAEV5V6ExtMmrMultiMeasureReplace(const CAAEV5V6ExtMmrMultiMeasureReplace &iObjectToCopy);

	// Assignment operator, not implemented
	// Set as private to prevent from compiler automatic creation as public.
	CAAEV5V6ExtMmrMultiMeasureReplace & operator = (const CAAEV5V6ExtMmrMultiMeasureReplace &iObjectToCopy);
};

#endif
