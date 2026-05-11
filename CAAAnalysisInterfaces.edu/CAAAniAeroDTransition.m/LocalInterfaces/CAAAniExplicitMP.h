// COPYRIGHT DASSAULT SYSTEMES 2001
//===================================================================
//
// CAAAniExplicitMP.h
// Provide an implementation to interface CATISamExplicitation  
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//===================================================================
#ifndef CAAAniExplicitMP_H
#define CAAAniExplicitMP_H

#include "CATBaseUnknown.h"

class CATISpecObject;
class CATDocument;
class CATISamAnalysisModel;
class CATAnalysisExplicitListUsr;

//-----------------------------------------------------------------------

/**
 * Class Class extending the object with late type "STRUCTURAL_AeroMeshPart".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see CATAnalysisInterfaces.CATISamExplicitation
 *  </ol>
 * Using this prefered syntax will enable mkdoc to document your class.
 */
class CAAAniExplicitMP: public CATBaseUnknown
	{
	CATDeclareClass;

	public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
		CAAAniExplicitMP();
		virtual ~CAAAniExplicitMP();

 /**
  * Implements a function Explicit from an interface.
  * @see CATAnalysisModeler.CATISamExplicitation#TranslateToFieldModel
  */
		HRESULT TranslateToFieldModel(CATISpecObject* iFeatToTranslate, 
									  CATISamAnalysisModel* iFEMModel, 
									  CATAnalysisExplicitListUsr& iOldExplObjects, 
									  CATAnalysisExplicitListUsr& oNewExplObjects);

	private:
// The copy constructor and the equal operator must not be implemented
// -------------------------------------------------------------------
		CAAAniExplicitMP (CAAAniExplicitMP &);
		CAAAniExplicitMP& operator=(CAAAniExplicitMP&);

    // Retrieve the support (external file as CATDocument)
    HRESULT GetLinkedDoc (CATISpecObject* iFeatToTranslate,CATDocument* &oDoc) ;
	};

//-----------------------------------------------------------------------

#endif
