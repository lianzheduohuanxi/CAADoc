// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAALifInstanceScrewExt.h
// Provide implementation to interface CATIInstance
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   EXTENSION: Screw
//   TIE: CATIInstance
//End CAA2 Wizard Generation Report
//
//===================================================================
#ifndef CAALifInstanceScrewExt_H
#define CAALifInstanceScrewExt_H

#include "CATKweInstanceAdapter.h"

//-----------------------------------------------------------------------

/**
* Class extending the object "CAALifFeatureScrew".
* <br>
* It implements the interfaces :
*  <ol>
*  <li>@see KnowledgeInterfaces.CATIInstance
*  </ol>
* Using this prefered syntax will enable mkdoc to document your class.
*/
class CAALifInstanceScrewExt: public CATKweInstanceAdapter
{
	CATDeclareClass;

public:
	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	CAALifInstanceScrewExt ();
	virtual ~CAALifInstanceScrewExt ();

protected:
	//Returns the main type of an object.
	virtual CATIType* TypeInternal() const ;

	//Sets an attribute value.
	virtual HRESULT SetValueInternal( const CATUnicodeString& iKey, const CATIValue_var& iValue ) ;

	//Gets an attribute value.
	virtual CATIValue* GetValueInternal( const CATUnicodeString& iKey ) ;

private:
	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
	CAALifInstanceScrewExt (CAALifInstanceScrewExt &);
	CAALifInstanceScrewExt& operator=(CAALifInstanceScrewExt&);

};

//-----------------------------------------------------------------------

#endif
