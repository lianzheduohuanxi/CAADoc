// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CAA2DLHeader
//   Header class for starting sample commands regarding 2DL application.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2007  Creation
//=============================================================================

//-------------------------------------------------- Include file of this class
#include "CAA2DLHeader.h"

//-----------------------------------------------------------------------------
// Contructor
//-----------------------------------------------------------------------------
CAA2DLHeader::CAA2DLHeader (const CATString & iHeaderID,
                            const CATString & iLoadName,
                            const CATString & iClassname,
                            void * ipArgument,
                            int iState)
: CATCommandHeader(iHeaderID, iLoadName, iClassname, ipArgument, iState)
{}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAA2DLHeader::~CAA2DLHeader ()
{}


//-----------------------------------------------------------------------------
// 1er Arg : type of the header
// 2nd Arg : parent header for derivation
// 3em Arg : name of resource file

CATImplementHeaderResources(CAA2DLHeader, CATCommandHeader, CAA2DLHeader);

//-----------------------------------------------------------------------------
CATImplementClass(CAA2DLHeader, Implementation, CATCommandHeader, CATNull);
