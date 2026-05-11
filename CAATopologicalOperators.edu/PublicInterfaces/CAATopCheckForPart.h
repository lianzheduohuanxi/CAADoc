#include "CATIACGMLevel.h"
#ifdef CATIACGMR420CAA
#ifdef	__CAATopCheckForPart


//

// COPYRIGHT DASSAULT SYSTEMES 2000

//
#define ExportedByCAATopCheckForPart DSYExport
#else
#define ExportedByCAATopCheckForPart DSYImport
#endif
#include "DSYExport.h"
#else
#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAATopCheckForPart
#define	ExportedByCAATopCheckForPart	__declspec(dllexport)
#else
#define	ExportedByCAATopCheckForPart	__declspec(dllimport)
#endif
#else
#define	ExportedByCAATopCheckForPart
#endif
#endif
