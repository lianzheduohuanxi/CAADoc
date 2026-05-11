// COPYRIGHT DASSAULT SYSTEMES 2003

// Local Framework
#include "CAAIAfrMRUManagement.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIAfrMRUManagement = { /* 3e2ac3c7-aa04-4b63-910f-af072affa19a */
    0x3e2ac3c7,
    0xaa04,
    0x4b63,
    {0x91, 0x0f, 0xaf, 0x07, 0x2a, 0xff, 0xa1, 0x9a}
  };

// Declares that CAAIAfrMRUManagement is an interface
CATImplementInterface(CAAIAfrMRUManagement, CATBaseUnknown);

