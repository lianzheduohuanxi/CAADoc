// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniAeroMesher.h
// Provide implementation to interface CATIMSHMesher
// Sample of code for managing Analysis data for Aero Dynamic.
// Import of Meshing data inside the CATAnalysis.
//===================================================================
#ifndef CAAAniAeroMesher_H
#define CAAAniAeroMesher_H

#include "CATMSHExtIMesher.h"

class CATIMSHMeshPart;
class CATUnicodeString;
class CATDocument;

//-----------------------------------------------------------------------

/**
 * Class Class extending the object "AeroMeshPart_mesher".
 * <br>
 * It implements the interfaces :
 *  <ol>
 *  <li>@see AnalysisMeshingModel.CATIMSHMesher
 *  </ol>
 */
class CAAAniAeroMesher: public CATMSHExtIMesher
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
    CAAAniAeroMesher ();
    virtual ~CAAAniAeroMesher ();

    /**
     * Implements a function from an interface.
     */
	int IsATypeOf (CATIMSHMeshPart * iMeshPart ,const CATUnicodeString &iType );
    HRESULT CheckSupport ( CATIMSHMeshPart * iMeshPart , int &oNbParents , CATIMSHMeshPart ** &oParentMeshParts );
    HRESULT Mesh ( CATIMSHMeshPart * iMeshPart ) ;

  private:
    // Retrieve the support (external file as CATDocument)
    HRESULT GetLinkedDoc ( CATIMSHMeshPart * iMeshPart,CATDocument* &oDoc) ;

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAAniAeroMesher (CAAAniAeroMesher &);
    CAAAniAeroMesher& operator=(CAAAniAeroMesher&);
};

//-----------------------------------------------------------------------

#endif
