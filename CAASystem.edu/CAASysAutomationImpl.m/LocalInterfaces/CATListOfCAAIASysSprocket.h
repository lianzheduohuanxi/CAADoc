#ifndef CATListOfCAAIASysSprocket_h
#define CATListOfCAAIASysSprocket_h

// COPYRIGHT DASSAULT SYSTEMES 2002

class CAAIASysSprocket;

#include  "CATLISTP_Clean.h"

// Define the methods supported by the list of pointers to parameters
#define	CATLISTP_Append
#define	CATLISTP_RemoveAll
#define CATLISTP_FillArrayPtrs
#define CATLISTP_AppendList

#include  "CATLISTP_Declare.h"
// Declare the type : list of pointers to class <CAAIASysSprocket>
CATLISTP_DECLARE(CAAIASysSprocket);

typedef CATLISTP(CAAIASysSprocket) CATListOfCAAIASysSprocket;

#endif // CATListOfCAAIASysSprocket_h

