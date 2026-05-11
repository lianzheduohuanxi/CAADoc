//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#include "CAAICafTexturePropertyPageEdtFactory.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAICafTexturePropertyPageEdtFactory = { 
    0x0cf4c1bc,
    0xd409,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
    };

// Declares that CAAICafTexturePropertyPageEdtFactory is an interface that 
// OM derives from CATIGenericFactory
CATImplementInterface(CAAICafTexturePropertyPageEdtFactory, CATIGenericFactory);
