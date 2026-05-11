// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
#ifndef CAAAniAeroDynamicTransition_H
#define CAAAniAeroDynamicTransition_H

#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
class CATDocument;

//-----------------------------------------------------------------------

/**
 * Class to implement CATISamAnalysisTransition and CATIAlias 
 * on the type AeroDynamic.
 * <br>
 * It implements the interfaces :
 *  @see CATAnalysisInterfaces.CATISamAnalysisTransition
 *  @see ObjectModelerBase.CATIAlias
 *  
 */
class CAAAniAeroDynamicTransition: public CATBaseUnknown
	{
	CATDeclareClass;

	public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
		CAAAniAeroDynamicTransition ();
		virtual ~CAAAniAeroDynamicTransition ();

/**
 * Implements the execution of the transition.
 * @see CATISamAnalysisTransition#ExecuteTransition
 */
		HRESULT ExecuteTransition (const CATDocument* iDocument) ;

/**
 * Sets an alias to the object.
 * @param iName  alias to associate to the object.
 */	
	void SetAlias(const CATUnicodeString&  iName ) ;

/**
 * Returns alias of the object.
 * @see ObjectModelerBase#GetAlias
 */	
    CATUnicodeString GetAlias() ;

	private:

// The copy constructor and the equal operator must not be implemented
// -------------------------------------------------------------------
		CAAAniAeroDynamicTransition (CAAAniAeroDynamicTransition &);
		CAAAniAeroDynamicTransition& operator=(CAAAniAeroDynamicTransition&);

	};

//-----------------------------------------------------------------------

#endif
