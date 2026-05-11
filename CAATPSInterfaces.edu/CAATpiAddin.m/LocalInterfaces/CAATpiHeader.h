// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiHeader
//   Header class for starting sample commands regarding 3D Annotations.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

#ifndef CAATpiHeader_H
#define CAATpiHeader_H

#include "CATCommandHeader.h"

//-----------------------------------------------------------------------------
class CAATpiHeader : public CATCommandHeader
{
  CATDeclareClass;
  CATDeclareHeaderResources;

  public:

    CAATpiHeader (const CATString & iHeaderID,
                  const CATString & iLoadName,
                  const CATString & iClassName,
                  void * ipArgument,
                  int iState = CATFrmAvailable);

    virtual ~CAATpiHeader ();

  private:
    // must not be implemented
    CAATpiHeader (CAATpiHeader &);
    CAATpiHeader& operator=(CAATpiHeader&);
};
#endif
