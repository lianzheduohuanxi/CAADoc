// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CAA2DLHeader
//   Header class for starting sample commands regarding 2DL.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2007  Creation
//=============================================================================

#ifndef CAA2DLHeader_H
#define CAA2DLHeader_H

#include "CATCommandHeader.h"

//-----------------------------------------------------------------------------
class CAA2DLHeader : public CATCommandHeader
{
  CATDeclareClass;
  CATDeclareHeaderResources;

  public:

    CAA2DLHeader (const CATString & iHeaderID,
                  const CATString & iLoadName,
                  const CATString & iClassName,
                  void * ipArgument,
                  int iState = CATFrmAvailable);

    virtual ~CAA2DLHeader ();

  private:
    // must not be implemented
    CAA2DLHeader (CAA2DLHeader &);
    CAA2DLHeader& operator=(CAA2DLHeader&);
};
#endif
