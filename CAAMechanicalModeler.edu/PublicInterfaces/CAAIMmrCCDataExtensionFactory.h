// COPYRIGHT DASSAULT SYSTEMES 2007

#ifndef CAAIMmrCCDataExtensionFactory_H
#define CAAIMmrCCDataExtensionFactory_H

// Local Framework
#include "CAAMmrCCDataExtension.h"

// System Framework
#include "CATBaseUnknown.h"

class CAAIMmrCCDataExtension;

extern ExportedByCAAMmrCCDataExtension IID IID_CAAIMmrCCDataExtensionFactory ;

/**
 * Interface to create a MmrCCDataExtension.
 * 
 * Role : use this interface to create a MmrCCDataExtension.
 *        A MmrCCDataExtension is an Extension which compute the length of a Combined Curve
 *        Consequently, a MmrCCDataExtension has only one input: The Combined Curve.
 */

class ExportedByCAAMmrCCDataExtension CAAIMmrCCDataExtensionFactory: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

   /* Creates an explicit MmrCCDataExtension
    *   @param iBaseFeature
    *      The Base Feature to extend
    *   @param ioMmrCCDataExtension
    *      The MmrCCDataExtension Created
    * 
    *   Returns S_OK if everything ran ok, E_FAIL otherwise.
    */
    
    virtual HRESULT CreateMmrCCDataExtension(const CATBaseUnknown *iBaseFeature,
                                             CAAIMmrCCDataExtension **ioMmrCCDataExtension) = 0;
};

#endif
