// COPYRIGHT DASSAULT SYSTEMES  2010
//=============================================================================
//
// CAACloSpecPlacePart
//
#ifndef CAACloSpecPlacePart_H
#define CAACloSpecPlacePart_H

#include "CAAPspBaseEnvProtected.h"
#include "CATError.h"
#include "CATUnicodeString.h"

class CATIMovable;
class CATMathDirection;

//-----------------------------------------------------------------------------

class CAACloSpecPlacePart : public CAAPspBaseEnvProtected
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAACloSpecPlacePart ();
    virtual ~CAACloSpecPlacePart();  

    //-------------------------------------------------------------------------
    // Place a part in space.
    //-------------------------------------------------------------------------
    HRESULT PlaceSpecPartInSpace();

    //-------------------------------------------------------------------------
    // Input: iuFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing geometry, objects ...
    //-------------------------------------------------------------------------
    HRESULT DoSample (const CATUnicodeString &iuFileToBeLoaded);      

};
#endif
