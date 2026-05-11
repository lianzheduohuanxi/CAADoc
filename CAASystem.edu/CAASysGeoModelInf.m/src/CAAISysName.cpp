// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysName.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysName={ /* e53e2f16-89e3-4b22-ab08-15e051152df9 */
    0xe53e2f16,
    0x89e3,
    0x4b22,
    {0xab, 0x08, 0x15, 0xe0, 0x51, 0x15, 0x2d, 0xf9}
  };


// Declares that CAAISysName is an interface 
CATImplementInterface(CAAISysName, CATBaseUnknown);

