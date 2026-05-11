// COPYRIGHT DASSAULT SYSTEMES 1999
//===================================================================
//
// CAAAniExplicitAeroSet.h
// Provide implementation to interface
//    CATISamExplicitation for AnalysisSet 
//
//===================================================================
#ifndef CAAAniExplicitAeroSet_H
#define CAAAniExplicitAeroSet_H

#include "CATISamExplicitation.h"

//-----------------------------------------------------------------------

/**
 * Class Class extending the object "AnalysisSet".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see CATAnalysisInterfaces.CATISamExplicitation
 *  </ol>
 * Using this prefered syntax will enable mkdoc to document your class.
 */
class CAAAniExplicitAeroSet: public CATISamExplicitation
{
	CATDeclareClass;

	public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
		CAAAniExplicitAeroSet();
		virtual ~CAAAniExplicitAeroSet();

 /**
  * Implements a function Explicit from an interface.
  * @see CATAnalysisInterfaces.CATISamExplicitation#TranslateToFieldModel
  */
		HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate,
									  CATISamAnalysisModel* iFEMModel,
									  CATAnalysisExplicitListUsr& iOldExplObjects,
									  CATAnalysisExplicitListUsr& oNewExplObjects);

	private:
// The copy constructor and the equal operator must not be implemented
// -------------------------------------------------------------------
		CAAAniExplicitAeroSet (CAAAniExplicitAeroSet &);
		CAAAniExplicitAeroSet& operator=(CAAAniExplicitAeroSet&);

};

//-----------------------------------------------------------------------

#endif
