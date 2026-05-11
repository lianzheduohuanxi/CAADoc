//COPYRIGHT DASSAULT SYSTEMES  1994 2000
// =============================================================================
//
// ABSTRACT
// --------
// Implements the necessary interfaces for building a feature that 
// valuates a parameter as output.
//
// =============================================================================
//  Usage:
//  ------
//		In Show() implement the way the output parameter is seen through the 
//	knowledgeware editors.
//		In Build() implement the valuation of the otput parameter in function
// of the input one.
//   
// 	
//===========================================================================
//  Inheritance:
//  ------------
//         CATParmValuatorAdapter
//
//===========================================================================
//  Main Method:
//  ------------
//				None
//
//===========================================================================

#ifndef CAAExtensionForMeasure_H
#define CAAExtensionForMeasure_H

//LiteralFeatures
#include "CATParmValuatorAdapter.h"


class CAAExtensionForMeasure : public CATParmValuatorAdapter
{

public:

	// Constructors/Destructors
	CAAExtensionForMeasure ();
	virtual ~CAAExtensionForMeasure ();


	/**
	*	Implements CATIParmValuator
	*/
	virtual CATUnicodeString  Show () const ;

	/**
	*	Implements CATIBuild
	*/
	virtual HRESULT Build();

protected:
	// Copy Constructor
	CAAExtensionForMeasure (const CAAExtensionForMeasure &);

	CATDeclareClass;     

};
#endif
