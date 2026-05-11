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

//-------------------------------------------------- Include file of this class
#include "CAATpiHeader.h"

//-----------------------------------------------------------------------------
// Contructor
//-----------------------------------------------------------------------------
CAATpiHeader::CAATpiHeader (const CATString & iHeaderID,
                            const CATString & iLoadName,
                            const CATString & iClassname,
                            void * ipArgument,
                            int iState)
: CATCommandHeader(iHeaderID, iLoadName, iClassname, ipArgument, iState)
{}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiHeader::~CAATpiHeader ()
{}


//-----------------------------------------------------------------------------
// 1er Arg : type of the header
// 2nd Arg : parent header for derivation
// 3em Arg : name of resource file

CATImplementHeaderResources(CAATpiHeader, CATCommandHeader, CAATpiHeader);

//-----------------------------------------------------------------------------
CATImplementClass(CAATpiHeader, Implementation, CATCommandHeader, CATNull);
